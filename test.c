#include <stdlib.h>
#include <stdio.h>
#include "mpi.h"
#include<string.h>

enum {
	MATRICES,
	SIZE,
	DATA,
	__END__
};

int* alloc_1d (int N, int M)
{
	int *data = (int*)malloc(M * M * N * sizeof(int));
	return data;
}

void read (int* A, int N, int M)
{
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			for (int k = 0; k < M; ++k)
				scanf ("%d", &A [(j * M + k) + (i * M * M)]);
			scanf ("\n");
		};
		scanf ("\n");
	}
}

int main(int argc, char* argv[]) 
{
int M, N;

int size_, rank_;

MPI_Init(&argc, &argv);
MPI_Comm_size(MPI_COMM_WORLD, &size_);
MPI_Comm_rank(MPI_COMM_WORLD, &rank_);
printf("Enter the number\n");
scanf("%d %d",&M, &N);

if (rank_ == 0)
	printf("%d\n%d\n",M, N);
MPI_Finalize();
exit(0);
}
