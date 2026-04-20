#include "spectral.h"
#include "utils.h"
#include "vector.h"
#include "matrix.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

extern double **A, **Q, **R;
extern Vector eigenvalues;

static double normalization(double *v, int n) {
	double s = 0.0;
	for(int i = 0; i < n; ++i)
		s += v[i]*v[i];
	return sqrt(s);
}

static double dot_product(double *a, double *b, int n) {
	double s = 0.0;
	for(int i = 0; i < n; ++i)
		s += a[i]*b[i];
	return s;
}

static int cmp(const void *a, const void *b) {
	return *(vec_elem_t*)a > *(vec_elem_t*)b;
}

void spectral(Graph *g) {
	A = alloc_matrix(g->n_vertices);
	Q = alloc_matrix(g->n_vertices);
	R = alloc_matrix(g->n_vertices);

	for(int i = 0; i < g->n_edges; ++i) {
		if(g->edges[i].u != g->edges[i].v) {
			A[g->edges[i].u][g->edges[i].v] = -1;
			A[g->edges[i].v][g->edges[i].v]++;
		}
	}

	for(int iter = 0; iter < SPECTRAL_ITERATIONS; ++iter) {
		for(int k = 0; k < g->n_vertices; ++k) {
			for(int i = 0; i < g->n_vertices; ++i)
				Q[k][i] = A[k][i];
			for(int j = 0; j < k; ++j) {
				double d = dot_product(Q[j], A[k], g->n_vertices)/dot_product(Q[j], Q[j], g->n_vertices);
				for(int l = 0; l < g->n_vertices; ++l)
					Q[k][l] -= A[k][l]*d;
			}
		}
		for(int k = 0; k < g->n_vertices; ++k) {
			double norm = normalization(Q[k], g->n_vertices);
			for(int i = 0; i < g->n_vertices; ++i)
				Q[k][i] /= norm;
		}
		for(int i = 0; i < g->n_vertices; ++i) {
			for(int j = i; j < g->n_vertices; ++j) {
				R[i][j] = dot_product(Q[i], A[j], g->n_vertices);
			}
		}
		multiply_matrix(A, Q, R, g->n_vertices);
	}

	eigenvalues = reserved_vec(g->n_vertices);
	for(int i = 0; i < g->n_vertices; ++i)
		push_back(&eigenvalues, A[i][i]);
	qsort(eigenvalues.ptr, g->n_vertices, sizeof(vec_elem_t), cmp);

	for(int i = 0; i < g->n_vertices; ++i)
		fprintf(stderr, "%lf ", eigenvalues.ptr[i]);
}
