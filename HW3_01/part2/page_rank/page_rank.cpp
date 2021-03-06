#include "page_rank.h"

#include <stdlib.h>
#include <cmath>
#include <omp.h>
#include <utility>

#include "../common/CycleTimer.h"
#include "../common/graph.h"

// pageRank --
//
// g:           graph to process (see common/graph.h)
// solution:    array of per-vertex vertex scores (length of array is num_nodes(g))
// damping:     page-rank algorithm's damping parameter
// convergence: page-rank algorithm's convergence threshold
//
void pageRank(Graph g, double *solution, double damping, double convergence)
{

  // initialize vertex weights to uniform probability. Double
  // precision scores are used to avoid underflow for large graphs
  /*
  int numNodes = num_nodes(g);
  double equal_prob = 1.0 / numNodes;
  for (int i = 0; i < numNodes; ++i)
  {
    solution[i] = equal_prob;
  }*/

  int numNodes = num_nodes(g);
  double even_prob = 1.0 / numNodes, sum_no_out_bound = 0.0;
  #pragma omp parallel for reduction(+:sum_no_out_bound)
  for (int i = 0; i < numNodes; ++i)
  {
    solution[i] = even_prob;
    if(outgoing_size(g,i) == 0){
      sum_no_out_bound+= solution[i];
    }
  }
  /*
     For PP students: Implement the page rank algorithm here.  You
     are expected to parallelize the algorithm using openMP.  Your
     solution may need to allocate (and free) temporary arrays.

     Basic page rank pseudocode is provided below to get you started:

     // initialization: see example code above
     score_old[vi] = 1/numNodes;

     while (!converged) {

       // compute score_new[vi] for all nodes vi:
       score_new[vi] = sum over all nodes vj reachable from incoming edges
                          { score_old[vj] / number of edges leaving vj  }
       score_new[vi] = (damping * score_new[vi]) + (1.0-damping) / numNodes;

       score_new[vi] += sum over all nodes v in graph with no outgoing edges
                          { damping * score_old[v] / numNodes }

       // compute how much per-node scores have changed
       // quit once algorithm has converged

       global_diff = sum over all nodes vi { abs(score_new[vi] - score_old[vi]) };
       converged = (global_diff < convergence)
     }

   */

    bool converge = false;
    double *solution_new = (double*) calloc(numNodes, sizeof(double));
    double num_out_bound, sum_leave_vj, global_diff = 0.0;
    while(!converge){
      //fprintf(stderr, "not conv\n");
      // #pragma omp parallel for private(num_out_bound, sum_leave_vj)
      #pragma omp parallel for private(sum_leave_vj)      
      for(int i = 0 ; i < numNodes ; ++i){
        solution_new[i] = 0.0;
        // num_out_bound = 0.0;
        sum_leave_vj = 0.0;

        const Vertex *start = incoming_begin(g, i);
        const Vertex *end = incoming_end(g, i);

        for (const Vertex *vj = start ; vj != end ; vj++){
          // num_out_bound = outgoing_size(g, *vj);
          // sum_leave_vj += solution[*vj]/num_out_bound;
          sum_leave_vj += solution[*vj]/outgoing_size(g, *vj);
        }	

        solution_new[i] = (damping * sum_leave_vj) + (1.0 - damping)/numNodes;
        solution_new[i] += damping * sum_no_out_bound / numNodes;
      }
    
      global_diff = 0.0;
      sum_no_out_bound = 0.0;
      #pragma omp parallel for reduction(+:global_diff, sum_no_out_bound)
      for(int i = 0 ; i < numNodes ; ++i){
        global_diff += fabs(solution_new[i] - solution[i]);
        solution[i] = solution_new[i];
        if(outgoing_size(g,i) == 0){
          sum_no_out_bound += solution_new[i];
        }

      }

      converge = (global_diff < convergence);
    }

}
