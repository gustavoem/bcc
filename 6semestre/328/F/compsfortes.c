/* DECLARO QUE SOU O UNICO AUTOR E RESPONSAVEL POR ESTE PROGRAMA.
// TODAS AS PARTES DO PROGRAMA, EXCETO AS QUE FORAM FORNECIDAS
// PELO PROFESSOR OU COPIADAS DO LIVRO OU DAS BIBLIOTECAS DE
// SEDGEWICK OU ROBERTS, FORAM DESENVOLVIDAS POR MIM.  DECLARO
// TAMBEM QUE SOU RESPONSAVEL POR TODAS AS COPIAS DESTE PROGRAMA
// E QUE NAO DISTRIBUI NEM FACILITEI A DISTRIBUICAO DE COPIAS.
//
// Autor:      Gustavo Estrela
// Numero USP: 8536051
// Sigla:      GUSTAVOE
// Data:       2016-09-11
//
// Este arquivo faz parte da tarefa F
// da disciplina MAC0328 e tem como objetivo estudar como o tamanho
// das maiores componentes fortes de um digrafo aleatório de V vértices
// e A arcos evolui em função de A.
//
////////////////////////////////////////////////////////////// */

#include <stdlib.h>
#include <stdio.h>
#include "DIGRAPHlists.h"

/* Protótipo das funções */
double avg_higher_components (Digraph G);
void n_highest (int *data, int *highest, int n, int k);
double data_mean (int *data, int n);

/* Esta função recebe dois vetores, data e highest com tamanhos n e k
respectivamente e devolve em highest os k maiores valores encontrados
em data. */
void n_highest (int *data, int *highest, int n, int k) {
    int unordered, aux, i, j;
    for (i = 0; i < k; i++)
        highest[i] = 0;
    for (i = 0; i < n; i++) {
        unordered = data[i];
        for (j = 0; j < k; j++)
            if (unordered > highest[j]) {
                aux = highest[j];
                highest[j] = unordered;
                unordered = aux;
            }
    }
}

/* Esta função retorna a média dos valores contidos em um vetor de
tamanho n. */
double data_mean (int *data, int n) {
    int i;
    int accumulated = 0;
    for (i = 0; i < n; i++)
        accumulated += data[i];
    return accumulated / (float) n;
}

/* Esta função devolve a média do tamanho das três maiores componentes
fortes do digrafo G. Para essa função funcionar é necessário que o
digrafo G tenha suas componentes informadas no campo sc de Digraph. */
double avg_higher_components (Digraph G) {
    Vertex v;
    double ans;
    int highestcp[3];
    int *cpsize = DIGRAPHscsizes (G);
    /**/
    printf ("\nTamanho das componentes: ");
    for (v = 0; v < G->V; v++)
        printf ("%d ", cpsize[v]);
    printf ("\n");
    /**/
    n_highest (cpsize, highestcp, G->V, 3);
    ans = data_mean (highestcp, 3);
    free (cpsize);
    return ans;
}

/* Esta função recebe como parametros, em argv, V e k. São gerados
então k grafos aleatórios com V vértices e um numero A de arcos que
varia. */
int main (int argc, char **argv) {
    int V, A, k, i, j;
    Digraph G;
    if (argc != 3)
        return 0;
    V = atoi (argv[1]);
    k = atof (argv[2]);
    printf ("V = %d; k = %d\n\n", V, k);
    printf ("   A   |  1a maior componente  |  2a maior componente  |  3a\
maior componente\n");
    printf ("____________________________________________________________\
_________________\n");
    for (A = V / 2; A <= 16 * V; A += V / 2) {
        int bigcpsum[3] = {0, 0, 0};
        printf ("\n");
        printf (" %5d ", A);
        for (i = 0; i < k; i++) {
            int bigcp[3];
            int *cpsizes;
            G = DIGRAPHrand1 (V, A);
            DIGRAPHscKS (G);
            cpsizes = DIGRAPHscsizes (G);
            n_highest (cpsizes, bigcp, G->V, 3);
            for (j = 0; j < 3; j++)
                bigcpsum[j] += bigcp[j];
            free (cpsizes);
            DIGRAPHdestroy (G);
        }
        for (j = 0; j < 3; j++)
            printf ("|       %8.2f        ", bigcpsum[j] / (float) k);
    }
    printf ("\n");
    return 0;
}
