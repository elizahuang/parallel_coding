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
        // printf("rank %d : %d,%d\n", world_rank, x,y);
        double distance=x*x+y*y;
        if (distance<=1.0){
            localCount++;
        }
    }
    // TODO: use MPI_Gather
    long long int *recvbuffer;
    if (world_rank == 0){
	    recvbuffer = (long long int*)malloc(sizeof(long long int) * world_size);
    }
    MPI_Gather(&localCount, 1, MPI_UNSIGNED_LONG, recvbuffer, 1, MPI_UNSIGNED_LONG, 0, MPI_COMM_WORLD);

    if (world_rank == 0)
    {
        // TODO: PI result
        for (int i = 0; i < world_size; i++){
            count += recvbuffer[i];
        }
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
