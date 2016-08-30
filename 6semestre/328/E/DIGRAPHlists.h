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
// da disciplina MAC0328 e tem como objetivo definir uma
// biblioteca para manipulação de grafos. Essa biblioteca usa listas
// de adjacência na sua implementação.
//
////////////////////////////////////////////////////////////// */

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
    int *pre;
    int *pos;
    Vertex *father;
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

/* REPRESENTAÇÂO POR LISTAS DE ADJACÊNCIAS: A função 
DIGRAPHdistroyDFSinfo () libera o espaço alocado para estrutura do
digrafo pelos vetores pre, pos e father. */
void DIGRAPHdestroyDFSinfo (Digraph G);

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

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIAS: A função DIGRAPHrand1 ()
constrói um digrafo aleatório com vértices 0..V-1 e exatamente A
arcos. (As duas pontas de cada arco devem ser diferentes.) A função
supõe que A <= V*(V-1). Se A for próximo de V*(V-1), a função pode
consumir muito tempo. (Código inspirado no Programa 17.7 de
Sedgewick.) */
Digraph DIGRAPHrand1 (int V, int A);

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIAS: A função GRAPHrand1 ()
constrói um grafo aleatório com vértices 0..V-1 e exatamente E arestas
(As duas pontas de cada aresta devem ser diferentes.). A função
supõe que E <= V*(V-1)/2. Se E for próximo de V*(V-1)/2, a função pode
consumir muito tempo. (Código inspirado no Programa 17.7 de
Sedgewick.) */
Digraph GRAPHrand1 (int V, int E);

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIAS: a função DIGRAPHrand2 ()
constrói um digrafo aleatório com vértices 0..V-1 e número esperado de
arcos igual a A. (As duas pontas de cada arco devem ser diferentes.) A
função supõe que V >= 2 e A <= V*(V-1). (Código inspirado no Program
17.8 de Sedgewick.) */
Digraph DIGRAPHrand2 (int V, int A);

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIAS: a função GRAPHrand2 ()
constrói um grafo aleatório com vértices 0..V-1 e número esperado de
arestas igual a E. (As duas pontas de cada aresta devem ser
diferentes.) A função supõe que V >= 2 e E <= V*(V-1)/2. (Código
inspirado no Program 17.8 de Sedgewick.) */
Digraph GRAPHrand2 (int V, int E);

#endif
