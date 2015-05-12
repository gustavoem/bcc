#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NMAX 100

/* Devolve um vetor (mallocado) L tal que, para todo i ≥ 1,
   L[i] = rOpt[i, 1] */
int * lLCS (char * x, int n, char * y, int m)
{
    int i, j;
    int * L = (int *) malloc (NMAX * sizeof (int));
    int v1[NMAX];
    int v2[NMAX];
    
    
    // ultima coluna
    // lLCS (xin, ymm) = 1 se ymm in xin; 0 c.c.
    for (i = n; i > 0 && y[m] != x[i]; i--)
        opt[i][m] = 0;

    while (i > 0)
        opt[i--][m] = 1;

    for (j = m - 1; j > 0; j--)
    {
        // lLCS (xnn, yjm) = 1 se yjm in xnn; 0 c.c.
        opt[n][j] = (x[n] == y[j]) || (opt[n][j+1]);
        for (i = n - 1; i > 0; i--)
        {
            if (x[i] == y[j])
                opt[i][j] = 1 + opt[i + 1][j + 1];
            else 
                if (opt[i][j + 1] >= opt[i + 1][j])
                    opt[i][j] = opt[i][j + 1];
                else
                    opt[i][j] = opt[i + 1][j];
        }
    }

    for (i = n; i > 0; i--)
        L[i] = opt[i][1];
    return L;
} 


int main ()
{
    int i = 1;
    int n, m;
    int * L;
    char * x = (char *) malloc (NMAX * sizeof (char));
    char * y = (char *) malloc (NMAX * sizeof (char));

    while (scanf ("%c", &x[i]) && x[i++] != 10);
    x[i--] = 0;
    n = i - 1;
    i = 1;
    while (scanf ("%c", &y[i]) && y[i++] != 10);
    y[i--] = 0;
    m = i - 1;

    L =  lLCS (x, n, y, m);
    for (i = n; i > 0; i--)
        printf ("lLCS(x%dn, y1m) = %d\n", i, L[i]);
    return 0;
}
