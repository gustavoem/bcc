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
// Este arquivo faz parte da tarefa G
// Essa tarefa consiste em estudar o problema dos caminhos dos 
// custos mínimos. Este arquivo testa as diferentes 
// implementações do algoritmo de Dijkstra, implementadas na
// biblioteca wDIGRAPHlists.
//
////////////////////////////////////////////////////////////// */

#include <stdlib.h>
#include <stdio.h>
#include "wDIGRAPHlists.h"

/* Definições */
#define Graph Digraph

/* Protótipo das funções */
void runDijkstra (Digraph G, Vertex s, int impl);
void calcDeltaxy (Digraph G);

/* Chama o algoritmo de Dijkstra, partindo do vértice s, usando a
// implementação impl. */
void runDijkstra (Digraph G, Vertex s, int impl) {
    switch (impl) {
        case 0:
            DIGRAPHsptD0 (G, s);
            break;
        case 1:
            DIGRAPHsptD1 (G, s);
            break;
        case 2:
            DIGRAPHsptD2 (G, s);
    }
}

/* Dado um digrafo G que passou por um dos algoritmos de Dijkstra que
// calcula uma SPT, essa função devolve o maior delta[x-y] para x-y
// fora da árvore. O valor delta[x-y] é o maior número que podemos
// subtrair do custo do arco x-y sem fazer que a SPT desse grafo,
// partindo do mesmo elemento, mude.*/
void calcDeltaxy (Digraph G) {
    Vertex vd = -1, wd = -1, v;
    double maxdeltavw = 0;
    for (v = 0; v < G->V; v++) {
        link a;
        for (a = G->adj[v]; a != NULL; a = a->next)
        {
            double deltavw = a->cst - (G->dist[a->w] - G->dist[v]);
            if (deltavw > maxdeltavw) {
                vd = v;
                wd = a->w;
                maxdeltavw = deltavw;
            }
        }
    }
    printf ("Maior delta[v-w]: %4.3f.", maxdeltavw);
    if (maxdeltavw > 0)
        printf (" v: %d, w: %d", vd, wd);
    printf ("\n");
}

/* Esse programa recebe por argumentos os valores V A s impl e seed.
// Esses argumentos determinam um grafo pseudo-aleatório de V vértices
// e A arestas que será usado para rodar uma implementação impl do
// algoritmo de Dijkstra. Primeiro, calculamos o diametro desse 
// digrafo. Depois, calculamos o maior valor de delta[x-y]. Quando 
// conveniente, essas informações são mostradas na tela.  */
int main (int argc, char **argv) {
    Digraph G;
    Vertex *p;
    int V, A, s, impl, seed;
    if (argc != 6) {
        printf ("Uso:\n./distancia V A s impl seed\n.");
        return 0;
    }   
    else {
        V = atoi (argv[1]);
        A = atoi (argv[2]);
        s = atoi (argv[3]);
        impl = atoi (argv[4]);
        seed = atoi (argv[5]);
    }
    srand (seed);
    G = DIGRAPHrand2 (V, A, 0, 1);
    if (V < 30)
        DIGRAPHshow (G); 
    runDijkstra (G, impl, s);
    calcDeltaxy (G);
    p = DIGRAPHdiameter (G, impl);
    free (p);
    DIGRAPHdestroy (G);
    return 0;
}
