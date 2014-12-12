#include <stdio.h> 

double step;

int main(int argc, char *argv[]) {
    int i;
    double x, pi, sum = 0.0;
    int num_steps = atoi(argv[1]);
    int num_threads = atoi(argv[2]);
    
    step = 1.0/(double) num_steps;
    #pragma omp parallel for schedule(static, 1) num_threads(num_threads)
    for (i = 0; i < num_steps; i++) {
        x = (i + 0.5) * step;
        #pragma omp atomic
        sum = sum + 4.0 / (1.0 + x * x);
    }
    pi = step * sum;
    printf("PI: %g\n", pi);
    return 0;
}
