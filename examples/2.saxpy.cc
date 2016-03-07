#include <iostream>
#include <omp.h>

using namespace std;

void saxpy(float *z, float a, float *x, float y, int n)
{
    #pragma omp parallel for
    for (int i=0; i<n; i++) 
    {
        cout << omp_get_thread_num() << '/' << omp_get_num_threads() << '\n';
        z[i]=a*x[i]+y;
    }
}

int main(){
    omp_set_num_threads(10);
    cout << "Total num threads in main " << omp_get_num_threads() << '\n';

    float x[]={0,1,2,3,4,5,6,7,8,9};
    float z[10];

    saxpy(z, 2, x, 3, 10);

    for (int i=0; i<10; i++)
        cout << i << ' ' << z[i] << '\n';

}
