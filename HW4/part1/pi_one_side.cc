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

    MPI_Win win;

    // TODO: MPI init
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
        double distance=x*x+y*y;
        if (distance<=1.0){
            localCount++;
        }
    }

    if (world_rank == 0)
    {
        // Master
        long long int  spaceToStore;
        MPI_Alloc_mem(sizeof(long long int), MPI_INFO_NULL, &count);
        count = localCount;
        // Create a window. Set the displacement unit to sizeof(int) to simplify
        // the addressing at the originator processes
        MPI_Win_create(&count,sizeof(long long int), sizeof(long long int), MPI_INFO_NULL,
           MPI_COMM_WORLD, &win);
    }else
    {
        // Workers
        // Worker processes do not expose memory in the window
        MPI_Win_create(NULL, 0, 1, MPI_INFO_NULL, MPI_COMM_WORLD, &win);

        // Register with the master
        MPI_Win_lock(MPI_LOCK_EXCLUSIVE, 0, 0, win);
        // MPI_Put(&localCount, 1, MPI_UNSIGNED_LONG, 0, world_rank, 1, MPI_UNSIGNED_LONG, win);
        MPI_Accumulate(&localCount, 1, MPI_LONG_LONG_INT, 0, 0, 1, MPI_LONG_LONG_INT, MPI_SUM,win);
        // &my_rank, 1, MPI_INT, 0, 0, 1, MPI_INT, MPI_SUM, window
        MPI_Win_unlock(0, win);

    }

    MPI_Win_free(&win);

    if (world_rank == 0)
    {
        // TODO: handle PI result
        pi_result = 4 * count / (double) tosses;

        // --- DON'T TOUCH ---
        double end_time = MPI_Wtime();
        printf("%lf\n", pi_result);
        printf("MPI running time: %lf Seconds\n", end_time - start_time);
        // ---
    }
    
    MPI_Finalize();
    return 0;
}