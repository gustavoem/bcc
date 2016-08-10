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
static Vertex randV (Digraph G);

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

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIAS: A função DIGRAPHoutdeg() 
calcula o grau de saída do vértice v do grafo G. A função supõe que
v é menor que G->V */
int DIGRAPHoutdeg (Digraph G, Vertex v) {
   int count = 0;
   link a = G->adj[v];
   while (a != NULL) {
      count++;
      a = a->next;
   }
   return count;
}

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIAS: A função DIGRAPHindeg() 
calcula o grau de entrada do vértice v do grafo G. A função supõe que
v é menor que G->V */
int DIGRAPHindeg (Digraph G, Vertex w) {
   int count = 0;
   Vertex v;
   for (v = 0; v < G->V; v++) {
      link a = G->adj[v];
      while (a != NULL && a->w != w)
         a = a->next;
      if (a != NULL)
         count++;
   }
   return count;
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
      G->A--;
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
         G->A--;
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


/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIAS: A função DIGRAPHrand1 ()
constrói um digrafo aleatório com vértices 0..V-1 e exatamente A
arcos. (As duas pontas de cada arco devem ser diferentes.) A função
supõe que A <= V*(V-1). Se A for próximo de V*(V-1), a função pode
consumir muito tempo. (Código inspirado no Programa 17.7 de 
Sedgewick.) */
Digraph DIGRAPHrand1 (int V, int A) { 
   Vertex v, w;
   Digraph G = DIGRAPHinit (V);
   while (G->A < A) {
      v = randV (G);
      w = randV (G);
      if (v != w) 
         DIGRAPHinsertA (G, v, w);
   }
   return G;
}

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIAS: A função GRAPHrand1 ()
constrói um grafo aleatório com vértices 0..V-1 e exatamente E arestas 
(As duas pontas de cada aresta devem ser diferentes.). A função
supõe que E <= V*(V-1)/2. Se E for próximo de V*(V-1)/2, a função pode
consumir muito tempo. (Código inspirado no Programa 17.7 de 
Sedgewick.) */
Digraph GRAPHrand1 (int V, int E) { 
   Vertex v, w;
   Digraph G = DIGRAPHinit (V);
   while (G->A / 2 < E) {
      v = randV (G);
      w = randV (G);
      if (v != w) 
      {
         DIGRAPHinsertA (G, v, w);
         DIGRAPHinsertA (G, w, v);
      }
   }
   return G;
}

/* A função randV() devolve um vértice aleatório do digrafo G. */
static Vertex randV (Digraph G) { 
   double r;
   r = rand () / (RAND_MAX + 1.0);
   return r * G->V;
}

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIAS: a função DIGRAPHrand2 ()
constrói um digrafo aleatório com vértices 0..V-1 e número esperado de
arcos igual a A. (As duas pontas de cada arco devem ser diferentes.) A
função supõe que V >= 2 e A <= V*(V-1). (Código inspirado no Program
17.8 de Sedgewick.) */
Digraph DIGRAPHrand2 (int V, int A) { 
   Vertex v, w;
   double p = (double) A / V / (V-1);
   Digraph G = DIGRAPHinit (V);
   for (v = 0; v < V; v++)
      for (w = 0; w < V; w++)
         if (v != w && rand () < p * (RAND_MAX + 1.0))
            DIGRAPHinsertA (G, v, w);
   return G;
}

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIAS: a função GRAPHrand2 ()
constrói um grafo aleatório com vértices 0..V-1 e número esperado de 
arestas igual a E. (As duas pontas de cada aresta devem ser 
diferentes.) A função supõe que V >= 2 e E <= V*(V-1)/2. (Código
inspirado no Program 17.8 de Sedgewick.) */
Digraph GRAPHrand2 (int V, int E) { 
   Vertex v, w;
   double p = (double) 2 * E / V / (V-1);
   Digraph G = DIGRAPHinit (V);
   for (v = 0; v < V; v++)
      for (w = 0; w < V; w++)
         if (v != w && rand () < p * (RAND_MAX + 1.0))
         {
            DIGRAPHinsertA (G, v, w);
            DIGRAPHinsertA (G, w, v);
         }
   return G;
}