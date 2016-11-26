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

#include "PQ.h"

#define Vertex int

/* Este módulo implementa uma fila priorizada em um heap.
// O heap é armazenado num vetor pq[1..N] de vértices. (A posição 0 
// do vetor não é usada.) */

static Vertex *pq; 
static int N;

/* Funções do tipo static */
static void exch (int i, int j);
static void fixUp (int k, double prty[]);
static void fixDown (int k, double prty[]);

/* As prioridades são dadas em um vetor prty indexado por vértices: 
// o vértice na posição k de pq tem prty[pq[k]]. O heap é
// caracterizado pela propriedade  prty[pq[k/2]] ≤ prty[pq[k]] 
// para k = 2, ..., N. Portanto, o vértice pq[1] tem prioridade 
// mínima. */
#define greater_(i, j) (prty[pq[i]] > prty[pq[j]] ? 1 : 0)

/* O vetor qp[0..N-1] é o "inverso" de pq: para cada vértice v, 
// qp[v] é o único índice tal que pq[qp[v]] == v.
// É claro que qp[pq[i]] == i para todo i. */
static int *qp; 

/* Supõe-se que teremos sempre N ≤ maxN. */
/* Inicializa uma fila de prioridade. O valor maxN determina o tamanho
// máximo dessa fila.*/
void PQinit (int maxN) {
   pq = malloc ((maxN+1) * sizeof (Vertex));
   qp = malloc (maxN * sizeof (int));
   N = 0;
}

/* Verifica se a fila de prioridade está vazia. Retorna 0 se não e 1 se
// sim. */
int PQempty (void) {
   return N == 0;
}

/* A função PQinsert() insere um vértice v na fila de prioridade. O 
// vetor prty[] determina a prioridade dos vértices. */
void PQinsert (Vertex v, double prty[]) {
   qp[v] = ++N;
   pq[N] = v;
   fixUp (N, prty);
}

/* A função PQdelmin() remove o elemento mínimo da fila de prioridade.
// Além de remover, essa função retorna o elemento mínimo da fila. */
Vertex PQdelmin (double prty[]) { 
   exch (1, N);
   --N;
   fixDown (1, prty);
   return pq[N+1];
}

/* A função PQdec() decrementa a prioridade de um vértice w e atualiza
// a fila de prioridade. */
void PQdec (Vertex w, double prty[]) { 
   fixUp (qp[w], prty); 
}

/* A função exch() Troca os elementos i e j de posição em pq e atualiza
// qp */
static void exch (int i, int j) {
   Vertex t;
   t = pq[i]; pq[i] = pq[j]; pq[j] = t;
   qp[pq[i]] = i;
   qp[pq[j]] = j;
}

/* A função fixUp() atualiza pq e qp para todo indice menor que k de pq
// para fazer valer as condições iniciais definidas para pq. */
static void fixUp (int k, double prty[]) {
   while (k > 1 && greater_(k/2, k)) {
      exch (k/2, k);
      k = k/2;
   }
}

static void fixDown (int k, double prty[]) { 
   int j;
   while (2*k <= N) { 
      j = 2*k;
      if (j < N && greater_(j, j+1)) j++;
      if (!greater_(k, j)) break;
      exch (k, j); 
      k = j;
   }
}

/* A função PQfree() libera da memória o espaço alocado para contrução
// da fila. */
void PQfree (void) { 
   free (pq);
   free (qp);
}
