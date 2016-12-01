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
// O código desse arquivo foi inspirado no código disponível em:
// https://www.ime.usp.br/~pf/algoritmos_para_grafos/aulas/solutions/
// heap.html
//
////////////////////////////////////////////////////////////// */

#include <stdlib.h>

#define Vertex int

/* Este módulo implementa uma fila priorizada em um heap.
// O heap é armazenado num vetor pq[1..N] de vértices. (A posição 0 
// do vetor não é usada.) */

/* As prioridades são dadas em um vetor prty indexado por vértices: 
// o vértice na posição k de pq tem prty[pq[k]]. O heap é
// caracterizado pela propriedade  prty[pq[k/2]] ≤ prty[pq[k]] 
// para k = 2, ..., N. Portanto, o vértice pq[1] tem prioridade 
// mínima. */

/* O vetor qp[0..N-1] é o "inverso" de pq: para cada vértice v, 
// qp[v] é o único índice tal que pq[qp[v]] == v.
// É claro que qp[pq[i]] == i para todo i. */

/* Inicializa uma fila de prioridade. O valor maxN determina o tamanho
// máximo dessa fila.*/
void PQinit (int maxN);

/* Verifica se a fila de prioridade está vazia. Retorna 0 se não e 1 se
// sim. */
int PQempty (void);

/* A função PQinsert() insere um vértice v na fila de prioridade. O 
// vetor prty[] determina a prioridade dos vértices. */
void PQinsert (Vertex v, double prty[]);

/* A função PQdelmin() remove o elemento mínimo da fila de prioridade.
// Além de remover, essa função retorna o elemento mínimo da fila. */
Vertex PQdelmin (double prty[]);

/* A função PQdec() decrementa a prioridade de um vértice w e atualiza
// a fila de prioridade. */
void PQdec (Vertex w, double prty[]);

/* A função PQfree() libera da memória o espaço alocado para contrução
// da fila. */
void PQfree (void);
