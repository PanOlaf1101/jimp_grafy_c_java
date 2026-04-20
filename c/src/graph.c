#include <stdlib.h>
#include "graph.h"
#include "utils.h"

Graph create_graph(int max_edges) {
    Graph g;
    g.n_vertices = 0;
    g.n_edges = 0;
    g.edges = alloc(sizeof(Edge) * max_edges);
    g.vertices = NULL;

    return g;
}

int edge_exists(Graph *g, int u, int v) {
    for(int i=0;i<g->n_edges;i++){
        if((g->edges[i].u==u && g->edges[i].v==v) ||
           (g->edges[i].u==v && g->edges[i].v==u))
            return 1;
    }
    return 0;
}

void add_edge(Graph *g,int u,int v,double w){
    if(edge_exists(g,u,v))
        return;

    g->edges[g->n_edges].u=u;
    g->edges[g->n_edges].v=v;
    g->edges[g->n_edges].w=w;

    g->n_edges++;

    if (u + 1 > g->n_vertices) g->n_vertices = u + 1;
    if (v + 1 > g->n_vertices) g->n_vertices = v + 1;
}

void free_graph(Graph *g) {
    free(g->edges);
	free(g->vertices);

    g->edges=NULL;
    g->vertices=NULL;
}
