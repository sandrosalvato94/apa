#ifndef GRAFO_H_DEFINED
#define GRAFO_H_DEFINED

typedef struct
{
    int v;
    int w;
    int p;
}EDGE;

typedef struct graph *GRAPH;

GRAPH GraphInit(int num_vertici);
void GraphInsert(GRAPH G, EDGE e);
EDGE GetEdge(int v, int w, int p);
void GraphShow(GRAPH G);
int RankNode(GRAPH G, int num_nodo);
void InizializzaMatriceAdj(GRAPH G);
void Generazione_MatAdj(GRAPH G);
void StampaMatrice(GRAPH G);
void Incidenze(GRAPH G, int num_nodo);
int** Scan_Incidenze_Vett(GRAPH G, int num_nodo, int** m);
void DeallocaGrafo(GRAPH G);

#endif

