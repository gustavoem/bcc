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
// Data:       2016-08-17
// 
// Este arquivo faz parte da tarefa C
// da disciplina MAC0328 e tem como objetivo imlpementar uma
// biblioteca para manipulação de grafos. Essa biblioteca usa matrizes
// de adjacência na sua implementação.
//
////////////////////////////////////////////////////////////// */

#include "DIGRAPHmatrix.h"

/* Protótipos de funções do tipo static. A descrição dessas funções
estão junto às definições das funções. */
static int **MATRIXint (int r, int c, int val);
static void MATRIXdelete (int **m, int r);
static void DFSprepare (Digraph G);
static Vertex randV (Digraph G);

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função DIGRAPHinit()
constrói um digrafo com vértices 0 1 .. V-1 e nenhum arco. */
Digraph DIGRAPHinit (int V) {
    Digraph G = malloc (sizeof *G);
    G->V = V;
    G->A = 0;
    G->adj = MATRIXint (V, V, 0);
    G->pre = NULL;
    G->pos = NULL;
    G->father = NULL;
    G->pre_count = 0;
    G->pos_count = 0;
    return G;
}

/* REPRESENTAÇÂO POR MATRIZ DE ADJACÊNCIAS: A função DIGRAPHdestroy()
destrói um digrafo G liberando na memória o espaço que foi alocado em
sua criação */
void DIGRAPHdestroy (Digraph G) {
    MATRIXdelete (G->adj, G->V);
    DIGRAPHdestroyDFSinfo (G);
    free (G);
}

/* REPRESENTAÇÂO POR MATRIZ DE ADJACÊNCIAS: A função 
DIGRAPHdistroyDFSinfo () libera o espaço alocado para estrutura do
digrafo pelos vetores pre, pos e father. */
void DIGRAPHdestroyDFSinfo (Digraph G) {
    if (G->pre != NULL)
        free (G->pre);
    if (G->pos != NULL)
        free (G->pos);
    if (G->father != NULL)
        free (G->father);
    G->pre = NULL;
    G->pos = NULL;
    G->father = NULL;
}


/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função MATRIXdelete()
deleta uma matriz com linhas 0..r-1 e colunas 0..c-1. */
static void MATRIXdelete (int **m, int r) {
    int i;
    for (i = 0; i < r; i++)
        free (m[i]);
    free (m);
}

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função MATRIXint() aloca
uma matriz com linhas 0..r-1 e colunas 0..c-1. Cada elemento da matriz
recebe valor val. */
static int **MATRIXint (int r, int c, int val) {
    Vertex i, j;
    int **m = malloc (r * sizeof (int *));
    for (i = 0; i < r; i++)
        m[i] = malloc (c * sizeof (int));
    for (i = 0; i < r; i++)
        for (j = 0; j < c; j++)
            m[i][j] = val;
    return m;
}

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função DFSprepare () 
prepara as variáveis relacionadas a rotina de DFS. */
void DFSprepare (Digraph G) {
    int V = G->V;
    int v;
    DIGRAPHdestroyDFSinfo (G);
    G->pre = malloc (V * sizeof (int));
    G->pos = malloc (V * sizeof (int));
    G->father = malloc (V * sizeof (int));
    for (v = 0; v < V; v++) {
        G->pre[v] = -1;
        G->pos[v] = -1;
    }
}


