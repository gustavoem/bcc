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
// Data:       2016-08-17
//
// Este arquivo faz parte da tarefa C
// da disciplina MAC0328 e tem como objetivo implementar e testar uma
// variante da função DFS de que mostra o traço do algoritmo.
//
////////////////////////////////////////////////////////////// */

#include <stdlib.h>
#include <stdio.h>
#include "DIGRAPHlists.h"

/* Guarda a profundidade atual do algoritmo de DFS */
int depth;

/* Guarda contagem de vértices já descobertos pelo DFS */
int pre_count;

/* Guarda contagem de vértices já processados (mortos) pelo DFS */
int pos_count;

/* Guarda a número de pré-ordem de cada vértice */
int *pre;

/* Guarda o número de pós-ordem de cada vértice */
int *pos;

/* Protótipos de funções */
void DIGRAPHdfs (Digraph G);
static void dfsR (Digraph G, Vertex v);

/* A função DIGRAPHdfs() visita todos os vértices e todos os arcos do
digrafo G. A função atribui um número de ordem pre[x] a cada vértice x:
o k-ésimo vértice descoberto recebe número de ordem k.  (Código
inspirado no programa 18.3 de Sedgewick.) */
void DIGRAPHdfs (Digraph G) {
    Vertex v;
    pre = malloc (G->V * sizeof (int));
    pos = malloc (G->V * sizeof (int));
    pre_count = 0;
    pos_count = 0;
    for (v = 0; v < G->V; v++) {
        pre[v] = -1;
        pos[v] = -1;
    }
    for (v = 0; v < G->V; v++)
        if (pre[v] == -1) {
            /* printf ("\n"); */
            dfsR (G, v);
            /* printf ("\n"); */
        }
}

/* Seja U o conjunto dos vértices u tais que pre[u] >= 0. Nesse
ambiente, para cada vértice x acessível a partir de v por um caminho
que não usa vértices de U, a função dfsR() atribui um número positivo a
pre[x]:  se x é o k-ésimo vértice descoberto, pre[x] recebe conta+k.
(Código inspirado no programa 18.1 de Sedgewick.) */
static void dfsR (Digraph G, Vertex v) {
    Vertex w;
    link l = G->adj[v];
    int i;
    pre[v] = pre_count++;
    depth++;
    while (l != NULL) {
        printf ("\n");
        w = l->w;
        for (i = 0; i < depth; i++)
            printf ("  ");
        printf ("%d-%d ", v, w);
        if (pre[w] == -1) {
            printf ("floresta");
            dfsR (G, w);
        }
        else if (pos[w] != -1)
            if (pos[w] < pre[v]) 
                printf ("cruzado");
            else
                printf ("descendente");
        else
            printf ("retorno");
        l = l->next;
    }
    pos[v] = pos_count++;
    depth--;
}

/* Esta função recebe como parametros, em argv, V e A, e gera um
digrafo aleatório com V vértices e A arestas. Além disso a função
aplica a função DIGRAPGdfs () no grafo gerado. */
int main (int argc, char **argv) {
    int V, A;
    Digraph G;
    if (argc != 3)
        return 0;
    V = atoi (argv[1]);
    A = atof (argv[2]);
    G = DIGRAPHrand1 (V, A);
    DIGRAPHshow (G);
    DIGRAPHdfs (G);
    DIGRAPHdestroy (G);
    free (pos);
    free (pre);
    printf ("\n");
    return 0;
}
