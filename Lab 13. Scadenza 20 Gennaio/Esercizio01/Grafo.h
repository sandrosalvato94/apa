#ifndef GRAFO_H_DEFINED
#define GRAFO_H_DEFINED


typedef struct grh *GRAPH;
typedef struct
{
    int v;
    int w;
}EDGE;

GRAPH GraphInit(int num_vertici, int num_archi);
EDGE GetEdge(int v, int w);
void EdgeGraphInsert(GRAPH G, EDGE e, int arco_corr);
void GraphInsert(GRAPH G, EDGE e);
void GRAPHbfs(GRAPH G, int vertice_partenza, int vertice_arrivo);
void GraphShow(GRAPH G);
void GetCammino(int vertice_partenza, int vertice_arrivo);
void DAGrts(GRAPH G);

#endif
