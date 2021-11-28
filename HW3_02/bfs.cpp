#include "bfs.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstddef>
#include <omp.h>

#include "../common/CycleTimer.h"
#include "../common/graph.h"

#define ROOT_NODE_ID 0
#define NOT_VISITED_MARKER -1

void vertex_set_clear(vertex_set *list)
{
    list->count = 0;
}

void vertex_set_init(vertex_set *list, int count)
{
    list->max_vertices = count;
    list->vertices = (int *)malloc(sizeof(int) * list->max_vertices);
    vertex_set_clear(list);
}

// Take one step of "top-down" BFS.  For each vertex on the frontier,
// follow all outgoing edges, and add all neighboring vertices to the
// new_frontier.
void top_down_step(
    Graph g,
    vertex_set *frontier,
    vertex_set *new_frontier,
    vertex_set *bu_frontier,
    vertex_set *bu_new_frontier,
    int *distances,int *p_mfrontier_count)
{
    // int count=1;
    #pragma omp parallel for schedule(dynamic,512)
    for (int i = 0; i < frontier->count; i++)
    {
        int node = frontier->vertices[i];

        int start_edge = g->outgoing_starts[node];
        int end_edge = (node == g->num_nodes - 1)
                           ? g->num_edges
                           : g->outgoing_starts[node + 1];

        // attempt to add all neighbors to the new frontier
        for (int neighbor = start_edge; neighbor < end_edge; neighbor++)
        {   
            // count mf
            // add mf in each tp step then subtract it from total number of edge to get nf 
            *p_mfrontier_count+=1;
            int outgoing = g->outgoing_edges[neighbor];
            if (distances[outgoing] == NOT_VISITED_MARKER)
            {   
                distances[outgoing] = distances[node] + 1; //distances stores the distance of each node to root 
                #pragma omp critical
                {
                    int index = new_frontier->count++;
                    bu_new_frontier->count++;
                    new_frontier->vertices[index] = outgoing;
                    bu_new_frontier->vertices[outgoing]=1;
                }                
            }
        }
        // count++;
    }
    // printf("count: %d\n",count);
}

// Implements top-down BFS.
//
// Result of execution is that, for each node in the graph, the
// distance to the root is stored in sol.distances.
void bfs_top_down(Graph graph, solution *sol)
{
    vertex_set list1;
    vertex_set list2;
    vertex_set list3;
    vertex_set list4;
    vertex_set_init(&list1, graph->num_nodes);
    vertex_set_init(&list2, graph->num_nodes);
    vertex_set_init(&list3, graph->num_nodes);
    vertex_set_init(&list4, graph->num_nodes);

    vertex_set *frontier = &list1; // frontier in pseudocode
    vertex_set *new_frontier = &list2; // next in pseudocode
    vertex_set *bu_frontier = &list3; // frontier in pseudocode
    vertex_set *bu_new_frontier = &list4; // next in pseudocode

    bool bfs_top_down=true;
    int sum_mfrontier_count=0;
    int* p_mfrontier_count=&sum_mfrontier_count;    
    
    // initialize all nodes to NOT_VISITED
    #pragma omp parallel for
    for (int i = 0; i < graph->num_nodes; i++)
        sol->distances[i] = NOT_VISITED_MARKER;

    // setup frontier with the root node
    #pragma omp single
    {    
        frontier->vertices[frontier->count++] = ROOT_NODE_ID;
        bu_frontier->vertices[ROOT_NODE_ID]=1;
        sol->distances[ROOT_NODE_ID] = 0;
        bu_frontier->count++;
    }

    while (frontier->count != 0)
    {
// #define VERBOSE   1

#ifdef VERBOSE
        double start_time = CycleTimer::currentSeconds();
#endif

        vertex_set_clear(new_frontier);
        vertex_set_clear(bu_new_frontier);
        top_down_step(graph, frontier, new_frontier,bu_frontier,bu_new_frontier, sol->distances,p_mfrontier_count);

#ifdef VERBOSE
        double end_time = CycleTimer::currentSeconds();
        printf("frontier=%-10d %.4f sec\n", frontier->count, end_time - start_time);
#endif

        // swap pointers
        vertex_set *tmp = frontier;
        frontier = new_frontier;
        new_frontier = tmp;

        vertex_set *bu_tmp = bu_frontier;
        bu_frontier = bu_new_frontier;
        bu_new_frontier = bu_tmp;        
    }
}

// Take one step of "top-down" BFS.  For each vertex on the frontier,
// follow all outgoing edges, and add all neighboring vertices to the
// new_frontier.
void bottom_up_step(
    Graph g,
    vertex_set *frontier,
    vertex_set *new_frontier,     
    vertex_set *bu_frontier,
    vertex_set *bu_new_frontier, 
    int *distances,int* p_mfrontier_count)
{
    int testcount=0;
    #pragma omp parallel for schedule(dynamic,512)
    for (int i = 0; i < g->num_nodes; i++){
        if (distances[i] == NOT_VISITED_MARKER){
            int start_edge = g->incoming_starts[i];
            int end_edge = (i == g->num_nodes - 1) ? g->num_edges : g->incoming_starts[i + 1];

            *p_mfrontier_count+=(end_edge-start_edge);

            for (int neighbor = start_edge; neighbor < end_edge; neighbor++)
            {
                int incoming = g->incoming_edges[neighbor];
  
                if(bu_frontier->vertices[incoming]==1){
                    distances[i]=distances[incoming]+1;
                    bu_new_frontier->count++;
                    bu_new_frontier->vertices[i] = 1;
                    #pragma omp critical
                    {
                    int index=new_frontier->count++;
                    new_frontier->vertices[index]=i;
                    }
                    break;
                }
            }
            
        }
    }
}

