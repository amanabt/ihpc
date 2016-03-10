#include <mpi.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

enum
{
	CASES,
	DATA,
	RESULT,
	__END__
};

int* alloc_1d (int size)
{
	int *data = (int*)malloc(size * sizeof(int));
// 	printf ("allocated\n");
	return data;
}

int** allocate_2d_matrix (int m, int n)
{
	int *linear, **mat;
	int i;
	
	linear = malloc (sizeof (int) * m * n);
	mat = malloc (sizeof (int *) * m);
	for (i = 0; i < m; i++)
	{
		mat[i] = &linear[i*n];
	}
// 	printf ("allocated\n");
	return mat;
}


int main (int argc, char** argv)
{
	int N;
	int rank_;
	int size_;
	int ec_;
	const int MPI_MASTER = 0;
	int*** A;
	int* size;
	const int param = 4;
		
	ec_ = MPI_Init (&argc, &argv);
	
	if (ec_ != MPI_SUCCESS)
		MPI_Abort (MPI_COMM_WORLD, ec_);
	
	MPI_Comm_size (MPI_COMM_WORLD, &size_);
	MPI_Comm_rank (MPI_COMM_WORLD, &rank_);
	
	if (rank_ == MPI_MASTER) {
		scanf ("%d", &N);
		A = (int***) malloc (N * sizeof(int**));
		size = alloc_1d (N);

		for (int n = 0; n < N; ++n) {
			scanf ("%d", &size[n]);
			A[n] = allocate_2d_matrix (size[n], 4);
			
			for (int i = 0; i < size[n]; ++i) {
				for (int j = 0; j < 4; ++j) {
					scanf ("%d", &A[n][i][j]);
				}
			}
		}
		
		for (int n = 0; n < N; ++n)
		{
			for (int i = 0; i < size[n]; ++i) {
				for (int j = 0; j < 4; ++j) {
					printf ("%d \t", A[n][i][j]);
				}
				printf ("\n");
			}
			printf ("\n");
		}
	}
	
	if (rank_ == MPI_MASTER)
	{
		
		
	}
	
	if (rank_ == MPI_MASTER) {
		free (size);
		free (A);
	}
	MPI_Finalize();
}
