#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    // --- DON'T TOUCH ---
    MPI_Init(&argc, &argv);
    double start_time = MPI_Wtime();
    double pi_result;
    long long int tosses = atoi(argv[1]);
    int world_rank, world_size;
    // ---

    // TODO: init MPI
    MPI_Comm_rank(MPI_COMM_WORLD,&world_rank);
    MPI_Comm_size(MPI_COMM_WORLD,&world_size);
    MPI_Status status;
    long long int numTaskPer=tosses/world_size;
    int SEED;
    SEED = (int)time(NULL);
    int tag=0;
    long long int count =0;

    unsigned int seed =world_rank*SEED;
    // printf("rank %d :,seed: %d\n",world_rank,seed);
    srand(seed); 
    unsigned int dest=0;
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

    if (world_rank > 0)
    {
        // TODO: handle workers
        MPI_Send(&localCount,1,MPI_UNSIGNED_LONG,dest,tag,MPI_COMM_WORLD);
    }
    else if (world_rank == 0)
    {
        // TODO: master
        count=localCount;
        long long int buffer;
        for(int sendSource=1;sendSource<world_size;sendSource++){
            MPI_Recv(&buffer, 1, MPI_UNSIGNED_LONG, sendSource, tag, MPI_COMM_WORLD, &status);
            count+=buffer;
        }
    }

    if (world_rank == 0)
    {
        // TODO: process PI result
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
