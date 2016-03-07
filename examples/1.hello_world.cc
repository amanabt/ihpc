#include <iostream>

int main (void) {
    #pragma omp parallel
    std::cout << "Hello world" << std::endl;
    return 0;
}
