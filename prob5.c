#include <mpi.h>
#include <math.h>

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

int **allocate_2d_matrix (int m, int n)
{
  int *linear, **mat;
  int i;
 
  linear = malloc (sizeof (int) * m * n);
  mat = malloc (sizeof (int *) * m);
  for (i = 0; i < m; i++)
  {
    mat[i] = &linear[i*n];
  }
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
	char* results;
	const int param = 4;
		
	ec_ = MPI_Init (&argc, &argv);
	
	if (ec_ != MPI_SUCCESS)
		MPI_Abort (MPI_COMM_WORLD, ec_);
	
	MPI_Comm_size (MPI_COMM_WORLD, &size_);
	MPI_Comm_rank (MPI_COMM_WORLD, &rank_);
	
	if (rank_ == MPI_MASTER)
		scanf ("%d", &N);
	
	for (int n = 0; n < N; ++n)
		scanf ("%d", &M);
	
	MPI_Finalize();
}
