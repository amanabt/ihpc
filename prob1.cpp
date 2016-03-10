#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

// N = number of Matrices 
// M = total number of elements in matrices

enum {
	MATRICES,
	SIZE,
	DATA,
	__END__
};

int* alloc_1d (int N, int M)
{
	int *data = (int*)malloc(M * M * N * sizeof(int));
// 	printf ("allocated\n");
	return data;
}

// void read (int* A, int N, int M)
// {
// 	for (int i = 0; i < N; ++i) {
// 		for (int j = 0; j < M; ++j) {
// 			for (int k = 0; k < M; ++k)
// 				scanf ("%d", &A [(j * M + k) + (i * M * M)]);
// 			scanf ("\n");
// 		};
// 		scanf ("\n");
// 	}
// }
	
int main (int argc, char** argv)
{
	int N;
	int M;
	int rank_;
	int size_;
	int ec_;
	const int MPI_MASTER = 0;
	int* A;
	
	ec_ = MPI_Init (&argc, &argv);
	
	if (ec_ != MPI_SUCCESS)
		MPI_Abort (MPI_COMM_WORLD, ec_);
	
	MPI_Comm_size (MPI_COMM_WORLD, &size_);
	MPI_Comm_rank (MPI_COMM_WORLD, &rank_);
	
	if (rank_ == MPI_MASTER) {
		scanf ("%d\n%d", &N, &M);
	}
	
	if (rank_ == MPI_MASTER) {
		for (int rank = 1; rank < size_; ++rank) {
			MPI_Send (&N, 1, MPI_INT, rank, MATRICES, MPI_COMM_WORLD);
			MPI_Send (&M, 1, MPI_INT, rank, SIZE, MPI_COMM_WORLD);
// 			MPI_Send (A, M * M * N, MPI_INT, rank, DATA, MPI_COMM_WORLD);
		}
	}

	else {
	MPI_Recv (&N,
				1,
				MPI_INT,
				MPI_MASTER,
				MATRICES,
				MPI_COMM_WORLD,
				MPI_STATUS_IGNORE);
	
	MPI_Recv (&M,
				1,
				MPI_INT,
				MPI_MASTER,
				SIZE,
				MPI_COMM_WORLD,
				MPI_STATUS_IGNORE);
	
	printf ("%d : %d : %d\n", rank_, N, M);
	}
	
	A = alloc_1d (N, M);
	
	if (rank_ == MPI_MASTER) {
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < M; ++j) {
				for (int k = 0; k < M; ++k)
					scanf ("%d", &A [(j * M + k) + (i * M * M)]);
// 				printf ("\n");
			};
// 			printf ("\n");
		}
		for (int i = 0; i < N * M * M; ++i)
			printf ("%d ", A[i]);
	}
	
	if (rank_ == MPI_MASTER)
		for (int i = 1; i < size_; ++i)
			MPI_Send(A, M * M * N, MPI_INT, i, DATA, MPI_COMM_WORLD);
		
	if (rank_ != MPI_MASTER) {
		MPI_Recv (A,
				  M * M * N,
				  MPI_INT,
				  MPI_MASTER,
				  DATA,
				  MPI_COMM_WORLD,
				  MPI_STATUS_IGNORE);
		for (int i = 0; i < N * M * M; ++i)
			printf ("%d ", A[i]);
	}
	
	

	MPI_Finalize();
	exit (0);
}































// // 	Divyat's Code
// 
// 	if(rank_==0)
// 	{
// 		int* temp = (int*)malloc(M * sizeof(int));
// 		for(int k=0;k<N;k=k+2){
// 			for(int l=0;l<size_;++l){
// 			
// 				
// 				int* result=(int *)malloc(sizeof(int)*M*M);
// 				MPI_Send(&k,1,MPI_INT,l+1,2 + __END__,MPI_COMM_WORLD);
// 		
// 				MPI_Recv(temp,M,MPI_INT,l,l + 1 +__END__,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
// 				for(int j=0;j<M;j++){
// 					result[l+j*M]=temp[j];
// 				}
// 			}
// 		}		
// 	}
// 
// 	else
// 	{	
// 		int index;
//         MPI_Recv(&index,1,MPI_INT,0,2 + __END__,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
// 	
// 		int* result=(int *)malloc(sizeof(int)*M);
// 
// 		for(int i=0;i<M;i++){
// 			for(int j=0;j<M;j++){
// 				result[i]+=A[index*N+i*M+j]*A[(index+1)*N+j*M+(rank_-1)*M];
// 			}
// 		}
// 
// 		MPI_Send(result,M,MPI_INT,0,rank_+__END__,MPI_COMM_WORLD);
// 	}
















// // 	printf ("%d", rank_);
// // 	if (rank_ == 0)
// // 		printf ("%d", rank_);
// // 	if (rank_ == MPI_MASTER)
// // 	printf ("%d %d", N, M);
// 
// printf("Enter the number\n");
// scanf("%d",&M);
// 
// printf("%d\n",M);
// 		
// 		
// 		
// 		
// // 	
// 	if (rank_ == MPI_MASTER) {
// 		for (int rank = 1; rank < nop_; ++rank) {
// 			MPI_Send (&M, 1, MPI_INT, rank, MATRICES, MPI_COMM_WORLD);
// 			MPI_Send (&N, 1, MPI_INT, rank, SIZE, MPI_COMM_WORLD);
// 			MPI_Send (A, M * M * N, MPI_INT, rank, DATA, MPI_COMM_WORLD);
// 		}
// 	}
// // 		
// 	else {
// 		MPI_Recv (&N,
// 				  1,
// 				  MPI_INT,
// 				  MPI_MASTER,
// 				  MATRICES,
// 				  MPI_COMM_WORLD,
// 				  MPI_STATUS_IGNORE);
// 		
// 		MPI_Recv (&M,
// 				  1,
// 				  MPI_INT,
// 				  MPI_MASTER,
// 				  SIZE,
// 				  MPI_COMM_WORLD,
// 				  MPI_STATUS_IGNORE);
// // 		
// 		MPI_Recv (A,
// 				  M * M * N,
// 				  MPI_INT,
// 				  MPI_MASTER,
// 				  DATA,
// 				  MPI_COMM_WORLD,
// 				  MPI_STATUS_IGNORE);
// // 	printf ("%d %d", M, N);
// // 	}
// // 	






















// 	MPI_Init(&argc, &argv);
// MPI_Comm_size(MPI_COMM_WORLD, &size_);
// MPI_Comm_rank(MPI_COMM_WORLD, &rank_);
// printf("Enter the number\n");
// scanf("%d",&M);
// 
// printf("%d\n",M);
// MPI_Finalize();
// exit(0);
































// 	int **A;
// 	const int N = 2, M = 2;
// 	const int master_ = 0;
// 	int ec, rank_, 
// 	A = alloc_2d_init(2,2);
// 	
// 	ec = MPI_Init (argc&, argv&);
// 	
// 	if (ec != MPI_SUCCESS)
// 		MPI_Abort (MPI_COMM_WORLD, ec);
// 	
// 	MPI_Send (&(A[0][0]), N * M, MPI_INT, 1, 0, MPI_COMM_WORLD);

// int **alloc_2d_int(int rows, int cols) {
//     int *data = (int *)malloc(rows*cols*sizeof(int));
//     int **array= (int **)malloc(rows*sizeof(int*));
//     for (int i=0; i<rows; i++)
//         array[i] = &(data[cols*i]);
// 
//     return array;
// }
