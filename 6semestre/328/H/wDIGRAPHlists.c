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
// Este arquivo faz parte da tarefa H
// da disciplina MAC0328 e tem como objetivo imlpementar uma
// biblioteca para manipulação de grafos com custos nos arcos.
// Essa biblioteca usa listas de adjacência na sua implementação.
//
////////////////////////////////////////////////////////////// */

#include "wDIGRAPHlists.h"

#define TRUE 1

static Vertex *frj;

/* Tipo auxiliar privado para esta biblioteca. */
typedef struct {
    double x;
    double y;
} point;

/* Protótipos de funções do tipo static */
static link NEWnode (Vertex w, double cst, link next);
static void LISTSdelete (link a);
static Vertex randV (Digraph G);
static double randC (double cmin, double cmax);
static point *createRandPoints (int n);
static void NEWdist (Digraph G);
static void NEWfather (Digraph G);
static double findINFINITE (Digraph G);
static int checkDist (Digraph G);

/* A função NEWnode() recebe um vértice w e o endereço next de um nó e
devolve o endereço a de um novo nó tal que a->w == w e a->next == next.
*/
static link NEWnode (Vertex w, double cst, link next) {
    link a = malloc (sizeof (struct node));
    a->w = w;
    a->cst = cst;
    a->next = next;
    return a;
}

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIA: A função DIGRAPHinit()
constrói um digrafo com vértices 0 1 .. V-1 e nenhum arco. */
Digraph DIGRAPHinit (int V) {
    Vertex v;
    Digraph G = malloc (sizeof *G);
    G->V = V;
    G->A = 0;
    G->adj = malloc (V * sizeof (link));
    for (v = 0; v < V; v++)
        G->adj[v] = NULL;
    G->father = NULL;
    G->dist = NULL;
    return G;
}

/* REPRESENTAÇÂO POR LISTAS DE ADJACÊNCIAS: A função DIGRAPHdestroy()
destrói um digrafo G liberando na memória o espaço que foi alocado em
sua criação */
void DIGRAPHdestroy (Digraph G) {
    Vertex i;
    for (i = 0; i < G->V; i++)
        LISTSdelete (G->adj[i]);
    free (G->adj);
    DIGRAPHdestroyFather (G);
    DIGRAPHdestroyDist (G);
    free (G);
}

/* REPRESENTAÇÂO POR LISTAS DE ADJACÊNCIAS: A função LISTSdelete ()
destrói uma lista de links */
static void LISTSdelete (link a) {
    while (a != NULL) {
        link aux = a;
        a = a->next;
        free (aux);
    }
}

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIA: A função DIGRAPHinsertA()
insere um arco v-w no digrafo G. A função supõe que v e w são
distintos, positivos e menores que G->V. Se o digrafo já tem um arco
v-w, a função não faz nada. */
void DIGRAPHinsertA (Digraph G, Vertex v, Vertex w, double cst) {
    link a;
    for (a = G->adj[v]; a != NULL; a = a->next)
        if (a->w == w) return;
    G->adj[v] = NEWnode (w, cst, G->adj[v]);
    G->A++;
}

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIAS: A função DIGRAPHinsertE()
insere uma aresta v-w no digrafo G. A função supõe que v e w são
distintos, positivos e menores que G->V. Se o digrafo já tem uma aresta
v-w, a função não faz nada. */
void GRAPHinsertE (Graph G, Vertex v, Vertex w, double cst) {
    link a;
    for (a = G->adj[v]; a != NULL; a = a->next)
        if (a->w == w) return;
    G->adj[v] = NEWnode (w, cst, G->adj[v]);
    G->adj[w] = NEWnode (v, cst, G->adj[w]);
    G->A++;
}

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIA: A função DIGRAPHremoveA()
remove do digrafo G o arco v-w. A função supõe que v e w são distintos,
positivos e menores que G->V. Se não existe arco v-w, a função não faz
nada. */
void DIGRAPHremoveA (Digraph G, Vertex v, Vertex w) {
    if (G->adj[v] == NULL)
        return;
    if (G->adj[v]->w == w) {
        link aux = G->adj[v];
        G->adj[v] = G->adj[v]->next;
        free (aux);
        G->A--;
    }
    else {
        link b = G->adj[v];
        link a = b->next;
        while (a != NULL && a->w != w) {
            b = a;
            a = a->next;
        }
        if (a != NULL) {
            b->next = a->next;
            free (a);
            G->A--;
        }
    }
}

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIA: A função DIGRAPHshow()
imprime, para cada vértice v do digrafo G, em uma linha, todos os
vértices adjacentes a v. */
void DIGRAPHshow (Digraph G) {
    Vertex v;
    if (G->V > 30) return;
    for (v = 0; v < G->V; v++) {
        link a = G->adj[v];
        printf ("%d: ", v);
        while (a != NULL) {
            printf ("%6d ", a->w);
            a = a->next;
        }
        printf ("\n");
        printf ("   ");
        a = G->adj[v];
        while (a != NULL) {
            printf ("%6.2f ", a->cst);
            a = a->next;
        }
        printf ("\n");
    }
}

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIAS: A função DIGRAPHrand1 ()
constrói um digrafo aleatório com vértices 0..V-1 e exatamente A
arcos. (As duas pontas de cada arco devem ser diferentes.) A função
supõe que A <= V*(V-1). Se A for próximo de V*(V-1), a função pode
consumir muito tempo. (Código inspirado no Programa 17.7 de
Sedgewick.) */
Digraph DIGRAPHrand1 (int V, int A, double cmin, double cmax) {
    Vertex v, w;
    Digraph G = DIGRAPHinit (V);
    while (G->A < A) {
        v = randV (G);
        w = randV (G);
        if (v != w)
        {
            double cst = randC (cmin, cmax);
            DIGRAPHinsertA (G, v, w, cst);
        }
    }
    return G;
}

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIAS: A função GRAPHrand1 ()
constrói um grafo aleatório com vértices 0..V-1 e exatamente E arestas
(As duas pontas de cada aresta devem ser diferentes.). A função
supõe que E <= V*(V-1)/2. Se E for próximo de V*(V-1)/2, a função pode
consumir muito tempo. (Código inspirado no Programa 17.7 de
Sedgewick.) */
Graph GRAPHrand1 (int V, int E, double cmin, double cmax) {
    Vertex v, w;
    Graph G = DIGRAPHinit (V);
    while (G->A / 2 < E) {
        v = randV (G);
        w = randV (G);
        if (v != w)
        {
            double cst = randC (cmin, cmax);
            DIGRAPHinsertA (G, v, w, cst);
            DIGRAPHinsertA (G, w, v, cst);
        }
    }
    return G;
}

