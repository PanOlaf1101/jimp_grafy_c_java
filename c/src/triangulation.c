#include <stdio.h>
#include "graph.h"

static int edge_exists(Graph *g, int u, int v)
{
	for (int i = 0; i < g->n_edges; i++) {

		if ((g->edges[i].u == u && g->edges[i].v == v) ||
		    (g->edges[i].u == v && g->edges[i].v == u)) {

			return 1;
		}
	}

	return 0;
}

void triangulate_graph(Graph *g)
{
	int max_edges = 3 * g->n_vertices - 6;

	for (int i = 0; i < g->n_edges; i++) {

		for (int j = i + 1; j < g->n_edges; j++) {

			if (g->n_edges >= max_edges)
				return;

			int a = g->edges[i].u;
			int b = g->edges[i].v;

			int c = g->edges[j].u;
			int d = g->edges[j].v;

			if (b == c) {

				if (!edge_exists(g, a, d)) {

					add_edge(g, a, d, 1.0);
				}
			}

			if (a == d) {

				if (!edge_exists(g, b, c)) {

					add_edge(g, b, c, 1.0);
				}
			}
		}
	}
}
