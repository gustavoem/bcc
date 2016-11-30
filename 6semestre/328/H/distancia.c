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
// TODO: escrever sobre o que essa tarefa é
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

void calcDeltaxy (Digraph G) {
    Vertex vd = -1, wd = -1, v;
    double maxdeltavw = 0;
    for (v = 0; v < G->V; v++) {
        link a;
        for (a = G->adj[v]; a != NULL; a = a->next)
        {
            double deltavw = a->cst - (G->dist[a->w] - G->dist[v]);
            if (deltavw > maxdeltavw) {
                /*printf ("\ndelta[%d-%d] = %5.4f. d[%d] = %5.4f; 
 *                      d[%d] = %5.4f; c[v-w] = %5.4f", v, a->w, deltavw,
 *                       v, G->dist[v], a->w, G->dist[a->w], a->cst);*/
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

/* TODO: escrever sobre essa função */
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
    G = DIGRAPHrand1 (V, A, 0, 1);
    if (V < 30)
        DIGRAPHshow (G); 
    runDijkstra (G, impl, s);
    calcDeltaxy (G);
    p = DIGRAPHdiameter (G);
    free (p);
    DIGRAPHdestroy (G);
    return 0;
}
