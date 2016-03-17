
#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>


int **A;

int prime(int x)
{	
	int b=0;
	b=(double)x;
	double c=sqrt(b);
	double j;
	if(b==1){
	   return 0;	
	}

	for(j=2;j<=c;j++)
	{
		if(b%(int)j==0)
			{	break;}
	}
	if(j>c){
		return 1;
	}
	else{
		return 0;
	}
	return 0;
}

int main(int argc,char** argv)
{
	int N,nop,rank,k,M;
	int i,j,l,y;
	scanf("%d",&N);	

	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&nop);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	
//Functions For sending data
	if(rank==0)
	{	
		for(k=1;k<nop;k++)
		{
			MPI_Send(&N,1,MPI_INT,k,0,MPI_COMM_WORLD);
		}	
	}
	else
	{
			MPI_Recv(&N,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	}

	if(rank==0)
	{	
		for(l=1;l<nop;l++)
		{
			MPI_Send(&M,1,MPI_INT,l,1,MPI_COMM_WORLD);
		}	
	}
	else
	{
			MPI_Recv(&M,1,MPI_INT,0,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	}

//Dynamic Memory Allocation
	int* B=(int*)malloc(N*sizeof(int));
	for(i=0;i<N;i++){
		B[i]=0;
	}	

	A=(int**)malloc(N*sizeof(int*));
	for(i=0;i<N;i++){
		A[i]=(int*)malloc(N*sizeof(int));
		for(j=0;j<N;j++){
			A[i][j]=0;
		}
	}

	for(i=0;i<N;i++){
		scanf("%d",&M);
		B[i]=M;
		A[i]=(int*)malloc(M*sizeof(int));
		for(j=0;j<M;j++){
			scanf("%d",&A[i][j]);
		}
	}

/*
	for(i=0;i<N;i++){
			for(j=0;j<B[i];j++){
				printf("%d ",A[i][j]);
			}
			printf(" \n");
		}
*/

	if(rank==0)
	{	
		for( l=1;l<nop;l++)
		{
			MPI_Send(B,N,MPI_INT,l,2,MPI_COMM_WORLD);
		}	
	}
	else
	{
			MPI_Recv(&B[0],N,MPI_INT,0,2,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	}


	if(rank==0)
	{	
		for( l=1;l<nop;l++)
		{
			for(i=0;i<N;i++){
				MPI_Send(A[i],B[i],MPI_INT,l,3,MPI_COMM_WORLD);
			}
		}	
	}
	else
	{
			for(i=0;i<N;i++){
				MPI_Recv(&A[i][0],B[i],MPI_INT,0,3,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			}
			
	}


	
	for(i=0;i<N;i++){		
		if(rank==(i%nop)){
			int num=0;
			for(j=0;j<B[i];j++){
				if(prime(A[i][j])){
					if(num==0){
						printf("-- \n");						
						}
					printf("%d \n",A[i][j]);
					num++;
				}
			}
			num=0;
		}
	
	}

	free(A);
	free(B);

	MPI_Finalize();

return 0;
}		



	





