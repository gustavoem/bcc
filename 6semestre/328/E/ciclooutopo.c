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
// Data:       2016-08-29
//
// Este arquivo faz parte da tarefa E
// da disciplina MAC0328 e tem como objetivo testar a função 
// DIGRAPHcycleOrTopo () da biblioteca DIGRAPHmatrix
//
////////////////////////////////////////////////////////////// */

#include <stdlib.h>
#include <stdio.h>
#include "DIGRAPHmatrix.h"

/* Esta função recebe digrafo descrito na entrada padrão e, usando a
função DIGRAPHcycleOrTopo () imprime um ciclo ou uma listagem 
topologica dos vértices. */
int main () {
    int i;
    int V, A;
    Digraph G;
    scanf ("%d\n%d", &V, &A);
    G = DIGRAPHinit (V);
    for (i = 0; i < A; i++) {
        int v, w;
        scanf ("%d %d", &v, &w);
        DIGRAPHinsertA (G, v, w);
    }
    DIGRAPHshow (G);
    i = DIGRAPHcycleOrTopo (G);
    printf ("\nans: %d\n", i);
    return 0;
}
