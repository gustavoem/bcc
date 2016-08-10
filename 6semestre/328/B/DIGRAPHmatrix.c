/*
Nome: Gustavo Estrela de Matos
NUSP: 8536051
Sigla: GUSTAVOE
Data: 08/08/2016
Disciplina: MAC0328

Este arquivo faz parte da tarefa B e tem como objetivo imlpementar uma
biblioteca para manipulação de grafos. Essa biblioteca usa matrizes
de adjacência na sua implementação.
*/

#include "DIGRAPHmatrix.h"

/* Protótipos de funções do tipo static */
static int **MATRIXint (int r, int c, int val);
static void MATRIXdelete (int **m, int r);

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função DIGRAPHinit()
constrói um digrafo com vértices 0 1 .. V-1 e nenhum arco. */
Digraph DIGRAPHinit (int V) { 
   Digraph G = malloc (sizeof *G);
   G->V = V; 
   G->A = 0;
   G->adj = MATRIXint (V, V, 0);
   return G;
}

/* REPRESENTAÇÂO POR MATRIZ DE ADJACÊNCIAS: A função DIGRAPHdestroy()
destrói um digrafo G liberando na memória o espaço que foi alocado em
sua criação */
void DIGRAPHdestroy (Digraph G) {
   MATRIXdelete (G->adj, G->V);
   free (G);
}

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função MATRIXdelete()
deleta uma matriz com linhas 0..r-1 e colunas 0..c-1. */
static void MATRIXdelete (int **m, int r) {
   int i;
   for (i = 0; i < r; i++)
      free (m[i]);
   free (m);
}

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função MATRIXint() aloca
uma matriz com linhas 0..r-1 e colunas 0..c-1. Cada elemento da matriz
recebe valor val. */
static int **MATRIXint (int r, int c, int val) { 
   Vertex i, j;
   int **m = malloc (r * sizeof (int *));
   for (i = 0; i < r; i++)
      m[i] = malloc (c * sizeof (int));
   for (i = 0; i < r; i++)
      for (j = 0; j < c; j++)
         m[i][j] = val;
   return m;
}

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função DIGRAPHinsertA()
insere um arco v-w no digrafo G. A função supõe que v e w são 
distintos, positivos e menores que G->V. Se o digrafo já tem um arco 
v-w, a função não faz nada. */
void DIGRAPHinsertA (Digraph G, Vertex v, Vertex w) { 
   if (G->adj[v][w] == 0) {
      G->adj[v][w] = 1; 
      G->A++;
   }
}

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função DIGRAPHremoveA()
remove do digrafo G o arco v-w. A função supõe que v e w são distintos,
positivos e menores que G->V. Se não existe arco v-w, a função não faz
nada. */
void DIGRAPHremoveA (Digraph G, Vertex v, Vertex w) { 
   if (G->adj[v][w] == 1) {
      G->adj[v][w] = 0; 
      G->A--;
   }
}

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função DIGRAPHoutdeg() 
calcula o grau de saída do vértice v do grafo G. A função supõe que
v é menor que G->V */
int DIGRAPHoutdeg (Digraph G, Vertex v) {
   int w;
   int deg = 0;
   for (w = 0; w < G->V; w++)
      if (G->adj[v][w])
         deg++;
   return deg;
}

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função DIGRAPHindeg() 
calcula o grau de entrada do vértice v do grafo G. A função supõe que
v é menor que G->V */
int DIGRAPHindeg (Digraph G, Vertex w) {
   int v;
   int deg = 0;
   for (v = 0; v < G->V; v++)
      if (G->adj[v][w])
         deg++;
   return deg;
}

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função DIGRAPHshow()  
imprime, para cada vértice v do digrafo G, em uma linha, todos os
vértices adjacentes a v. */
void DIGRAPHshow (Digraph G) { 
   Vertex v, w;
   for (v = 0; v < G->V; v++) {
      printf ("%2d:", v);
      for (w = 0; w < G->V; w++)
         if (G->adj[v][w] == 1) 
            printf (" %2d", w);
      printf ("\n");
   }
}