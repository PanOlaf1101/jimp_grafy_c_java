#ifndef GRAPH_H
#define GRAPH_H

typedef struct Edge Edge;
typedef struct Graph Graph;

Graph create_graph(int max_edges);
void add_edge(Graph *g, int u, int v, double w);
int edge_exists(Graph *g, int u, int v);
void free_graph(Graph *g);

#endif
