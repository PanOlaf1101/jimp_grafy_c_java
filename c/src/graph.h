#ifndef _GRAPH_H__
#define _GRAPH_H__

typedef struct Edge {
    int u;
    int v;
    double w;
} Edge;

typedef struct Vertex { 
    int id;
    double x;
    double y;
} Vertex;

typedef struct Graph {
    int n_vertices;
    int n_edges;
    Edge *edges;
    Vertex *vertices;
} Graph;

Graph create_graph(int max_edges);
void add_edge(Graph *g, int u, int v, double w);
int edge_exists(Graph *g, int u, int v);
void free_graph(Graph *g);

#endif //_GRAPH_H__
