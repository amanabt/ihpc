#include <iostream>
#include <omp.h>

using namespace std;

int main(){
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            cout << omp_get_thread_num() << '/' << omp_get_num_threads() << '\n';            
        }
        #pragma omp section
        {
            cout << omp_get_thread_num() << '/' << omp_get_num_threads() << '\n';            
        }
        #pragma omp section
        {
            cout << omp_get_thread_num() << '/' << omp_get_num_threads() << '\n';            
        }
        #pragma omp section
        {
            cout << omp_get_thread_num() << '/' << omp_get_num_threads() << '\n';            
        }
    }
}