/* A função randV() devolve um vértice aleatório do digrafo G. */
static Vertex randV (Digraph G) {
    double r;
    r = rand () / (RAND_MAX + 1.0);
    return r * G->V;
}

/* A função randCst() devolve um número pseudo-aleatório entre 
cmin e cmax */
static double randC (double cmin, double cmax) {
    double r;
    r = rand () / (RAND_MAX + 1.0);
    return r * (cmax - cmin) + cmin;
}

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIAS: a função DIGRAPHrand2 ()
constrói um digrafo aleatório com vértices 0..V-1 e número esperado de
arcos igual a A. (As duas pontas de cada arco devem ser diferentes.) A
função supõe que V >= 2 e A <= V*(V-1). (Código inspirado no Program
17.8 de Sedgewick.) */
Digraph DIGRAPHrand2 (int V, int A, double cmin, double cmax) {
    Vertex v, w;
    double p = (double) A / V / (V-1);
    Digraph G = DIGRAPHinit (V);
    for (v = 0; v < V; v++)
        for (w = 0; w < V; w++)
            if (v != w && rand () < p * (RAND_MAX + 1.0))
            {
                double cst = randC (cmin, cmax);
                DIGRAPHinsertA (G, v, w, cst);
            }
    return G;
}

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIAS: a função GRAPHrand2 ()
constrói um grafo aleatório com vértices 0..V-1 e número esperado de
arestas igual a E. (As duas pontas de cada aresta devem ser
diferentes.) A função supõe que V >= 2 e E <= V*(V-1)/2. (Código
inspirado no Program 17.8 de Sedgewick.) */
Digraph GRAPHrand2 (int V, int E, double cmin, double cmax) {
    Vertex v, w;
    double p = (double) 2 * E / V / (V-1);
    Digraph G = DIGRAPHinit (V);
    for (v = 0; v < V; v++)
        for (w = 0; w < V; w++)
            if (v != w && rand () < p * (RAND_MAX + 1.0))
            {
                double cst = randC (cmin, cmax);
                DIGRAPHinsertA (G, v, w, cst);
                DIGRAPHinsertA (G, w, v, cst);
            }
    return G;
}

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIAS: a função
GRAPHclosePoints () escolhe V pontos aleatórios no quadrado
[0, 1)x[0,1) e cria um vértice para cada um desses pontos. Depois,
liga-se com arestas cada par de vértices v e w tal que a distância
entre os pontos representados por esses vértices é menor ou igual ao
parametro d. */
Graph GRAPHclosePoints (int V, double d) {
    /*int i, j;
    point *points = createRandPoints (V);*/
    Graph G;
    G = DIGRAPHinit (V);
    /*for (i = 0; i < V; i++) {
        for (j = i + 1; j < V; j++) {
            double dx = points[i].x - points[j].x;
            double dy = points[i].y - points[j].y;
            if (dx * dx + dy * dy <= d * d) {
                DIGRAPHinsertA (G, i, j);
                DIGRAPHinsertA (G, j, i);
            }
        }
    }
    free (points);*/
    return G;
}

