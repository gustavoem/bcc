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
// Data:       2016-11-25
//
// Este arquivo faz parte da tarefa H
// da disciplina MAC0328 e tem como objetivo imlpementar uma
// biblioteca para manipulação de grafos com custos nos arcos.
// Essa biblioteca usa listas de adjacência na sua implementação.
//
////////////////////////////////////////////////////////////// */

#ifndef WDIGRAPH_LISTS_H_
#define WDIGRAPH_LISTS_H_

/* Inclusão de outras interfaces necessárias para esta interface */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/* Definições de constantes */
#define Vertex int
#define Graph Digraph

/* A lista de adjacência de um vértice v é composta por nós do tipo
node. Cada nó da lista corresponde a um arco e contém um vizinho w de v;
o endereço do nó seguinte da lista; e o custo desse arco. Um link é um
ponteiro para um node. */
typedef struct node *link;
struct node {
    Vertex w;
    double cst;
    link next;
};

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIAS: A estrutura digraph
representa um digrafo. 
- O campo adj é um ponteiro para a matriz de
adjacências do digrafo.
- O campo V contém o número de vértices.
- O campo A contém o número de arcos do digrafo.
vértice
- O campo dist é utilizado para determinar a distância (ou preço)
de um vértice.
- O campo father é utilizado para determinar o pai de um vértice em
uma árvore. */
struct digraph {
    int V;
    int A;
    link *adj;
    int *dist;
    Vertex *father;
};

/* Um Digraph é um ponteiro para um digraph, ou seja, um Digraph contém
o endereço de um digraph. */
typedef struct digraph *Digraph;

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIAS: A função DIGRAPHinit()
constrói um digrafo com vértices 0 1 .. V-1 e nenhum arco. */
Digraph DIGRAPHinit (int V);

/* REPRESENTAÇÂO POR LISTAS DE ADJACÊNCIAS: A função DIGRAPHdestroy()
destrói um digrafo G liberando na memória o espaço que foi alocado em
sua criação */
void DIGRAPHdestroy (Digraph G);

/* REPRESENTAÇÂO POR LISTAS DE ADJACÊNCIAS: A função
DIGRAPHdestroyDFSinfo () libera o espaço alocado para estrutura do
digrafo nos vetores father e dist, criados em DIGRAPHdist () */
void DIGRAPHdestroydistinfo (Digraph G);

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIAS: A função DIGRAPHinsertA()
insere um arco v-w no digrafo G. A função supõe que v e w são
distintos, positivos e menores que G->V. Se o digrafo já tem um arco
v-w, a função não faz nada. */
void DIGRAPHinsertA (Digraph G, Vertex v, Vertex w, double cst);

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIAS: A função DIGRAPHinsertE()
insere uma aresta v-w no digrafo G. A função supõe que v e w são
distintos, positivos e menores que G->V. Se o digrafo já tem uma aresta
v-w, a função não faz nada. */
void GRAPHinsertE (Graph G, Vertex v, Vertex w, double cst);

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIAS: A função DIGRAPHremoveA()
remove do digrafo G o arco v-w. A função supõe que v e w são distintos,
positivos e menores que G->V. Se não existe arco v-w, a função não faz
nada. */
void DIGRAPHremoveA (Digraph G, Vertex v, Vertex w);

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIAS: Esta função calcula a
distância de um vértice s a cada vértice de G. O percorrimento dos
vértices feito nessa função gera uma árvore, armazenada no vetor father
da estrutura de G. */
void DIGRAPHdist (Digraph G, Vertex s);

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIAS: A função DIGRAPHshow()
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

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIAS: a função
GRAPHclosePoints () escolhe V pontos aleatórios no quadrado
[0, 1)x[0,1) e cria um vértice para cada um desses pontos. Depois,
liga-se com arestas cada par de vértices v e w tal que a distância
entre os pontos representados por esses vértices é menor ou igual ao
parametro d. */
Graph GRAPHclosePoints (int V, double d);

#endif
