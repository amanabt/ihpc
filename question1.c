#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<math.h>

int main( int argc, char** argv )
{
    int i,j,k,l,n,m;
    int rank,nop,index;
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


	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&nop);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

 	
	if(rank==0)
	{
		for(k=0;k<n;k=k+2){
			for(l=0;l<nop;l++){
			
				index=k
				int* result=(int *)malloc(sizeof(int)*m*m);
				int* result=(int *)malloc(sizeof(int)*m);
				MPI_Send(&m,1,MPI_INT,l+1,0,MPI_COMM_WORLD);
				MPI_Send(&n,1,MPI_INT,l+1,1,MPI_COMM_WORLD);
				MPI_Send(&index,1,MPI_INT,l+1,2,MPI_COMM_WORLD);
				MPI_Send(A,m*m*n,MPI_INT,l+1,3,MPI_COMM_WORLD);
		
				MPI_Recv(temp,m,MPI_INT,l,i,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				for(j=0;j<m;j++){
					result[l+j*m]=temp[j];
				}
			}
		}		
	}

	else
	{	

		int* org;
		int n,m,index;
		MPI_Recv(&n,1,MPI_INT,0,0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&m,1,MPI_INT,0,1,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&index,1,MPI_INT,0,2,MPI_COMM_WORLD, MPI_STATUS_IGNORE);

		org=(int*)malloc(n*m*n*sizeof(int *));
		MPI_Recv(org,size,MPI_INT,0,3,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	
		int* result=(int *)malloc(sizeof(int)*m);

		for(i=0;i<m;i++){
			for(j=0;j<m;j++){
				result[i]+=org[index*n+i*m+j]*org[(index+1)*n+j*m+(rank-1)*m];
			}
		}			

		MPI_Send(result,m,MPI_INT,0,0,MPI_COMM_WORLD);
		
	}

	free(A);
	MPI_Finalize();

	return 0;

}