#include <stdio.h>

int count_invertions (int v[], int e, int d, int n) {
    int inv, einv, dinv, minv;
    int k = (d + e) / 2;
    
    if (e == d - 1)
        return 0;

    einv = count_invertions (v, e, k, n);
    dinv = count_invertions (v, k, d, n);
    minv = intercala (v, e, k, d);

    return einv + dinv + minv;   
}

/*intercala os elementos dos vetores e devolve o numero de elementos do segundo vetor que sao maiores que elementos do primeiro vetor*/
int intercala (int v[], int e, int m, int n) {
    int i = e, j = m;
    int k = 0;
    int inv = 0;
    int v2[n];
   
    while ((i < m) && (j < n)) {
        if (v[i] < v[j]) {
            v2[k++] = v[i++];
        }
        else {
            /*invariante:
             * todo elemento de v[i] até v[m] é maior do que
             * v[j]
             */
            v2[k++] = v[j++];
            inv += (m - i);
        }
    }
    
    while (i < m) 
        v2[k++] = v[i++];

    while (j < n)
        v2[k++] = v[j++];

    for (i = e; i < n; i++)
        v[i] = v2[i - e];
    
    return inv;
}

int main () {
    int v[10] = {1, 2, 22, 6, 7, 19, 10, 13, 41};
    int r, i;
    
    r = count_invertions (v, 0, 9, 9);

    for (i = 0; i < 5; i++)
        printf ("%d\n", v[i]);
    printf ("Invercoes: %d\n", r);

    return 0;
}
