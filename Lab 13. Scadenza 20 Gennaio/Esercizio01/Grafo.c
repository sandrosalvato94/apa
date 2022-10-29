#include "Grafo.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "PriorityQueue.h"
#include "Tabella.h"

static EDGE *vett_edge;
static int time;
static int *pre;
static int *st;
static int *mindist;

struct node
{
    int w;
    struct node *succ;
};

typedef struct node *link;

struct grh
{
    int V;
    int E;
    link *list_adj;
    link DAG;
};

GRAPH GraphInit(int num_vertici, int num_archi)
{
    int i;
    GRAPH G = malloc(sizeof(*G));
    G->V = num_vertici;
    G->E = num_archi;
    G->list_adj = malloc(num_vertici*sizeof(link));
    G->DAG = malloc(sizeof(link));
    G->DAG = NULL;
    pre = malloc(num_vertici*sizeof(int));
    st = malloc(num_vertici*sizeof(int));
    for(i=0; i<num_vertici; i++)
    {
        G->list_adj[i] = NULL;
        st[i] = pre[i] = -1;
    }
    vett_edge = malloc(num_archi*sizeof(*vett_edge));
    return G;
}

EDGE GetEdge(int v, int w)
{
    EDGE e;
    e.v = v;
    e.w = w;
    return e;
}

link NEW(int v_arr, link next)
{
    link x = malloc(sizeof(*x));
    x->w = v_arr;
    x->succ = next;
    return x;
}

void GraphInsert(GRAPH G, EDGE e)
{
    G->list_adj[e.v] = NEW(e.w, G->list_adj[e.v]);
}

void GraphShow(GRAPH G)
{
    int i;
    link p_corr;

    for(i=0; i<G->V; i++)
    {
        printf("\n%d ->", i);
        for(p_corr = G->list_adj[i]; p_corr!=NULL; p_corr = p_corr->succ)
        {
            printf("%d ->", p_corr->w);
        }
        printf("\n");
    }
}

void EdgeGraphInsert(GRAPH G, EDGE e, int arco_corr)
{
    vett_edge[arco_corr] = e;
    GraphInsert(G, e);
}

void bfs(GRAPH G, EDGE e, int vertice_arrivo)
{
    link p_corr;
    PQ Q = QueueInit(G->V);
    st[e.v] = e.v;
    QueuePut(Q, e.v);
    pre[e.v] = time;
    while(QueueEmpty(Q) > 0)
    {
       for(p_corr = G->list_adj[e.v]; p_corr != NULL; p_corr = p_corr->succ)
       {
           if(st[p_corr->w] == -1)
           {
               st[p_corr->w] = e.v;
               QueuePut(Q, p_corr->w);
               pre[p_corr->w] = ++time;
           }
       }
       e.v = QueueExtr(Q);  /*Estraggo il primo elemento nella coda*/
    }
}

/*void CamminoMinimo(int vertice_partenza, int vertice_arrivo, int*CM)
{
    int i;
    int k;

    if(vertice_partenza == vertice_arrivo)
    {
        return;
    }

    vertice_partenza = st[vertice_partenza];
    *CM = *CM +1;
    CamminoMinimo(vertice_partenza, vertice_arrivo, CM);
    printf("->%d", vertice_partenza);
}*/

void GRAPHbfs(GRAPH G, int vertice_partenza, int vertice_arrivo)
{
    int v;
    time = 0;
    pre = malloc(G->V*sizeof(int));
    st = malloc(G->V*sizeof(int));
    //wt = malloc(G->V*sizeof(int));
    EDGE e = GetEdge(vertice_partenza, vertice_partenza);

    for (v=0; v<G->V; v++)
    {
        st[v] = pre[v] = -1;
        //wt[v] = INT_MAX; /*Impongo distanza infinita a tutti i vertici, tranne a quello dipartenza che avrà distanza zero da se stesso*/
    }
    //wt[vertice_partenza] = 0;
    bfs(G, e, vertice_arrivo);
}

void GetCammino(int vertice_partenza, int vertice_arrivo)
{
    int i,h=vertice_arrivo;
    printf("\n\n");
    for(i=0; ;i++)
    {
        printf("%d", h);
        if(h==st[h])
        {
            break;
        }
        h = st[h];
        printf("<- ");

    }
    printf("\nlungo %d", i);
}

/*void GraphspD(GRAPH G, int vertice_partenza, int vertice_arrivo)
{
    int i, w, v;
    PQ Q = QueueInit(G->V);
    mindist = malloc(G->V*sizeof(int));
    link p_corr;

    for(i=0; i<G->V; i++)
    {
        st[i] = -1;
        mindist[i] = 0;
    }
    mindist[vertice_partenza] = 0;
    QueuePut(Q, vertice_partenza);
    st[vertice_partenza] = vertice_partenza;

    while(QueueEmpty(Q) != 0)
    {
        if(mindist[v = QueueExtrMax(Q)]!= 0)
        {
            for(p_corr = G->list_adj[v]; p_corr != NULL; p_corr = p_corr->succ)
            {
                if(mindist[v] + 1 <mindist[w = t->w])
                {
                    mindist[w] = mindist[v] +1;
                    st[w] = v;
                }
            }
        }
    }

}*/
void TSdfsR(GRAPH G, int v, int st[])
{
    link p_corr;
    pre[v] = 0;
    for (p_corr = G->list_adj[v]; p_corr != NULL; p_corr = p_corr->succ)
    {
        if (pre[p_corr->w] == -1)
        {
            TSdfsR(G, p_corr->w, st);
        }
    }
    st[time++] = v;
}

void DAGrts(GRAPH G)
{
    int v;
    time = 0;
    link p_corr;
    for (v=0; v< G->V; v++)
    {
        pre[v] = -1;
        st[v] = -1;
    }
    for (v=0; v < G->V; v++)
    {
        if (pre[v]== -1)
        {
            TSdfsR(G, v, st);
        }
    }

    for (v=0; v < G->V; v++)
    {
        G->DAG = NEW(st[v], G->DAG);
    }
}
