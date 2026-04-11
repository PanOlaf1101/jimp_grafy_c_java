#ifndef GRAPH_H
#define GRAPH_H

typedef struct {
    int u;
    int v;
    double w;
} Edge;

typedef struct {
    int n_vertices;
    int n_edges;
    Edge *edges;
} Graph;

Graph create_graph(int max_edges);
void add_edge(Graph *g, int u, int v, double w);
void free_graph(Graph *g);

#endif
