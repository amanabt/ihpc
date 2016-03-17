#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<math.h>

int main( int argc, char** argv )
{
    int i,j,k,n,m;
    int rank,size;
    scanf("%d",&n);
    scanf("%d",&m);
    int*** A;

    A=(int ***)malloc(n*sizeof(int **)); 
    for(k=0;k<n;k++){
    	A[k]=(int **)malloc(m*sizeof(int*));	
    }
    for(k=0;k<n;k++){
    	for(i=0;i<m;i++){
    		A[k][i]=(int *)malloc(m*sizeof(int));
    	} 
    }
    
    for(k=0;k<n;k++){
    	for(i=0;i<m;i++){
    		for(j=0;j<m;j++){
    			scanf("%d",&A[k][i][j]);
    		}    	
    	}
    }

/*
    for(k=0;k<n;k++){
    	for(i=0;i<m;i++){
    		for(j=0;j<m;j++){
    			printf("%d ",A[k][i][j]);
    		}    	
    		printf("\n");
    	}
    	printf("\n");
    	printf("\n");
    }
 */	

	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

 	
	if(rank==0)
	{

		MPI_Send(&m,1,MPI_INT,1,0,MPI_COMM_WORLD);

//		MPI_Send(A[0],m*m,MPI_INT**,1,0,MPI_COMM_WORLD);
					
//			MPI_Recv(&temp0,1,MPI_INT,i,i-1,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}

	if(rank==1)
	{	

		int** org;

		int size;
	///	temp1=A[0]*A[1];
		MPI_Recv(&size,1,MPI_INT,0,0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("%d",size);

//		MPI_Recv(org,size,MPI_INT**,0,0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
//		printf("%d",org[0][0]);

	//	MPI_Send(&temp1,1,MPI_INT,0,0,MPI_COMM_WORLD);
		
	}
/*
	if(rank==2)
	{	
		temp2=A[2]*A[3];
		MPI_Send(&temp2,1,MPI_INT,0,1,MPI_COMM_WORLD);
		
	}

	if(rank==3)
	{	
		printf("%d\n", rank);
		temp3=A[4]*A[5];
		MPI_Send(&temp3,1,MPI_INT,0,2,MPI_COMM_WORLD);
		
	}

*/
	MPI_Finalize();

//	printf("%d\n", rank );
	return 0;


}