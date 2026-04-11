#include "triangulation.h"
#include "graph.h"

void triangulate(Graph *g) {

    int original_edges = g->n_edges;

    for (int i = 0; i < original_edges; i++) {
        for (int j = i + 1; j < original_edges; j++) {

            int a = g->edges[i].u;
            int b = g->edges[i].v;

            int c = g->edges[j].u;
            int d = g->edges[j].v;

            if (b == c) {
                add_edge(g, a, d, 1.0);
            }

            if (a == d) {
                add_edge(g, c, b, 1.0);
            }
        }
    }
}
