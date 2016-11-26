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

/* TODO: escrever sobre essa função */
int main (int argc, char **argv) {
    Graph G;
    Vertex *p;
    int i;
    if (argc > 1)
        srand (atoi (argv[1]));
    G = GRAPHrand2 (10, 4, 0, 1);
    DIGRAPHshow (G);
    DIGRAPHsptD2 (G, 0);
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
