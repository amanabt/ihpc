#include <iostream>

using namespace std;

int some_complicated_calculation(int i)
{
    return i*i;
}

int main(){
    int m=10;
    float x[m];

    #pragma omp parallel for ordered
    for (int i=0; i<m; i++) {
        x[i]=some_complicated_calculation(i);
        #pragma omp ordered
        cout << i << ' ' << x[i] << endl;
    }
}

//ordered can be used anywhere in the dynaminc extent