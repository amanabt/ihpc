#include<stdio.h>
#include<mpi.h>
#include<math.h>

int main( int argc, char** argv )
{
    int i,temp1,temp2,temp3,temp0,ans,rank,size;
    int A[6];
    for(i=0;i<6;i++){
    	A[i]=i+1;
    }
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	if(rank==0)
	{
		
		ans=1;
		for(i=1;i<=3;i++){
			
			MPI_Recv(&temp0,1,MPI_INT,i,i-1,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			ans=ans*temp0;
		}	
		
		printf("%d\n",ans);		
	}

	if(rank==1)
	{	
		temp1=A[0]*A[1];
		MPI_Send(&temp1,1,MPI_INT,0,0,MPI_COMM_WORLD);
		
	}

	if(rank==2)
	{	
		temp2=A[2]*A[3];
		MPI_Send(&temp2,1,MPI_INT,0,1,MPI_COMM_WORLD);
		
	}

	if(rank==3)
	{	
		temp3=A[4]*A[5];
		MPI_Send(&temp3,1,MPI_INT,0,2,MPI_COMM_WORLD);
		
	}

	MPI_Finalize();

	return 0;


}