/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função DIGRAPHinsertA()
insere um arco v-w no digrafo G. A função supõe que v e w são
distintos, positivos e menores que G->V. Se o digrafo já tem um arco
v-w, a função não faz nada. */
void DIGRAPHinsertA (Digraph G, Vertex v, Vertex w) {
    if (G->adj[v][w] == 0) {
        G->adj[v][w] = 1;
        G->A++;
    }
}

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função DIGRAPHremoveA()
remove do digrafo G o arco v-w. A função supõe que v e w são distintos,
positivos e menores que G->V. Se não existe arco v-w, a função não faz
nada. */
void DIGRAPHremoveA (Digraph G, Vertex v, Vertex w) {
    if (G->adj[v][w] == 1) {
        G->adj[v][w] = 0;
        G->A--;
    }
}

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função 
DIGRAPHcycleOrTopo () devolve um inteiro que representa o começo de um
ciclo presente no digrafo G ou devolve -1 se existe uma ordenação 
topológica em G. No ultimo caso, a numeração da ordenação topológica é
dada pelo vetor pre. */
int DIGRAPHcycleOrTopo (Digraph G) {
    Vertex v;
    DFSprepare (G);
    for (v = 0; v < G->V; v++) {
        if (G->pre[v] == -1) {
            int ans;
            G->father[v] = v;
            ans = DIGRAPHcycleOrTopoR (G, v);
            if (ans != -1)
                return ans;
        }
    }
    return -1;
}

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função
DIGRAPHcycleOrTopoR () devolve um inteiro que representa o começo de um
ciclo presente no subdigrafo de G tal que todo vértice é descendente do
vértice v ou devolve -1 se existe uma ordenação topológica em tal 
digrafo. No ultimo caso, a numeração da ordenação topológica é dada 
pelo vetor pre de G. */
int DIGRAPHcycleOrTopoR (Digraph G, Vertex v) {
    int w;
    G->pre[v] = G->pre_count++; 
    for (w = 0; w < G->V; w++) {
        if (G->adj[v][w]) {
            if (G->pre[w] == -1) {
                int ans;
                G->father[w] = v;
                ans = DIGRAPHcycleOrTopoR (G, w);
                if (ans != -1)
                    return ans;
            }
            if (G->pos[w] == -1) {
                G->father[w] = v;
                return w;
            }
        }
    }
    G->pos[v] = G->pos_count++;
    return -1;
}

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função DIGRAPHoutdeg()
calcula o grau de saída do vértice v do grafo G. A função supõe que
v é menor que G->V */
int DIGRAPHoutdeg (Digraph G, Vertex v) {
    int w;
    int deg = 0;
    for (w = 0; w < G->V; w++)
        if (G->adj[v][w])
            deg++;
    return deg;
}

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função DIGRAPHindeg()
calcula o grau de entrada do vértice v do grafo G. A função supõe que
v é menor que G->V */
int DIGRAPHindeg (Digraph G, Vertex w) {
    int v;
    int deg = 0;
    for (v = 0; v < G->V; v++)
        if (G->adj[v][w])
            deg++;
    return deg;
}

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função DIGRAPHshow()
imprime, para cada vértice v do digrafo G, em uma linha, todos os
vértices adjacentes a v. */
void DIGRAPHshow (Digraph G) {
    Vertex v, w;
    for (v = 0; v < G->V; v++) {
        printf ("%2d:", v);
        for (w = 0; w < G->V; w++)
            if (G->adj[v][w] == 1)
                printf (" %2d", w);
        printf ("\n");
    }
}

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função DIGRAPHrand1 ()
constrói um digrafo aleatório com vértices 0..V-1 e exatamente A
arcos. (As duas pontas de cada arco devem ser diferentes.) A função
supõe que A <= V*(V-1). Se A for próximo de V*(V-1), a função pode
consumir muito tempo. (Código inspirado no Programa 17.7 de
Sedgewick.) */
Digraph DIGRAPHrand1 (int V, int A) {
    Vertex v, w;
    Digraph G = DIGRAPHinit (V);
    while (G->A < A) {
        v = randV (G);
        w = randV (G);
        if (v != w)
            DIGRAPHinsertA (G, v, w);
    }
    return G;
}

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função GRAPHrand1 ()
constrói um grafo aleatório com vértices 0..V-1 e exatamente E arestas
(As duas pontas de cada aresta devem ser diferentes.). A função
supõe que E <= V*(V-1)/2. Se E for próximo de V*(V-1)/2, a função pode
consumir muito tempo. (Código inspirado no Programa 17.7 de
Sedgewick.) */
Digraph GRAPHrand1 (int V, int E) {
    Vertex v, w;
    Digraph G = DIGRAPHinit (V);
    while (G->A / 2 < E) {
        v = randV (G);
        w = randV (G);
        if (v != w)
        {
            DIGRAPHinsertA (G, v, w);
            DIGRAPHinsertA (G, w, v);
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

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: a função DIGRAPHrand2 ()
constrói um digrafo aleatório com vértices 0..V-1 e número esperado de
arcos igual a A. (As duas pontas de cada arco devem ser diferentes.) A
função supõe que V >= 2 e A <= V*(V-1). (Código inspirado no Program
17.8 de Sedgewick.) */
Digraph DIGRAPHrand2 (int V, int A) {
    Vertex v, w;
    double p = (double) A / V / (V-1);
    Digraph G = DIGRAPHinit (V);
    for (v = 0; v < V; v++)
        for (w = 0; w < V; w++)
            if (v != w && rand () < p * (RAND_MAX + 1.0))
                DIGRAPHinsertA (G, v, w);
    return G;
}

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: a função GRAPHrand2 ()
constrói um grafo aleatório com vértices 0..V-1 e número esperado de
arestas igual a E. (As duas pontas de cada aresta devem ser
diferentes.) A função supõe que V >= 2 e E <= V*(V-1)/2. (Código
inspirado no Program 17.8 de Sedgewick.) */
Digraph GRAPHrand2 (int V, int E) {
    Vertex v, w;
    double p = (double) 2 * E / V / (V-1);
    Digraph G = DIGRAPHinit (V);
    for (v = 0; v < V; v++)
        for (w = 0; w < V; w++)
            if (v != w && rand () < p * (RAND_MAX + 1.0))
            {
                DIGRAPHinsertA (G, v, w);
                DIGRAPHinsertA (G, w, v);
            }
    return G;
}