void bfs_bottom_up(Graph graph, solution *sol)
{
    // For PP students:
    //
    // You will need to implement the "bottom up" BFS here as
    // described in the handout.
    //
    // As a result of your code's execution, sol.distances should be
    // correctly populated for all nodes in the graph.
    //
    // As was done in the top-down case, you may wish to organize your
    // code by creating subroutine bottom_up_step() that is called in
    // each step of the BFS process.
    vertex_set list1;
    vertex_set list2;
    vertex_set list3;
    vertex_set list4;
    vertex_set_init(&list1, graph->num_nodes);
    vertex_set_init(&list2, graph->num_nodes);
    vertex_set_init(&list3, graph->num_nodes);
    vertex_set_init(&list4, graph->num_nodes);

    vertex_set *frontier = &list1; // frontier in pseudocode
    vertex_set *new_frontier = &list2; // next in pseudocode
    vertex_set *bu_frontier = &list3; // frontier in pseudocode
    vertex_set *bu_new_frontier = &list4; // next in pseudocode

    bool bfs_top_down=true;
    int sum_mfrontier_count=0;
    int* p_mfrontier_count=&sum_mfrontier_count;    

    //initialize all nodes to NOT_VISITED
    #pragma omp parallel for
    for (int i = 0; i < graph->num_nodes; i++)
        sol->distances[i] = NOT_VISITED_MARKER;

    //setup frontier with the root node
    #pragma omp single
    {    
    frontier->vertices[frontier->count++] = ROOT_NODE_ID;
    bu_frontier->vertices[ROOT_NODE_ID]=1;
    sol->distances[ROOT_NODE_ID] = 0;
    bu_frontier->count++;
    }

    while (frontier->count != 0)
    {
// #define VERBOSE   1
#ifdef VERBOSE
        double start_time = CycleTimer::currentSeconds();
#endif

        vertex_set_clear(new_frontier);
        vertex_set_clear(bu_new_frontier);
        // top_down_step(graph, frontier, new_frontier, sol->distances);
        bottom_up_step(graph, frontier, new_frontier,bu_frontier,bu_new_frontier, sol->distances,p_mfrontier_count);

#ifdef VERBOSE
        double end_time = CycleTimer::currentSeconds();
        printf("frontier=%-10d %.4f sec\n", frontier->count, end_time - start_time);
#endif

        // swap pointers
        vertex_set *tmp = frontier;
        frontier = new_frontier;
        new_frontier = tmp;

        vertex_set *bu_tmp = bu_frontier;
        bu_frontier = bu_new_frontier;
        bu_new_frontier = bu_tmp;

    }
}

void bfs_hybrid(Graph graph, solution *sol)
{
    // For PP students:
    //
    // You will need to implement the "hybrid" BFS here as
    // described in the handout.
    int alpha=14,beta=24;
    vertex_set list1;
    vertex_set list2;
    vertex_set list3;
    vertex_set list4;
    vertex_set_init(&list1, graph->num_nodes);
    vertex_set_init(&list2, graph->num_nodes);
    vertex_set_init(&list3, graph->num_nodes);
    vertex_set_init(&list4, graph->num_nodes);

    vertex_set *frontier = &list1; // frontier in pseudocode
    vertex_set *new_frontier = &list2; // next in pseudocode
    vertex_set *bu_frontier = &list3; // frontier in pseudocode
    vertex_set *bu_new_frontier = &list4; // next in pseudocode

    bool bfs_top_down=true;
    int sum_mfrontier_count=0;
    int* p_mfrontier_count=&sum_mfrontier_count;
    int total_mfrontiersum=0;

    //initialize all nodes to NOT_VISITED
    #pragma omp parallel for
    for (int i = 0; i < graph->num_nodes; i++)
        sol->distances[i] = NOT_VISITED_MARKER;

    //setup frontier with the root node
    #pragma omp single
    {    
    frontier->vertices[frontier->count++] = ROOT_NODE_ID;
    bu_frontier->vertices[ROOT_NODE_ID]=1;
    sol->distances[ROOT_NODE_ID] = 0;
    bu_frontier->count++;
    }

    while (frontier->count != 0)
    {
// #define VERBOSE   1
#ifdef VERBOSE
        double start_time = CycleTimer::currentSeconds();
#endif
        total_mfrontiersum+=sum_mfrontier_count;
        if(sum_mfrontier_count>(graph->num_edges-total_mfrontiersum)/alpha && new_frontier->count<frontier->count) bfs_top_down=false;
        if(frontier->count< graph->num_nodes/beta && new_frontier->count>frontier->count)bfs_top_down=true; 
        sum_mfrontier_count=0;
        vertex_set_clear(new_frontier);
        vertex_set_clear(bu_new_frontier);
        // top_down_step(graph, frontier, new_frontier, sol->distances);
        if (bfs_top_down)
        top_down_step(graph, frontier, new_frontier,bu_frontier,bu_new_frontier, sol->distances,p_mfrontier_count);
        else
        bottom_up_step(graph, frontier, new_frontier,bu_frontier,bu_new_frontier, sol->distances,p_mfrontier_count);

#ifdef VERBOSE
        double end_time = CycleTimer::currentSeconds();
        printf("frontier=%-10d %.4f sec\n", frontier->count, end_time - start_time);
#endif

        // swap pointers
        vertex_set *tmp = frontier;
        frontier = new_frontier;
        new_frontier = tmp;

        vertex_set *bu_tmp = bu_frontier;
        bu_frontier = bu_new_frontier;
        bu_new_frontier = bu_tmp;

    }
}