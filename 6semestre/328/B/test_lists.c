#include <stdio.h>
#include "DIGRAPHlists.h"

/*
Nome: Gustavo Estrela de Matos
NUSP: 8536051
Sigla: GUSTAVOE
Data: 09/08/2016
Disciplina: MAC0328

Este arquivo faz parte da tarefa B e tem como objetivo testar as 
bibliotecas criadas para manipulação de grafos
*/

/* Apenas printa na tela uma mensagem de erro */
void test_feedback (int result) {
    if (result)
        printf ("OK!");
    else
        printf ("Falhou!");
    printf ("\n");
}

int main () {
    Digraph d;
    d = DIGRAPHinit (6);
    printf ("Teste de inserção de arco: ");
    DIGRAPHinsertA (d, 1, 2);
    test_feedback (d->A == 1);
    DIGRAPHinsertA (d, 2, 0);
    DIGRAPHinsertA (d, 2, 3);
    printf ("Teste de grau de saída de vértice: ");
    test_feedback (DIGRAPHoutdeg (d, 2) == 2);
    printf ("Teste de grau de entrada de vértice: ");
    test_feedback (DIGRAPHindeg (d, 2) == 1);
    DIGRAPHremoveA (d, 2, 0);
    DIGRAPHremoveA (d, 1, 2);
    DIGRAPHdestroy (d);
    return 0;
}