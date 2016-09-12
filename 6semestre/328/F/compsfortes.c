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
// Data:       2016-09-11
//
// Este arquivo faz parte da tarefa F
// da disciplina MAC0328 e tem como objetivo estudar como o tamanho
// das maiores componentes fortes de um digrafo aleatório de V vértices
// e A arcos evolui em função de A.
//
////////////////////////////////////////////////////////////// */

#include <stdlib.h>
#include <stdio.h>
#include "DIGRAPHlists.h"

/* Esta função recebe como parametros, em argv, V e k. São gerados 
então k grafos aleatórios com V vértices e 
TODO: terminar essa descrição */
int main (int argc, char **argv) {
    int V, A, k, i;
    Digraph G;
    if (argc != 3)
        return 0;
    V = atoi (argv[1]);
    k = atof (argv[2]);

    G = DIGRAPHrand1 (V, 2 * V);
    DIGRAPHshow (G);
    DIGRAPHscKS (G);
    printf ("\n");
    for (i = 0; i < G->V; i++)
        printf ("%d ", G->sc[i]);
    printf ("\n");
    DIGRAPHdestroy (G);
    return 0;
}
