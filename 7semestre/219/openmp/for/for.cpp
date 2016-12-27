// A parallel program for summing two vectors
// 

#include <iostream>
#include <omp.h>
#include <cstdlib>

#define N 10000000

using namespace std;

int main (int argc, char **argv) {
    int i, chunk, tid;
    float *a, *b, *c;
    a = (float *) malloc (N * sizeof (float));
    b = (float *) malloc (N * sizeof (float));
    c = (float *) malloc (N * sizeof (float));
    for (i = 0; i < N; i++) {
        a[i] =  rand () / (RAND_MAX + 1.0);
        b[i] =  rand () / (RAND_MAX + 1.0);
    }
    chunk = N / 10.0;
    #pragma omp parallel shared (a, b, c) private (i) 
    {
        // Dynamic scheduling: when a thread finishes one chunk it is
        // assigned to another
        #pragma omp for schedule(dynamic,chunk) nowait
        for (i = 0; i < N; i++) {
            //tid = omp_get_thread_num ();
            c[i] = a[i] + b[i];
            //cout << i << "-" << tid << endl;
        }
    }
    for (i = 0; i < N; i++)
        if (c[i] != b[i] + a[i])
            cout << "ERRO!" << endl;
    free (a);
    free (b);
    free (c);
    return 0;
}
