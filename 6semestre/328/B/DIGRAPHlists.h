/*
Nome: Gustavo Estrela de Matos
NUSP: 8536051
Sigla: GUSTAVOE
Data: 08/08/2016
Disciplina: MAC0328

Este arquivo faz parte da tarefa B e tem como objetivo definir uma 
biblioteca para manipulação de grafos. Essa biblioteca usa listas
de adjacência na sua implementação.
*/

#ifndef DIGRAPH_LISTS_H_
#define DIGRAPH_LISTS_H_

/* Inclusão de outras interfaces necessárias para esta interface */
#include <stdlib.h>
#include <stdio.h>

/* Definições de constantes */
#define Vertex int

/* A lista de adjacência de um vértice v é composta por nós do tipo 
node. Cada nó da lista corresponde a um arco e contém um vizinho w de v
e o endereço do nó seguinte da lista. Um link é um ponteiro para um
node. */
typedef struct node *link;
struct node { 
   Vertex w; 
   link next; 
};

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIAS: A estrutura digraph 
representa um digrafo. O campo adj é um ponteiro para a matriz de 
adjacências do digrafo. O campo V contém o número de vértices e o campo
A contém o número de arcos do digrafo. */
struct digraph {
   int V; 
   int A; 
   link *adj; 
};

/* Um Digraph é um ponteiro para um digraph, ou seja, um Digraph contém
o endereço de um digraph. */
typedef struct digraph *Digraph;

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIA: A função DIGRAPHinit() 
constrói um digrafo com vértices 0 1 .. V-1 e nenhum arco. */
Digraph DIGRAPHinit (int V);

/* REPRESENTAÇÂO POR LISTAS DE ADJACÊNCIAS: A função DIGRAPHdestroy()
destrói um digrafo G liberando na memória o espaço que foi alocado em
sua criação */
void DIGRAPHdestroy (Digraph G);

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIA: A função DIGRAPHinsertA()
insere um arco v-w no digrafo G. A função supõe que v e w são 
distintos, positivos e menores que G->V. Se o digrafo já tem um arco
v-w, a função não faz nada. */
void DIGRAPHinsertA (Digraph G, Vertex v, Vertex w);

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIA: A função DIGRAPHremoveA()
remove do digrafo G o arco v-w. A função supõe que v e w são distintos,
positivos e menores que G->V. Se não existe arco v-w, a função não faz
nada. */
void DIGRAPHremoveA (Digraph G, Vertex v, Vertex w);

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIAS: A função DIGRAPHoutdeg() 
calcula o grau de saída do vértice v do grafo G. */
int DIGRAPHoutdeg (Digraph G, Vertex v);

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIAS: A função DIGRAPHindeg() 
calcula o grau de entrada do vértice v do grafo G. A função supõe que
v é menor que G->V */
int DIGRAPHindeg (Digraph G, Vertex w);

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIA: A função DIGRAPHshow()  
imprime, para cada vértice v do digrafo G, em uma linha, todos os
vértices adjacentes a v. */
void DIGRAPHshow (Digraph G);

#endif