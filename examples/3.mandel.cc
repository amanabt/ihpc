#include <iostream>

using namespace std;

int mandel_val(int x, int y, int maxiter)
{
    return maxiter;
}

int main(){
    int m=10;
    int n=10;
    float depth[m][n];

    int i,j;
    float x,y;

    int maxiter=200;
	#pragma omp parallel for private(j, x, y)
    for (i=0; i<m; i++) {
        for (j=0; j<n; j++) {
            x=i/float(m);
            y=j/float(n);
            depth[i][j] = mandel_val(x, y, maxiter);
        }
    }
}
