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
// Data:       2016-10-01
//
// Este arquivo faz parte da tarefa G
// da disciplina MAC0328 e tem como objetivo estudar a distância
// média de vértices em um grafo do tipo WS (referência a Watts e
// Strogatz).
//
////////////////////////////////////////////////////////////// */

#include <stdlib.h>
#include <stdio.h>
#include "DIGRAPHlists.h"

/* Definições */
#define Graph Digraph

/* Protótipo das funções */

/* Esta função recebe pela entrada padrão uma sequencia de entradas no
formato "V d k" até que V seja -1. Para cada uma das entradas o
programa cria um grafo do tipo WS e mostra na saída padrão a distância
média dos vértices desse grafo criado. */
int main (int argc, char **argv) {
    int V = 0, k;
    double d;
    float meand;
    Graph G;
    printf ("> ");
    scanf ("%d", &V);
    while (V != -1) {
        scanf ("%lf %d", &d, &k);
        G = GRAPHws (V, d, k);
        meand = (float) GRAPHsmallWorld (G);
        printf ("  distancia media: %3.2f", meand);
        DIGRAPHdestroy (G);
        printf ("\n\n> ");
        scanf ("%d", &V);
    }
    printf ("\n");
    return 0;
}
