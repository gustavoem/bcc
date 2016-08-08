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

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A estrutura digraph 
representa um digrafo. O campo adj é um ponteiro para a matriz de 
adjacências do digrafo. O campo V contém o número de vértices e o campo
A contém o número de arcos do digrafo. */
struct digraph;

/* Um Digraph é um ponteiro para um digraph, ou seja, um Digraph contém
o endereço de um digraph. */
typedef struct digraph *Digraph;

/* A lista de adjacência de um vértice v é composta por nós do tipo 
node. Cada nó da lista corresponde a um arco e contém um vizinho w de v
e o endereço do nó seguinte da lista. Um link é um ponteiro para um
node. */
typedef struct node *link;
struct node;

#endif