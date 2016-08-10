/*
Nome: Gustavo Estrela de Matos
NUSP: 8536051
Sigla: GUSTAVOE
Data: 08/08/2016
Disciplina: MAC0328

Este arquivo faz parte da tarefa B e tem como objetivo implementar e 
testar uma função que escolhe v pontos aleatórios no quadrado 
[0, 1) x [0, 1) e ligar por arestas todos os pontos que estiverem a uma
distancia <= d entre si.
*/

#include <stdlib.h>
#include "DIGRAPHlists.h"

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
    int i;
    point *points = create_rand_points (V);
    return NULL;
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

int main (int argc, char **argv) {
    int V;
    double d;
    if (argc != 3)
        return 0;
    V = atoi (argv[1]);
    d = atof (argv[2]);

    return 0;
}