/* Cria um vetor de n pontos aleatórios no quadrado [0, 1) x [0, 1) */
point *createRandPoints (int n) {
    int i;
    point *points = malloc (n * sizeof (point));
    for (i = 0; i < n; i++) {
        point p;
        p.x = rand () / (RAND_MAX + 1.0);
        p.y = rand () / (RAND_MAX + 1.0);
        points[i] = p;
    }
    return points;
}

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIAS: a função
// DIGRAHdestroyDist() libera da memória o espaço alocado para o vetor
// de distâncias. */
void DIGRAPHdestroyDist (Digraph G) {
    if (G->dist != NULL)
        free (G->dist);
    G->dist = NULL;
}

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIAS: a função
// DIGRAHdestroFather() libera da memória o espaço alocado para o vetor
// de pais, utilizado para representação de árvores
// (radicadas em geral). */
void DIGRAPHdestroyFather (Digraph G) {
    if (G->father != NULL)
        free (G->father);
    G->father = NULL;
}

/* Destroi qualquer vetor de pai antigo que estiver alocado e aloca um
// novo. */
static void NEWfather (Digraph G) {
    DIGRAPHdestroyFather (G);
    G->father = malloc (G->V * sizeof (Vertex));
}

/* Destroi qualquer vetor de distâncias antigo que estiver alocado e
// aloca um novo. */
static void NEWdist (Digraph G) {
    DIGRAPHdestroyDist (G);
    G->dist = malloc (G->V * sizeof (double));
}

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIAS: a função
// DIGRAPHsptD0 é uma implementação simples e não muito eficiente
// do algoritmo de Dijkstra. Esse algoritmo acha no digrafo uma árvore
// de caminhos mínimos partindo do vértice s. A árvore resultante fica
// armazenada no vetor father, e a distância no vetor dist. */
void DIGRAPHsptD0 (Digraph G, Vertex s) {
    Vertex v, *father;
    double *dist;
    int INFINITE = findINFINITE (G);
    NEWdist (G);
    NEWfather (G);
    father = G->father;
    dist = G->dist;
    /*printf ("INFINITE: %d\n", INFINITE);*/
    for (v = 0; v < G->V; v++) {
        dist[v] = INFINITE;
        father[v] = -1;
    }
    dist[s] = .0;
    father[s] = s;

    while (TRUE) {
        link a;
        /* Apenas para silenciar o compilador */
        Vertex x = -1, y = -1; 
        double minpr = INFINITE;
        for (v = 0; v < G->V; v++) {
            if (father[v] == -1) continue;
            for (a = G->adj[v]; a != NULL; a = a->next) {
                if (dist[v] + a->cst < dist[a->w])
                {
                    minpr = dist[v] + a->cst;
                    x = v, y = a->w;
                }
            }
        }
        if (minpr == INFINITE)
            break;
        father[y] = x, dist[y] = minpr;
    }
    if (!checkDist (G))
        printf ("A implementação de sptD0 não está correta.\n");
    else
        printf ("ok\n");
}

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIAS: a função
// DIGRAPHsptD0 é uma implementação do algoritmo de Dijkstra eficiente
// para grafos densos. Esse algoritmo acha no digrafo uma árvore de
// caminhos mínimos partindo do vértice s. A árvore resultante fica
// armazenada no vetor father, e a distância no vetor dist. */
void DIGRAPHsptD1 (Digraph G, Vertex s) {
    Vertex v, *father, *frg;
    double *dist;
    int INFINITE = findINFINITE (G);
    NEWdist (G);
    NEWfather (G);
    frj = malloc (G->V * sizeof (Vertex));
    father = G->father;
    dist = G->dist;
    dist[s] = .0;
    father[s] = s;


}

/* Essa função calcula o maior preço possível de um caminho simples 
// no grafo G mais uma unidade. Esse valor é calculado como um mais a
// soma dos V-1 arcos mais caros de G*/
static double findINFINITE (Digraph G) {
    int i, V;
    Vertex v;
    double *highest, infinite;
    V = G->V;
    infinite = 1;
    highest = malloc ((V - 1) * sizeof (double));
    for (i = 0; i < V - 1; i++)
        highest[i] = 0;
    for (v = 0; v < V; v++) {
        link a;
        for (a = G->adj[v]; a != NULL; a = a->next) {
            int k;
            double unsorted = a->cst;
            for (k = 0; k < G->V - 1; k++)
                if (unsorted > highest[k]) {
                    double temp = highest[k];
                    highest[k] = unsorted;
                    unsorted = temp;
                }
        }
    }
    for (i = 0; i < V - 1; i++)
        infinite += highest[i];
    free (highest);
    return infinite;
}

/* Verifica se o vetor dist de G é um potencial */
static int checkDist (Digraph G) {
    Vertex v;
    link a;
    double *dist = G->dist;
    for (v = 0; v < G->V; v++)
        for (a = G->adj[v]; a != NULL; a = a->next)
            if (dist[v] + a->cst < dist[a->w])
                return 0;
    return 1;
}
