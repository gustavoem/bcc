/*
Nome: Gustavo Estrela de Matos
NUSP: 8536051
Sigla: GUSTAVOE
Data: 08/08/2016
Disciplina: MAC0328

Este arquivo faz parte da tarefa B e tem como objetivo definir uma 
biblioteca para manipulação de grafos. Essa biblioteca usa matrizes
de adjacência na sua implementação.
*/

#ifndef DIGRAPH_MATRIX_H_
#define DIGRAPH_MATRIX_H_

/* Inclusão de outras interfaces necessárias para esta interface */
#include <stdlib.h>
#include <stdio.h>

/* Definições de constantes */
#define Vertex int

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A estrutura digraph 
representa um digrafo. O campo adj é um ponteiro para a matriz de 
adjacências do digrafo. O campo V contém o número de vértices e o campo
A contém o número de arcos do digrafo. */
struct digraph;

/* Um Digraph é um ponteiro para um digraph, ou seja, um Digraph contém
o endereço de um digraph. */
typedef struct digraph *Digraph;

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função DIGRAPHinit()
constrói um digrafo com vértices 0 1 .. V-1 e nenhum arco. */
Digraph DIGRAPHinit (int V);

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função DIGRAPHinsertA()
insere um arco v-w no digrafo G. A função supõe que v e w são 
distintos, positivos e menores que G->V. Se o digrafo já tem um arco 
v-w, a função não faz nada. */
void DIGRAPHinsertA (Digraph G, Vertex v, Vertex w);

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função DIGRAPHremoveA()
remove do digrafo G o arco v-w. A função supõe que v e w são distintos,
positivos e menores que G->V. Se não existe arco v-w, a função não faz
nada. */
void DIGRAPHremoveA (Digraph G, Vertex v, Vertex w);

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função DIGRAPHshow()  
imprime, para cada vértice v do digrafo G, em uma linha, todos os
vértices adjacentes a v. */
void DIGRAPHshow (Digraph G);

#endif