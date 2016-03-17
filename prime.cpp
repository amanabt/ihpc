#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int prime(int b)
{	
	 int c=sqrt(b);
	int j;
	for(j=2;j<=c;j++)
	{
		if(b%j==0)
			{	break;}
	}
	if(j>c)
		{ return 1;}
	return 0;
}

int main(int argc,char** argv)
{
	//printf("%d\n",prime(7));
	int N,nop,rank,k,y,count_;
	scanf("%d",&N);	
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&nop);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	
	if(rank==0)
	{	
		for(k=1;k<nop;k++)
		{
			MPI_Send(&N,1,MPI_INT,k,0,MPI_COMM_WORLD);
		}	
	}
	if(rank!=0)
	{
		MPI_Recv(&N,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		//printf("recv");
	}

	int *M=(int *)malloc(N*sizeof(int));
	int **a=(int **)malloc(2*N*sizeof(int *));
	
	for(int i=0;i<N;i++)		
	{
		scanf("%d",&M[i]);
		if(rank==0)
		{	
			for(k=1;k<nop;k++)
			{
				MPI_Send(&M[i],1,MPI_INT,k,1,MPI_COMM_WORLD);
			}	
		}
		if(rank!=0)
		{
			MPI_Recv(&M[i],1,MPI_INT,0,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			//printf("recv");
		}	

		*(a+2*i)=(int *)malloc(M[i]*sizeof(int));
		*(a+2*i+1)=(int *)malloc(M[i]*sizeof(int));
		for(int j=0;j<M[i];j++)
		{
			scanf("%d",&a[2*i][j]);
			a[2*i+1][j]=0;		
		}
	}
	/*if(rank==0)
	{	
		for(int k=1;k<nop;k++)
		{
			MPI_Send(&M[0],N,MPI_INT,k,1,MPI_COMM_WORLD);
		}
	}
	else
	{
		printf("enter");
		MPI_Recv(&M[0],N,MPI_INT,0,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		printf("recv");
	}*/
	for(int i=0;i<N;i++)
	{	if(rank==0)
		{	
			for(int k=1;k<nop;k++)
			{
				MPI_Send(a[2*i],M[i],MPI_INT,k,2+i,MPI_COMM_WORLD);
				//printf("sent");
			}
		}
		else
		{
			MPI_Recv(&a[2*i][0],M[i],MPI_INT,0,2+i,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			//printf("rec");
		}
		
	}

	


	for(int k=1;k<=N;k++)
	{	
		printf("%d ",rank);
		for(int j=1;j<=M[k-1]/nop+1;j++)
		{	
			if(rank+nop*(j-1)<M[k-1])
			{	//printf("enter");
				y=prime(a[2*(k-1)][rank+nop*(j-1)]);
				//printf("%d ",a[2*(k-1)][rank+nop*(j-1)]);
				//printf("%d ",rank);						
				//printf("%d  ",y);
			}
		
			if(y==1)
			{	
				printf("enter");				
				a[2*k-1][rank+nop*(j-1)]=1;
				
			}
		}

		/*if(rank==0)
		{	
			printf("entered");
			for(int l=1;l<nop;l++)
			{	printf("entered");
				MPI_Recv(&count[l],1,MPI_INT,l,l,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
				printf("received _0  ");

			}
		}
		if(rank!=0)
		{	
				printf("entered");
				MPI_Send(&count_,1,MPI_INT,0,rank,MPI_COMM_WORLD);
				
				printf("sent  _1 ");	
		
		}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if(rank==0)
		{	
			int j,m;
			for( int l=1;l<nop;l++)
			{	
					j=0;
					m=0;
					while(j<M[k-1]&&m<count[l])
					{	MPI_Recv(&j,1,MPI_INT,l,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
						MPI_Recv(&a[2*k-1][j],1,MPI_INT,l,l+j-1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
						m++;
						j++;
					}
			}

		}


		if(rank!=0)
		{
			for(int j=0;j<M[k-1];j++)
			{	
				if(a[2*k-1][j]==1)
					MPI_Send(&j,1,MPI_INT,0,0,MPI_COMM_WORLD);						
					MPI_Send(&a[2*k-1][j],1,MPI_INT,0,rank+j,MPI_COMM_WORLD);
			}

		}


	}*/
		for(int i=1;i<nop;i++)
		{
			for(int j=0;j<M[k-1];j++)
			{	
				//printf("enter");
				if(a[2*k-1][j]==1)
				{	
					//printf("enter");
					MPI_Bcast(&a[2*k-1][j],1,MPI_INT,i,MPI_COMM_WORLD);
					//printf("enter");  }
				}
			}
		}
	}



	if(rank==0)
	{	
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<M[i];j++)
			{	if(a[2*i+1][j]==1)
				printf("%d ",a[2*i][j]);
			}
														printf("\n");
		}	 
	}

	
	MPI_Finalize();




return 0;
}		



	




	
