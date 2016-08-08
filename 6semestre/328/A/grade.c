#include <stdio.h>
#include <stdlib.h>

int ** constroiMatrizAdj (m, n)
{
    int i, j, s, e;
    int ** matriz = malloc (m * n * sizeof (int *));
    for (i = 0; i < m * n; i++)
        matriz[i] = malloc (m * n * sizeof (int));
    
    for (s = 0; s < m * n; s++)
    {
        int s_i = s / n;
        int s_j = s % n;
        for (e = 0; e < m * n; e++)
        {
            int e_i = e / n;
            int e_j = e % n;

            if ((e_j == s_j && (s_i == e_i - 1 || s_i == e_i + 1)) ||
                (e_i == s_i && (s_j == e_j - 1 || s_j == e_j + 1)))
               matriz[s][e] = 1;
            else
               matriz[s][e] = 0; 
        }
    }
    return matriz;
}


int main ()
{
    int m, n;
    int i, j;
    int ** matriz;
    
    scanf ("%d %d", &m, &n);
    matriz = constroiMatrizAdj (m, n);
    for (i = 0; i < m * n; i++)
    {
        for (j = 0; j < m * n; j++)
            printf ("%d ", matriz[i][j]);
        printf ("\n");
    }
    return 0;
}
