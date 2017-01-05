#include <iostream>
#include <cmath>
#include <omp.h>
#include <list>
#include <cstdlib>

using namespace std;

void bar (int k, float *b);
void foo (int k);

void bar (int k, float *b) {
    #pragma omp task
    foo (k - 1);
    #pragma omp task
    foo (k - 2);
    #pragma omp task
    foo (k - 3);
    #pragma omp critical
    //cout << "k = " << k << " b = " << b << endl;
    #pragma omp taskwait
}

void foo (int k) {
    if (k < 1)
        return;
    float a;
    float *b = &a;
    int tid = omp_get_thread_num ();
    #pragma omp critical
    //cout << "Thread " << tid << " k = " << k << endl;
    #pragma omp parallel shared (b)
    #pragma omp single nowait
    bar (k, b);
    #pragma omp critical
    cout << "b depois = " << b << ", &a = " << &a << endl;
}

int main (int argc, char **argv) {
    foo (3);
    return 0;
}
