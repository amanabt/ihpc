#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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
	int *data = (int*)malloc(M * M * 2*N * sizeof(int));
	
	return data;
}


	
int main (int argc, char** argv)
{	
	
	int N,i,k,j,l,t,p;
	int count=0;
	int M;
	int rank;
	int nop;
	int ec_;
	const int MPI_MASTER = 0;
	int* A;
	
	ec_ = MPI_Init (&argc, &argv);
	
	if (ec_ != MPI_SUCCESS)
		MPI_Abort (MPI_COMM_WORLD, ec_);
	
	MPI_Comm_size (MPI_COMM_WORLD, &nop);
	MPI_Comm_rank (MPI_COMM_WORLD, &rank);
	
	if (rank == MPI_MASTER) {
		scanf ("%d\n%d", &N, &M);
	}
	
	if (rank == MPI_MASTER) {
		for (int rank = 1; rank < nop; ++rank) {
			MPI_Send (&N, 1, MPI_INT, rank, MATRICES, MPI_COMM_WORLD);
			MPI_Send (&M, 1, MPI_INT, rank, SIZE, MPI_COMM_WORLD);

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
	
	
	}
	
	A = alloc_1d (N, M);
	
	if (rank == MPI_MASTER) {
		for (int i = 0; i < 2*N; ++i) {
			for (int j = 0; j < M; ++j) {
				for (int k = 0; k < M; ++k)
					scanf ("%d", &A [(j * M + k) + (i * M * M)]);
				
			}

		}
	}	
	
	if (rank == MPI_MASTER)
		for (int i = 1; i < nop; ++i)
			MPI_Send(A, M * M * 2*N, MPI_INT, i, DATA, MPI_COMM_WORLD);
		
	if (rank != MPI_MASTER) {
		MPI_Recv (A,
				  M * M *2* N,
				  MPI_INT,
				  MPI_MASTER,
				  DATA,
				  MPI_COMM_WORLD,
				  MPI_STATUS_IGNORE);
	}

	


//chappu code
	for(p=1;p<=N;p++)	
	{	
		int **c_p;
		c_p=(int **)malloc(M*sizeof(int*));
		for(k=0;k<M;k++)
		{
			*(c_p+k)=(int*)malloc(M*sizeof(int));
		}
	
	
		for(i=0;i<M;i++)
		{
			for(j=0;j<M;j++)
			{
				c_p[i][j]=0;
			}
		}
	
		for(k=1;k<=M/nop+1;k++)
		{	
			if(rank+nop*(k-1)<M)
			{
				for(i=0;i<M;i++)
				{	
					for(j=0;j<M;j++)
					{
						c_p[rank+nop*(k-1)][i]=c_p[rank+nop*(k-1)][i]+A[M*i+j+2*(p-1)*M*M]*A[M*j+rank+nop*(k-1)+M*M*(2*p-1)];
					}
				}
			}	
		
		
			
		}
	
		if(rank==0)

		{	
			if(nop<M)
		
			{	for(k=1;k<=M/nop+1;k++)
			
				{
			

					
					if(rank+nop*(k-1)<M)
					{	
				
						{	for(l=1;l<nop;l++)
							{	
							
								MPI_Recv(&c_p[l+nop*(k-1)][0],M,MPI_INT,l,l+k+nop*(k-1),MPI_COMM_WORLD,MPI_STATUS_IGNORE);	
							}
						}
				
				
					}
				}
			}
			else
			{	for(l=1;l<M;l++)
				{	
					 
					MPI_Recv(&c_p[l][0],M,MPI_INT,l,l+1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);	
				}
			}	
		}
		else
		{	if(nop<M)
		
			{	for(k=1;k<=M/nop+1;k++)
		
			{	
				if(rank+nop*(k-1)<M)

				{	
					MPI_Send(c_p[rank+nop*(k-1)],M,MPI_INT,0,rank+k+nop*(k-1),MPI_COMM_WORLD);
				}
				
			}		
			}
			else
			{
				if(rank<M)

				{	
					MPI_Send(c_p[rank],M,MPI_INT,0,rank+1,MPI_COMM_WORLD);
				}
			
			}
		}
	
		if(rank==0)
		{

			
				for(j=0;j<M;j++)
				{
					for(k=0;k<M;k++)
					{
						printf("%d ",c_p[k][j]);
					}
					printf("\n");
				}
				
				printf("\n");
			
		}
	


	}

	


	MPI_Finalize();
return 0;	
}






















