// A simple hello world using OpenMP
// 

#include <iostream>
#include <omp.h>
#include <cstdlib>

using namespace std;

int main (int argc, char **argv) {
    int nthreads, tid;
    
    #pragma omp parallel private (tid)
    {
        tid = omp_get_thread_num ();
        cout << "Hello from thread " << tid << endl;
        if (tid == 0) {
            nthreads = omp_get_num_threads ();
            cout << "Number of threads: " << nthreads << endl;
        }
    }
    return 0;
}
