#include "spectral.h"
#include "utils.h"
#include "vector.h"
//#include <stdio.h>

extern double **sl_matrix, **help_mat;
extern Vector eigenvalues;

static void get_eigenvals(int top, int bottom, int left, int right) {
	if(top == bottom && left == right)
		return sl_matrix[top][left];
	for(int i = top; i < bottom; ++i) {
		for(int j = left; j < right; ++j) {
			
		}
	}
}

void spectral(Graph *g) {
	sl_matrix = zalloc(g->n_vertices, sizeof(double*));
	help_mat = zalloc(g->n_vertices, sizeof(double*));

	for(int i = 0; i < g->n_vertices; ++i) {
		sl_matrix[i] = zalloc(g->n_vertices, sizeof(double));
		help_mat[i] = zalloc(g->n_vertices, sizeof(double));
	}

	for(int i = 0; i < g->n_edges; ++i) {
		if(g->edges[i].u != g->edges[i].v) {
			sl_matrix[g->edges[i].u][g->edges[i].v] = -1;
			sl_matrix[g->edges[i].v][g->edges[i].v]++;
		}
	}

	/*for(int i = 0; i < g->n_vertices; ++i) {
		for(int j = 0; j < g->n_vertices; ++j) {
			printf("\t%.5lf", sl_matrix[i][j]);
		}
		putchar('\n');
	}*/

	for(int i = 0; i < g->n_edges; ++i) {
		for(int j = 0; j < g->n_edges; ++j) {
			
		}
	}
}
