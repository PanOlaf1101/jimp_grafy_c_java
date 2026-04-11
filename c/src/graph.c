#include <stdlib.h>
#include "graph.h"

struct Edge {
    int u;
    int v;
    double w;
};

struct Graph {
    int n_vertices;
    int n_edges;
    Edge *edges;
};

Graph create_graph(int max_edges) {
    Graph g;
    g.n_vertices = 0;
    g.n_edges = 0;
    g.edges = malloc(sizeof(Edge) * max_edges);
    return g;
}

void add_edge(Graph *g, int u, int v, double w) {

    g->edges[g->n_edges].u = u;
    g->edges[g->n_edges].v = v;
    g->edges[g->n_edges].w = w;

    g->n_edges++;

    if (u > g->n_vertices) g->n_vertices = u;
    if (v > g->n_vertices) g->n_vertices = v;
}

void free_graph(Graph *g) {
    free(g->edges);
    g->edges = NULL;
}
