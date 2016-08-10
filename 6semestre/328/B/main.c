/*
Nome: Gustavo Estrela de Matos
NUSP: 8536051
Sigla: GUSTAVOE
Data: 09/08/2016
Disciplina: MAC0328

Este arquivo faz parte da tarefa B e tem como objetivo implementar e
testar uma função que escolhe v pontos aleatórios no quadrado
[0, 1) x [0, 1) e ligar por arestas todos os pontos que estiverem a uma
distancia <= d entre si.
*/

#include <stdlib.h>
#include "DIGRAPHlists.h"
#include <math.h>

/* Struct que define um ponto */
typedef struct {
    double x;
    double y;
    int v;
} point;

/* Protótipos de funções */
Digraph rand_near_connected (int V, double d);
point *create_rand_points (int V);
double distance (point v, point w);

/* Função que cria um grafo com V vértices, cada um representando um
ponto aleatório no quadrado [0, 1) x [0, 1), e que possui arestas
conectando dois vértices sse a distância entre os seus pontos
associados é menor ou igual a d */
Digraph rand_near_connected (int V, double d) {
    int i, j;
    point *points = create_rand_points (V);
    Digraph G;
    G = DIGRAPHinit (V);
    for (i = 0; i < V; i++) {
        for (j = i + 1; j < V; j++) {
            if (distance (points[i], points[j]) <= d) {
                DIGRAPHinsertA (G, i, j);
                DIGRAPHinsertA (G, j, i);
            }
        }
    }
    free (points);
    return G;
}

/* Cria um vetor de V pontos aleatórios no quadrado [0, 1) x [0, 1) */
point *create_rand_points (int V) {
    int i;
    point *points = malloc (V * sizeof (point));
    for (i = 0; i < V; i++) {
        point p;
        p.x = rand () / (RAND_MAX + 1.0);
        p.y = rand () / (RAND_MAX + 1.0);
        p.v = i;
        points[i] = p;
    }
    return points;
}

/* Calcula a distância entre dois pontos v e w */
double distance (point v, point w) {
    return sqrt ((v.x - w.x) * (v.x - w.x) +
                 (v.y - w.y) * (v.y - w.y));
}

/* Testa a função rand_near_connected () e, se útil, mostra o grafo
criado */
int main (int argc, char **argv) {
    int V;
    double d;
    Digraph G;
    if (argc != 3)
        return 0;
    V = atoi (argv[1]);
    d = atof (argv[2]);
    G = rand_near_connected (V, d);
    printf ("Numero de arestas produzidas: %d\n", G->A / 2);
    if (G->V < 7 && G->A < 21) {
        DIGRAPHshow (G);
    }
    DIGRAPHdestroy (G);
    return 0;
}