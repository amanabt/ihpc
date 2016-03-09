int i,j,k,n,m;
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
    