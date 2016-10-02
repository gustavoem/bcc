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
    Vertex v;
    double meand;
    Graph G;
    G = DIGRAPHinit (5);
    GRAPHaddRandEdges (G, 1);
    DIGRAPHshow (G);
    meand = GRAPHsmallWorld (G);
    printf ("\nDistancia media: %3.2f", meand);
    DIGRAPHdestroy (G);
    printf ("\n");
    return 0;
}
