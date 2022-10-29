#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#define LUNGHEZZA 15

struct node
{
    int w;
    int peso;
    struct node *succ;
};
typedef struct node *link;

struct graph
{
    int V;
    int E;
    int **mat_adj;
    link *list_adj;
};

GRAPH GraphInit(int num_vertici)
{
    int i;
    GRAPH G = malloc(sizeof(*G));
    G->V = num_vertici;
    G->E = 0;
    G->list_adj = malloc(num_vertici*sizeof(link));
    for(i=0; i<num_vertici; i++)
    {
        G->list_adj[i] = NULL;
    }
    G->mat_adj = (int**)malloc(num_vertici*sizeof(int*));
    for (i=0; i<num_vertici; i++)
    {
        G->mat_adj[i] = (int*)malloc(num_vertici*sizeof(int));
    }
    return G;
}
EDGE GetEdge(int v, int w, int p)
{
    EDGE e;
    e.v = v;
    e.w = w;
    e.p = p;
    return e;
}

link NEW(int v_arr, int weight, link next)
{
    link x = malloc(sizeof(*x));
    x->w = v_arr;
    x->peso = weight;
    x->succ = next;
    return x;
}

void GraphInsert(GRAPH G, EDGE e)
{
    G->list_adj[e.v] = NEW(e.w, e.p, G->list_adj[e.v]);
    G->list_adj[e.w] = NEW(e.v, e.p, G->list_adj[e.w]);
    G->E++;
}

int RankNode(GRAPH G, int num_nodo)
{
    int grado=0;
    link p_corr;
    for(p_corr = G->list_adj[num_nodo]; p_corr !=NULL; p_corr = p_corr->succ)
    {
        grado++;
    }
    return grado;
}

void InizializzaMatriceAdj(GRAPH G)
{
    int i, j, k=1;
    for (i=0; i<G->V; i++)
    {
        for(j=0; j<k; j++)
        {
            G->mat_adj[i][j] = G->mat_adj[j][i] = 0;
        }
        if(k<G->V)
        {
            k++;
        }
    }
}

void StampaMatrice(GRAPH G)
{
    int i, j;
    for (i=0; i<G->V; i++)
    {
        for(j=0; j<G->V; j++)
        {
            printf("%d ", G->mat_adj[i][j]);
        }
        printf("\n");
    }
}

void Generazione_MatAdj(GRAPH G)
{
    int i;
    link p_corr;

    for (i=0; i<G->V; i++)
    {
        for(p_corr = G->list_adj[i]; p_corr != NULL; p_corr = p_corr->succ)
        {
            if(G->mat_adj[i][p_corr->w] == 0)
            {
                G->mat_adj[i][p_corr->w] = G->mat_adj[p_corr->w][i] = p_corr->peso;
            }
        }
    }
}

void Incidenze(GRAPH G, int num_nodo)
{
    link p_corr;

    for (p_corr = G->list_adj[num_nodo]; p_corr!= NULL; p_corr = p_corr->succ)
    {
        printf(" %d ", p_corr->w+1);
    }
}

int** Scan_Incidenze_Vett(GRAPH G, int num_nodo, int** m)
{
    link p_corr;
    int j=1;

    for(p_corr = G->list_adj[num_nodo]; p_corr != NULL; p_corr = p_corr->succ)
    {
        m[0][j] = p_corr->w;
        m[1][j] = p_corr->peso;
        j++;
    }
    return m;
}

void DeallocaLista(link puttesta)
{
    if(puttesta == NULL)
    {
        free(puttesta);
        return;
    }
    DeallocaLista(puttesta->succ);
}

void DeallocaGrafo(GRAPH G)
{
    int i;
    for(i=0; i<G->V; i++)
    {
        free(G->mat_adj[i]);
    }
    free(G->mat_adj);

    for(i=0; i<G->V; i++)
    {
        DeallocaLista(G->list_adj[i]);
    }
    free(G->list_adj);

    free(G);
}
