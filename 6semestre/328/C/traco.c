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
int count;

/* Guarda a número de pré-ordem de cada vértice */
int *pre;

/* A função DIGRAPHdfs() visita todos os vértices e todos os arcos do
digrafo G. A função atribui um número de ordem pre[x] a cada vértice x:
o k-ésimo vértice descoberto recebe número de ordem k.  (Código
inspirado no programa 18.3 de Sedgewick.) */
void DIGRAPHdfs (Digraph G) { 
   Vertex v;
   conta = 0;
   for (v = 0; v < G->V; v++) 
      pre[v] = -1;
   for (v = 0; v < G->V; v++)
      if (pre[v] == -1) 
         dfsR( G, v); /* começa nova etapa */
}

/* Seja U o conjunto dos vértices u tais que pre[u] >= 0. Nesse
ambiente, para cada vértice x acessível a partir de v por um caminho 
que não usa vértices de U, a função dfsR() atribui um número positivo a
pre[x]:  se x é o k-ésimo vértice descoberto, pre[x] recebe conta+k.
(Código inspirado no programa 18.1 de Sedgewick.) */
static void dfsR (Digraph G, Vertex v) {
   Vertex w;
   pre[v] = conta++; 
   for (w = 0; w < G->V; w++)
      if (G->adj[v][w] != 0 && pre[w] == -1)
         dfsR (G, w); 
}

