#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>



int prime(int b,int k,int nop,int rank,int i,int a[],int **c)
{	
	 int d=sqrt(b);
	int j;
	for(j=2;j<=d;j++)
	{
		if(b%j==0)
			{	break;}
	}
	if(j>d)
		{ 	*(*(c+i)+rank+nop*(k-1))=a[rank+nop*(k-1)];
			return 1;}
	return 0;
}

int main(int argc,char **argv)
{
	int N,nop,rank,i,j,k,y;
	scanf("%d",&N);
	MPI_Init(&argc,&argv);
	MPI_Comm_size (MPI_COMM_WORLD,&nop);
	MPI_Comm_rank (MPI_COMM_WORLD,&rank);
	if(rank==0)
	{
		for( i=1;i<nop;i++)
		{
			MPI_Send(&N,1,MPI_INT,i,0,MPI_COMM_WORLD);
		}
	}
	else
	{
		MPI_Recv(&N,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	}

	int *M=(int *)malloc(N*sizeof(int));
	int **c=(int **)malloc(N*sizeof(int*));
	for(i=0;i<N;i++)
	{
		*(c+k)=(int *)malloc(50*sizeof(int));
	}
	for(i=0;i<N;i++)
	{
		for(j=0;j<50;j++)
		{
			c[i][j]=0;
		}
	}

	for(j=0;j<N;j++)
	{
		int M_j;
		scanf("%d",&M_j);
		if(rank==0)
		{
			for( i=1;i<nop;i++)
			{
				MPI_Send(&M_j,1,MPI_INT,i,1,MPI_COMM_WORLD);
			}
		}
		else
		{
			MPI_Recv(&M_j,1,MPI_INT,0,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		}	
		int *a=(int *)malloc(M_j*sizeof(int));
		for( k=0;k<M_j;k++)
		{
			scanf("%d",&a[k]);
		}


		if(rank==0)
		{
			for( i=1;i<nop;i++)
			{
				MPI_Send(a,M_j,MPI_INT,i,2,MPI_COMM_WORLD);
			}
		}
		else
		{
			MPI_Recv(&a[0],M_j,MPI_INT,0,2,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		}	
		for(k=1;k<=M_j/nop+1;k++)
		{
			if(rank+nop*(k-1)<M_j)
			{	

				MPI_Barrier(MPI_COMM_WORLD);
				y=prime(a[rank+nop*(k-1)],k,nop,rank,j,a,c);
			}	
		}
		free(a);
		
	}
	for(k=0;k<N;k++)
	{	
		for(i=0;i<50;i++)
		{
			for(j=1;j<nop;j++)
			{
				if(rank==j)
				{	
					if(c[k][i]!=0)
					{	
						printf("%d ",c[k][i]);
						break;
					}	
				}
			}
		}
		printf("\n");
	}




	MPI_Finalize();



return 0;
}
















	
