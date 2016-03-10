#include <mpi.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

enum
{
	CASES,
	DATA,
	RESULT,
	__END__
};

// int is_aligned (int A, int B, int C)
// {
// 	if (A + B == C) return 1;
// 	else if (B + C == A) return 1;
// 	else if (C + A == B) return 1;
// 	else return 0;
// }
// 
// unsigned int distance (int x1,
// 					   int y1,
// 					   int z1,
// 					   int x2,
// 					   int y2,
// 					   int z2,)
// {
// 	return sqrt ((x1 - x2) * (x1 - x2) + 
// 				 (y1 - y2) * (y1 - y2) + 
// 				 (z1 - z2) * (z1 - z2));
// }

char is_aligned (int u1, int u2, int u3, int v1, int v2, int v3)
{
	if ((u2 * v3 - u3 * v2) || (u1 * v3 - u3 * v1) || (u1 * v2 - v1 * u2))
		return (char)'n';
	
	return (char)'r';
}

int* alloc_1d (int size)
{
	int* data = (int*)malloc(size * sizeof(int));
	printf ("allocated\n");
	return data;
}

int main (int argc, char** argv)
{
	int N;
	int rank_;
	int size_;
	int ec_;
	const int MPI_MASTER = 0;
	int* A;
	char* results;
	
	ec_ = MPI_Init (&argc, &argv);
	
	if (ec_ != MPI_SUCCESS)
		MPI_Abort (MPI_COMM_WORLD, ec_);
	
	MPI_Comm_size (MPI_COMM_WORLD, &size_);
	MPI_Comm_rank (MPI_COMM_WORLD, &rank_);
	
	if (rank_ == MPI_MASTER)
		scanf ("%d", &N);
	
	for (int rank = 1; rank < size_; ++rank)
		MPI_Send (&N, 1, MPI_INT, rank, CASES, MPI_COMM_WORLD);

	if (rank_ == 0)
		A = alloc_1d (((N / size_) + (N % size_ > rank_)) * 9);

	if (rank_ != MPI_MASTER)
		results = (char*)malloc((N / size_ + (N % size_ > rank_)) * sizeof(char));
	
	else 
		results = (char*)malloc(N * sizeof(char));
	
	if (rank_ == MPI_MASTER) {
		int* temp;
		temp = alloc_1d (9);
		
		for (int j = 0; j < ((N / size_) + (N % size_ > rank_)) * 9; ++j) {
			scanf ("%d", &A[j]);
		}
// 		for (int i = 0; i < 9; ++i) printf ("%d", A[i]);
		
		for (int rank = 1; rank < size_; ++rank) {
			for (int i = 0; i < (N / size_ + (N % size_ > rank)); ++i) {
				for (int j = 0; j < 9; ++j) {
					scanf ("%d", &temp [j]);
				}
// 				for (int i = 0; i < 9; ++i) printf ("%d ", temp [i]);
				MPI_Send (temp, 9, MPI_INT, rank, DATA, MPI_COMM_WORLD);
// 				printf ("Sent %d \n", rank);
			}
		}
		free (temp);
	}
	
	if (rank_ != MPI_MASTER) {
		MPI_Recv (&N,
				  1,
				  MPI_INT,
				  MPI_MASTER,
				  CASES,
				  MPI_COMM_WORLD,
				  MPI_STATUS_IGNORE);
		int tmp = (N / size_) + (N % size_ > rank_);
		A = alloc_1d (tmp * 9);
// 		printf ("%d\n", tmp * 9);
		
		for (int cases = 0; cases < (N / size_ + (N % size_ > rank_)); ++cases) {
			MPI_Recv (A + (cases * 9),
					  9,
					  MPI_INT,
					  MPI_MASTER,
					  DATA,
					  MPI_COMM_WORLD,
					  MPI_STATUS_IGNORE);
				for (int j = 0; j < ((N / size_) + (N % size_ > rank_)) * 9; ++j) {
					scanf ("%d", &A[j]);
				}
		}
	}
	
// 	int len[3];
	int u1, u2, u3, v1, v2, v3;
	for (int i = 0; i < ((N / size_) + (N % size_ > rank_)); ++i) {
			u1 = A [i * 9 + 0] - A [i * 9 + 3];
			u2 = A [i * 9 + 1] - A [i * 9 + 4];
			u3 = A [i * 9 + 2] - A [i * 9 + 5];
			v1 = A [i * 9 + 6] - A [i * 9 + 3];
			v2 = A [i * 9 + 7] - A [i * 9 + 4];
			v3 = A [i * 9 + 8] - A [i * 9 + 5];
			results[i] = is_aligned (u1, u2, u3, v1, v2, v3);
// 			printf ("%c:%d ", results[i], rank_);
	}
	
	if (rank_ != MPI_MASTER)
	{
		MPI_Send (results,
				  (N / size_) + (N % size_ > rank_),
				  MPI_INT,
				  0,
				  rank_ + __END__,
				  MPI_COMM_WORLD);
// 		for (int i = 0; i < (N / size_) + (N % size_ > rank_); ++i)
// 			printf ("Sent: %d : %c\n", rank_, results[i]);
	}
	
	else {
		int flag = N / size_ + ((N % size_) > 0);
		for (int rank = 1; rank < size_; ++rank) {
			char* temp = 
				(char*) malloc ((N / size_ + (N % size_ > rank)) * sizeof(char));
			int count = N / size_ + (N % size_ > rank);
			
			MPI_Recv (&temp[0],
					  count,
					  MPI_INT,
					  rank,
					  rank + __END__,
					  MPI_COMM_WORLD,
					  MPI_STATUS_IGNORE);
// 			printf ("Received: %d\n", rank);
// 			for (int j = 0; j < count; ++j)
// 				printf ("Printing Temp : %d : %c \n", rank, temp[j]);
			for (int j = 0; j < count; ++j) {
					results [flag++] = temp [j];
// 				printf ("results %d %c %d %c\n", rank * count + j + (N % size_ > rank), results[rank * count + j + (N % size_ > rank)], j, temp [j]);
			}
			
			free (temp);
	}
	
	for (int i = 0; i < N; ++i)
		printf ("%c\n", results[i]);
// 	printf ("\n");
	}
	
	free (A);
	
	MPI_Finalize();
}
	
	

// 	if (rank_ == MPI_MASTER) {
// 		for (int i = 0; i < (N / size_ + (N % size_ > rank_)); ++i)
// 			for (int j = 0; j < 9; ++j)
// 				printf ("%d ", A[j + (i * 9)]);
// 	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
// 	if (rank_ == MPI_MASTER) {
// 		for (int rank = 1; rank < size_; ++rank) {
// 			MPI_Send (&N, 1, MPI_INT, rank, CASES, MPI_COMM_WORLD);
// 		}
// 	}
// 
// 	else {
// 	MPI_Recv (&N,
// 			  1,
// 			  MPI_INT,
// 			  MPI_MASTER,
// 			  MATRICES,
// 			  MPI_COMM_WORLD,
// 			  MPI_STATUS_IGNORE);
// 	
// 	MPI_Recv (&M,
// 			  1,
// 			  MPI_INT,
// 			  MPI_MASTER,
// 			  SIZE,
// 			  MPI_COMM_WORLD,
// 			  MPI_STATUS_IGNORE);
// 	
// 	printf ("%d : %d : %d\n", rank_, N, M);
