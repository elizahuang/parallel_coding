#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <cmath>

int main(int argc, char **argv)
{
    // --- DON'T TOUCH ---
    MPI_Init(&argc, &argv);
    double start_time = MPI_Wtime();
    double pi_result;
    long long int tosses = atoi(argv[1]);
    int world_rank, world_size;
    // ---

    // TODO: MPI init
    MPI_Comm_rank(MPI_COMM_WORLD,&world_rank);
    MPI_Comm_size(MPI_COMM_WORLD,&world_size);
    MPI_Status status;
    long long int numTaskPer=tosses/world_size;
    int SEED;
    SEED = (int)time(NULL);
    int tag=0;
    long long int count =0;
    int numReduceIters=log2(world_size);
    int logOfTotal=numReduceIters;

    unsigned int seed =world_rank*SEED;
    srand(seed); 
    // unsigned 
    int dest=0;
    long long int localCount=0;

    for (long long int tossInd=0; tossInd<numTaskPer;tossInd++){
        double x=(double)rand_r(&seed)/RAND_MAX;
        double y=(double)rand_r(&seed)/RAND_MAX;
        // printf("rank %d : %d,%d\n", world_rank, x,y);
        double distance=x*x+y*y;
        if (distance<=1.0){
            localCount++;
        }
    }

    // TODO: binary tree redunction
    //numReduceIters
    while(numReduceIters>0){ //4,3,2,1
        int reduceStart=pow(2,logOfTotal-numReduceIters);
        int loopDist=pow(2,logOfTotal-numReduceIters+1);
        for(int i=reduceStart;i<=world_size-1;i+=loopDist){
            if (world_rank==i){
                dest=world_rank-reduceStart;
                MPI_Send(&localCount,1,MPI_UNSIGNED_LONG,dest,tag,MPI_COMM_WORLD);
                break;
            } 
        }
        // MPI_Barrier(MPI_COMM_WORLD);
        for(int i=0;i<world_size-1;i+=loopDist){
            if (world_rank==i){
                // printf("numReduceIters: %d\n",numReduceIters);
                long long int buffer;
                MPI_Recv(&buffer, 1, MPI_UNSIGNED_LONG, world_rank+reduceStart, tag, MPI_COMM_WORLD, &status);
                localCount+=buffer;
                break;
            }           
        }
        // MPI_Barrier(MPI_COMM_WORLD);        
        numReduceIters-=1;
    }

    if (world_rank == 0)
    {
        // TODO: PI result
        count=localCount;
        pi_result=4*(double)count/(double)tosses;

        // --- DON'T TOUCH ---
        double end_time = MPI_Wtime();
        printf("%lf\n", pi_result);
        printf("MPI running time: %lf Seconds\n", end_time - start_time);
        // ---
    }

    MPI_Finalize();
    return 0;
}
