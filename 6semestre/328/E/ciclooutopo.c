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
// Data:       2016-08-30
//
// Este arquivo faz parte da tarefa E
// da disciplina MAC0328 e tem como objetivo testar a função
// DIGRAPHcycleOrTopo () da biblioteca DIGRAPHmatrix
//
////////////////////////////////////////////////////////////// */

#include <stdlib.h>
#include <stdio.h>
#include "DIGRAPHmatrix.h"

void printTopoList (Digraph G) {
    Vertex v;
    Vertex *list = malloc (G->V * sizeof (Vertex));
    for (v = 0; v < G->V; v++)
        list[G->pre[v]] = v;
    printf ("\nListagem topológica: ");
    for (v = 0; v < G->V; v++)
        printf ("%d ", list[v]);
    printf ("\n");
    free (list);
}

void printCycle (Digraph G, Vertex v) {
    int i, j;
    Vertex aux;
    Vertex *cycle = malloc (G->V * sizeof (Vertex));
    i = 0;
    aux = v;
    while (G->father[aux] != v) {
        cycle[i++] = aux;
        aux = G->father[aux];
    }
    cycle[i] = aux;
    printf ("\nCiclo: ");
    for (j = i; j >= 0; j--)
        printf ("%d ", cycle[j]);
    printf ("%d\n", cycle[i]);
    free (cycle);
}


/* Esta função recebe digrafo descrito na entrada padrão e, usando a
função DIGRAPHcycleOrTopo () imprime um ciclo ou uma listagem
topologica dos vértices. */
int main () {
    int i;
    int V, A;
    Digraph G;
    scanf ("%d\n%d", &V, &A);
    G = DIGRAPHinit (V);
    for (i = 0; i < A; i++) {
        int v, w;
        scanf ("%d %d", &v, &w);
        DIGRAPHinsertA (G, v, w);
    }
    i = DIGRAPHcycleOrTopo (G);
    if (i == -1)
        printTopoList (G);
    else
        printCycle (G, i);
    DIGRAPHdestroy (G);
    return 0;
}
