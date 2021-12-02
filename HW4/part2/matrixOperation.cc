# include <stdio.h>
# include <stdlib.h>
# include <mpi.h>

# define MASTER 0
# define FROM_MASTER 1
# define FROM_WORKER 2

// Read size of matrix_a and matrix_b (n, m, l) and whole data of matrixes from stdin
//
// n_ptr:     pointer to n
// m_ptr:     pointer to m
// l_ptr:     pointer to l
// a_mat_ptr: pointer to matrix a (a should be a continuous memory space for placing n * m elements of int)
// b_mat_ptr: pointer to matrix b (b should be a continuous memory space for placing m * l elements of int)
void construct_matrices(int *n_ptr, int *m_ptr, int *l_ptr, int **a_mat_ptr, int **b_mat_ptr){
    int size, rank;
    int *ptr;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == MASTER){
    // printf("Input matrix size:\n");
	scanf("%d %d %d", n_ptr, m_ptr, l_ptr);
    }
	int n = *n_ptr, m = *m_ptr, l = *l_ptr;
	MPI_Bcast(n_ptr, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(m_ptr, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(l_ptr, 1, MPI_INT, 0, MPI_COMM_WORLD);    

	*a_mat_ptr = (int*)malloc(sizeof(int) * (*n_ptr)*(*m_ptr));
	*b_mat_ptr = (int*)malloc(sizeof(int) *(*m_ptr)*(*l_ptr));

    if (rank == MASTER){
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
            ptr = *a_mat_ptr + i * m + j;
            scanf("%d", ptr);
            }
        }

        for (int i = 0; i < m; i++){
            for (int j = 0; j < l; j++){
            ptr = *b_mat_ptr + i * l + j;
            scanf("%d", ptr);
            }
        }
    }
	MPI_Bcast(*a_mat_ptr, (*n_ptr)*(*m_ptr), MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(*b_mat_ptr, (*m_ptr)*(*l_ptr), MPI_INT, 0, MPI_COMM_WORLD);
	/* debug purpose */
	// for (int i = 0; i < n; i++){
	//     for (int j = 0; j < m; j++){
	// 	ptr = *a_mat_ptr + i * m + j;
	// 	printf("%d ", *ptr);
	//     }
	//     printf("\n");
	// }

	// for (int i = 0; i < m; i++){
	//     for (int j = 0; j < l; j++){
	// 	ptr = *b_mat_ptr + i * l + j;
	// 	printf("%d ", *ptr);
	//     }
	//     printf("\n");
	// }   

}


// Just matrix multiplication (your should output the result in this function)
//
// n:     row number of matrix a
// m:     col number of matrix a / row number of matrix b
// l:     col number of matrix b
// a_mat: a continuous memory placing n * m elements of int
// b_mat: a continuous memory placing m * l elements of int
void matrix_multiply(const int n, const int m, const int l, const int *a_mat, const int *b_mat){
	int world_rank, world_size;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	int *C, *ans;
	int len, start, end;
	len = n*l;
	start = (len/world_size)*world_rank;
	end = start+(len/world_size);

	if (world_rank == world_size-1){
		end = len;
	}

	C = (int*)calloc(len, sizeof(int));
	ans = (int*)calloc(len, sizeof(int));
 
    for(int i=start; i<end;i++){
        int c_y=i%l;
        int c_x=i/l;
        int sum=0;
        for(int multi_ind=0;multi_ind<m;multi_ind++){
            sum+=a_mat[c_x*m+multi_ind]*b_mat[multi_ind*l+c_y];
        }
        C[i]=sum;
    }

	MPI_Reduce(C, ans, len, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	if(world_rank == 0){
        // printf("\nOutput:\n");
		for(int i = 0 ; i < n ; i++){
			for(int j = 0 ; j < l ; j++){
				// if(j) putchar(' ');
				// printf("%d", ans[i*l+j]);
				printf("%d", ans[i*l+j]);
				putchar(' ');
                // if(j == l-1)
                //     printf("%d", ans[i*l+j]);
                // else
                //     printf("%d ", ans[i*l+j]);
			}
			putchar('\n');
            // printf("\n");
		}
	}
}

// Remember to release your allocated memory
void destruct_matrices(int *a_mat, int *b_mat){
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == MASTER){
        free(a_mat);
        free(b_mat);
    }
}