#include <iostream>
#include <omp.h>

using namespace std;

void test(int val)
{
    #pragma omp parallel if (val)
    cout << omp_get_thread_num() << '/' << omp_get_num_threads() << '\n';
}

int main( )
{
    omp_set_num_threads(2);
    cout << "serial\n";
    test(0);
    cout << "parallel\n";
    test(2);

    return 0;
}
