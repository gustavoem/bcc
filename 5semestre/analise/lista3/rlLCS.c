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
    int u[NMAX];
    int v[NMAX];
    int * C1 = u;
    int * C2 = v;
        
    
    // ultima coluna
    // lLCS (xin, ymm) = 1 se ymm in xin; 0 c.c.
    for (i = n; i > 0 && y[m] != x[i]; i--)
        C2[i] = 0;

    while (i > 0)
        C2[i--] = 1;

    for (j = m - 1; j > 0; j--)
    {
        int * aux;
        // C1 e a j-esima coluna da matriz opt
        // C2 e a j-esima+1 
        // lLCS (xnn, yjm) = 1 se yjm in xnn; 0 c.c.
        C1[n] = (x[n] == y[j]) || (C2[n]);
        for (i = n - 1; i > 0; i--)
        {
            if (x[i] == y[j])
                C1[i] = 1 + C2[i + 1];
            else 
                if (C2[i] >= C1[i + 1])
                    C1[i] = C2[i];
                else
                    C1[i] = C1[i + 1];
        }
        aux = C2;
        C2 = C1;
        C1 = aux;
    }

    for (i = n; i > 0; i--)
        L[i] = C2[i];
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
