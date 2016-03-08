#include <stdio.h>
#include<mpi.h>
#include<math.h>

int main(int argc,char** argv)
{	
	int a,b,rank,size;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	if(rank==0)
	{
			
		MPI_Recv(&a,1,MPI_INT,1,0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		MPI_Recv(&b,1,MPI_INT,1,1,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("%d\n",a+b);		
	}
	if(rank==1)
	{	
		a=1;
		b=2;
		MPI_Send(&a,1,MPI_INT,0,0,MPI_COMM_WORLD);
		MPI_Send(&b,1,MPI_INT,0,1,MPI_COMM_WORLD);	
	}
	
	MPI_Finalize();

	return 0;
}