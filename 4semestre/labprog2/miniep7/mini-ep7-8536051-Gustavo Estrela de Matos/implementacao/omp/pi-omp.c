#include <stdio.h> 

static long num_steps = 1000000;
double step;

int main() {
    int i;
    double x, pi, sum = 0.0;
    #pragma omp parallel num_threads(10)
    {
        int id = omp_get_thread_num();
        printf("Hi, i'm thread %d\n", id);
    }
    return 0;
}
