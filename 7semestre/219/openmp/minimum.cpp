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

using namespace std;

int main (int argc, char **argv) {
    list<float> x;
    list<float> cosx;
    int n;
    if (argc != 2)
        return 0;
    n = atoi (argv[1]);
    return 0;
}
