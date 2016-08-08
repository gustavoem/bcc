#include "DIGRAPHmatrix.h"

/* Protótipos de funções do tipo static */
static int **MATRIXint (int r, int c, int val);

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A estrutura digraph 
representa um digrafo. O campo adj é um ponteiro para a matriz de 
adjacências do digrafo. O campo V contém o número de vértices e o campo
A contém o número de arcos do digrafo. */
struct digraph {
    int V;
    int A;
    int **adj;
};


/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função DIGRAPHinit()
constrói um digrafo com vértices 0 1 .. V-1 e nenhum arco. */
Digraph DIGRAPHinit (int V) { 
   Digraph G = malloc (sizeof *G);
   G->V = V; 
   G->A = 0;
   G->adj = MATRIXint (V, V, 0);
   return G;
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