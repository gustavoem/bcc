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

/* TODO: escrever sobre essa função */
int main (int argc, char **argv) {
    Digraph G;
    Vertex *p;
    int i, V, A, s, impl, seed;
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
    p = path (G->father, 3);
    if (p != NULL) {
        for (i = 0; p[i] != 3; i++)
            printf ("%d ", p[i]);
        printf ("%d\n", p[i]);
        free (p);
    }
    DIGRAPHdestroy (G);
    return 0;
}
