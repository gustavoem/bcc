/*
Nome: Gustavo Estrela de Matos
NUSP: 8536051
Sigla: GUSTAVOE
Data: 08/08/2016
Disciplina: MAC0328

Este arquivo faz parte da tarefa B e tem como objetivo implementar uma
biblioteca para manipulação de grafos. Essa biblioteca usa listas
de adjacência na sua implementação.
*/

#include "DIGRAPHlists.h"

/* Protótipos de funções do tipo static */
static link NEWnode (Vertex w, link next);
static void LISTSdelete (link a);

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A estrutura digraph 
representa um digrafo. O campo adj é um ponteiro para a matriz de 
adjacências do digrafo. O campo V contém o número de vértices e o campo
A contém o número de arcos do digrafo. */
struct digraph {
   int V; 
   int A; 
   link *adj; 
};

/* A lista de adjacência de um vértice v é composta por nós do tipo 
node. Cada nó da lista corresponde a um arco e contém um vizinho w de v
e o endereço do nó seguinte da lista. Um link é um ponteiro para um
node. */
struct node { 
   Vertex w; 
   link next; 
};

/* A função NEWnode() recebe um vértice w e o endereço next de um nó e
devolve o endereço a de um novo nó tal que a->w == w e a->next == next.
*/
static link NEWnode (Vertex w, link next) { 
   link a = malloc (sizeof (struct node));
   a->w = w; 
   a->next = next;     
   return a;                         
}

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIA: A função DIGRAPHinit() 
constrói um digrafo com vértices 0 1 .. V-1 e nenhum arco. */
Digraph DIGRAPHinit (int V) { 
   Vertex v;
   Digraph G = malloc (sizeof *G);
   G->V = V; 
   G->A = 0;
   G->adj = malloc (V * sizeof (link));
   for (v = 0; v < V; v++) 
      G->adj[v] = NULL;
   return G;
}

/* REPRESENTAÇÂO POR LISTAS DE ADJACÊNCIAS: A função DIGRAPHdestroy()
destrói um digrafo G liberando na memória o espaço que foi alocado em
sua criação */
void DIGRAPHdestroy (Digraph G) {
   Vertex i;
   for (i = 0; i < G->V; i++)
      LISTSdelete (G->adj[i]);
   free (G->adj);
   free (G);
}


/* REPRESENTAÇÂO POR LISTAS DE ADJACÊNCIAS: A função LISTSdelete ()
destrói uma lista de links */
static void LISTSdelete (link a) {
   while (a != NULL) {
      link aux = a;
      a = a->next;
      free (aux);
   }
}


/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIA: A função DIGRAPHinsertA()
insere um arco v-w no digrafo G. A função supõe que v e w são 
distintos, positivos e menores que G->V. Se o digrafo já tem um arco
v-w, a função não faz nada. */
void DIGRAPHinsertA (Digraph G, Vertex v, Vertex w) {
   link a;
   for (a = G->adj[v]; a != NULL; a = a->next) 
      if (a->w == w) return;
   G->adj[v] = NEWnode (w, G->adj[v]);
   G->A++;
}

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIA: A função DIGRAPHremoveA()
remove do digrafo G o arco v-w. A função supõe que v e w são distintos,
positivos e menores que G->V. Se não existe arco v-w, a função não faz
nada. */
void DIGRAPHremoveA (Digraph G, Vertex v, Vertex w) {
   if (G->adj[v] == NULL)
      return;
   if (G->adj[v]->w == w) {
      link aux = G->adj[v];
      G->adj[v] = G->adj[v]->next;
      free (aux);
   }
   else {
      link b = G->adj[v];
      link a = b->next;
      while (a != NULL && a->w != w) {
         b = a;
         a = a->next;
      }
      if (a != NULL) {
         b->next = a->next;
         free (a);
      }
   }
}

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIA: A função DIGRAPHshow()  
imprime, para cada vértice v do digrafo G, em uma linha, todos os
vértices adjacentes a v. */
void DIGRAPHshow (Digraph G) {
   Vertex v;
   for (v = 0; v < G->V; v++) {
      link a = G->adj[v];
      printf ("%d: ", v);
      while (a != NULL) {
         printf ("%d ", a->w);
         a = a->next;
      }
      printf ("\n");
   }
}