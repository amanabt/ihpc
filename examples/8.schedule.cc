#include <iostream>
#include <omp.h>

using namespace std;

int mandel_val(int x, int y, int maxiter)
{
    return maxiter;
}

int main(){
    int m=10;
    int n=10;
    float depth[m][n];

    float x,y;

    int maxiter=200;
    #pragma omp parallel for private(x, y) schedule(dynamic)
    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            x=i/float(m);
            y=j/float(n);
            depth[i][j] = mandel_val(x, y, maxiter);
        }
    }
}
