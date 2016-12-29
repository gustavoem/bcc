// This program creates a list of random generated numbers in the
// interval [0,1) and then calculates the cosine of each one of the
// numbers. The answer is the smallest cosine.
// The idea of this program is to practice usage of the openmp 
// library, calculating the cosine of each number in a task.

#include <iostream>
#include <cmath>
#include <omp.h>
#include <list>
#include <cstdlib>

#define CUTOFF 2

using namespace std;

float my_rand ();
float rmin (float *cosx, int n);
float smin (float *cosx, int n);

float my_rand () {
    return rand () / (RAND_MAX + 1.0);
}

float rmin (float *cosx, int n) {
    if (n < CUTOFF)
        return smin (cosx, n);
    int tid = omp_get_thread_num ();
    #pragma omp critical
    cout << "base: " << cosx << " from thread: " << tid << endl;
    float min1, min2;
    int half = n / 2;
    #pragma omp task shared (min1)
    min1 = rmin (cosx, half);
    #pragma omp task shared (min2)
    min2 = rmin (cosx + half, half);
    #pragma omp taskwait
    if (min1 < min2)
        return min1;
    else
        return min2;
}

float smin (float *cosx, int n) {
    float min = cosx[0];
    for (int i = 1; i < n; i++)
        if (cosx[i] < min)
            min = cosx[i];
    return min;
}

int main (int argc, char **argv) {
    float *cosx;
    int n;
    float min;
    if (argc != 2)
        return 0;
    n = atoi (argv[1]);
    cosx = (float *) malloc (n * sizeof (float));
    #pragma omp parallel shared (cosx)
    #pragma omp for schedule (dynamic)
    for (int i = 0; i < n; i++) {
        float x = my_rand ();
        int tid = omp_get_thread_num ();
        cosx[i] = cos (x);
    }
    #pragma omp parallel shared (cosx)
    #pragma omp single nowait
    min = rmin (cosx, n);
    cout << "min: " << min << endl;
    return 0;
}
