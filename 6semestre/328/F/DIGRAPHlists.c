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
// biblioteca para manipulação de grafos. Essa biblioteca usa listas
// de adjacência na sua implementação.
//
////////////////////////////////////////////////////////////// */

#include "DIGRAPHlists.h"

/* Protótipos de funções do tipo static */
static link NEWnode (Vertex w, link next);
static void LISTSdelete (link a);
static Vertex randV (Digraph G);
static void dfsR (Digraph G, Vertex v);
static void DFSprepare (Digraph G); 
static void dfsRsc (Digraph G, Vertex v, int id);

/* Variáveis usadas no DFS */
static int pre_count;
static int pos_count;

/* A função NEWnode() recebe um vértice w e o endereço next de um nó e
devolve o endereço a de um novo nó tal que a->w == w e a->next == next.
*/
static link NEWnode (Vertex w, link next) {
    link a = malloc (sizeof (struct node));
    a->w = w;
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
    G->pre = NULL;
    G->pos = NULL;
    G->sc = NULL;
    G->father = NULL;
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
    if (G->pre != NULL)
        free (G->pre);
    if (G->pos != NULL)
        free (G->pos);
    if (G->sc != NULL)
        free (G->sc);
    if (G->father != NULL)
        free (G->father);
    free (G);
}

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIAS: A função DIGRAPHreverse()
constrói o inverso do digrafo G. */
Digraph DIGRAPHreverse (Digraph G) {
    link l;
    Vertex v, w;
    Digraph GR;
    GR = DIGRAPHinit (G->V);
    for (v = 0; v < G->V; v++) {
        l = G->adj[v];
        while (l != NULL) {
            w = l->w;
            DIGRAPHinsertA (GR, w, v);
            l = l->next;
        }
    }
    return GR;
}

/* REPRESENTAÇÂO POR LISTAS DE ADJACÊNCIAS: A função 
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
    pre_count = 0;
    pos_count = 0;
}

/* REPRESENTAÇÂO POR LISTAS DE ADJACÊNCIAS: A função
DIGRAPHdistroyDFSinfo () libera o espaço alocado para estrutura do
digrafo pelo vetor sc, que guarda a componente forte a qual cada
vertice pertence */
void DIGRAPHdestroySCinfo (Digraph G) {
    if (G->sc != NULL)
        free (G->sc);
}


/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIAS: A função DIGRAPHoutdeg()
calcula o grau de saída do vértice v do grafo G. A função supõe que
v é menor que G->V */
int DIGRAPHoutdeg (Digraph G, Vertex v) {
    int count = 0;
    link a = G->adj[v];
    while (a != NULL) {
        count++;
        a = a->next;
    }
    return count;
}

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIAS: A função DIGRAPHindeg()
calcula o grau de entrada do vértice v do grafo G. A função supõe que
v é menor que G->V */
int DIGRAPHindeg (Digraph G, Vertex w) {
    int count = 0;
    Vertex v;
    for (v = 0; v < G->V; v++) {
        link a = G->adj[v];
        while (a != NULL && a->w != w)
            a = a->next;
        if (a != NULL)
            count++;
    }
    return count;
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

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função DFSprepare () 
prepara as variáveis relacionadas a rotina de DFS. */
static void DFSprepare (Digraph G) {
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
    pre_count = 0;
    pos_count = 0;
}


/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIA: A função DIGRAPHinsertA()
insere um arco v-w no digrafo G. A função supõe que v e w são
distintos, positivos e menores que G->V. Se o digrafo já tem um arco
v-w, a função não faz nada. */
void DIGRAPHinsertA (Digraph G, Vertex v, Vertex w) {
    link a;
    for (a = G->adj[v]; a != NULL; a = a->next)
        if (a->w == w) return;
    G->adj[v] = NEWnode (w, G->adj[v]);
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
    link l;
    Vertex w;
    G->pre[v] = pre_count++; 
    for (l = G->adj[v]; l != NULL; l = l->next) {
        w = l->w;
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
    G->pos[v] = pos_count++;
    return -1;
}

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIA: A função DIGRAPHdfs() visita
todos os vértices e todos os arcos do digrafo G. A função atribui um
número de ordem pre[x] a cada vértice x: o k-ésimo vértice descoberto
recebe número de ordem k. (Código inspirado no programa 18.3 de
Sedgewick.) */
void DIGRAPHdfs (Digraph G) {
    Vertex v;
    DFSprepare (G);
    for (v = 0; v < G->V; v++)
        if (G->pre[v] == -1)
            dfsR (G, v);
}

/* Seja U o conjunto dos vértices u tais que pre[u] >= 0. Nesse
ambiente, para cada vértice x acessível a partir de v por um caminho
que não usa vértices de U, a função dfsR() atribui um número positivo a
pre[x]:  se x é o k-ésimo vértice descoberto, pre[x] recebe conta+k.
(Código inspirado no programa 18.1 de Sedgewick.) */
static void dfsR (Digraph G, Vertex v) {
    Vertex w;
    link l;
    G->pre[v] = pre_count++;
    l = G->adj[v];
    while (l != NULL) {
        w = l->w;
        l = l->next;
        if (G->pre[w] == -1)
            dfsR (G, w);
    }
    G->pos[v] = pos_count++; 
}

/* Esta função implementa o algoritmo de Kosaraju-Sharir de cálculo das
componentes fortes de um digrafo G. A função atribui um rótulo sc[v]
(os rótulos são 0,1,2,...) a cada vértice v de G de modo que dois
vértices tenham o mesmo rótulo se e somente se os dois pertencem à
mesma componente forte. A função devolve o número (quantidade) de
componentes fortes de G. (O código é adaptado do Programa 19.10 de
Sedgewick.) */
int DIGRAPHscKS (Digraph G) {
    Vertex v, w;
    int i, id;
    Vertex *ord = malloc (G->V * sizeof (Vertex));
    Vertex *sc = malloc (G->V * sizeof (Vertex));
    Digraph GR = DIGRAPHreverse (G);
    DFSprepare (GR);
    for (v = 0; v < GR->V; v++)
        if (GR->pre[v] == -1)
            dfsR (GR, v);
    for (v = 0; v < GR->V; v++)
        ord[GR->pos[v]] = v;
    for (v = 0; v > G->V; v++)
        sc[v] = -1;
    id = 0;
    for (i = 0; i < G->V; i++) {
        v = ord[i];
        if (sc[v] == -1)
            dfsRsc (G, v, id++);
    }
    G->sc = sc; 
    DIGRAPHdestroy (GR);
    return id;
}

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIA: A função dfsRsc() atribui o
rótulo id a todo vértice w que é acessível a partir de v e ainda não
foi rotulado. Os rótulos são armazenados no vetor sc[]; um vértice w é
considerado rotulado se sc[w] >= 0. */
static void dfsRsc (Digraph G, Vertex v, int id) {

}

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIA: A função DIGRAPHshow()
imprime, para cada vértice v do digrafo G, em uma linha, todos os
vértices adjacentes a v. */
void DIGRAPHshow (Digraph G) {
    Vertex v;
    for (v = 0; v < G->V; v++) {
        link a = G->adj[v];
        printf ("%d: ", v);
        while (a != NULL) {
            printf ("%d ", a->w);
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

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIAS: A função GRAPHrand1 ()
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

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIAS: a função DIGRAPHrand2 ()
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

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIAS: a função GRAPHrand2 ()
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
