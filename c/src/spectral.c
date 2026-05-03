#include "spectral.h"
#include "utils.h"
#include "vector.h"
#include "matrix.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

extern double **A, **Q, **T;
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
	return (*(vec_elem_t*)a) < (*(vec_elem_t*)b);
}

static void print_matrix(double **m, int n) {
	for(int i = 0; i < n; ++i) {
		putchar('[');
		for(int j = 0; j < n; ++j)
			printf(" %8g", m[i][j]);
		puts("]");
	}
	putchar('\n');
}

void spectral(Graph *g) {
	const int n = g->n_vertices;
	A = alloc_matrix(n);
	Q = alloc_matrix(n);
	T = alloc_matrix(n);

	for(int i = 0; i < g->n_edges; ++i) {
		if(g->edges[i].u != g->edges[i].v) {
			A[g->edges[i].u][g->edges[i].v] = -1;
			A[g->edges[i].v][g->edges[i].u] = -1;
			A[g->edges[i].v][g->edges[i].v]++;
			A[g->edges[i].u][g->edges[i].u]++;
		}
	}

	for(int iter = 0; iter < SPECTRAL_ITERATIONS; ++iter) {
		for(int k = 0; k < n; ++k) {
			for(int i = 0; i < n; ++i)
				Q[k][i] = A[k][i];
			for(int j = 0; j < k; ++j) {
				const double d = dot_product(Q[j], A[k], n)/dot_product(Q[j], Q[j], n);
				for(int l = 0; l < n; ++l)
					Q[k][l] -= A[k][l]*d;
			}
		}
		for(int k = 0; k < n; ++k) {
			double norm = normalization(Q[k], n);
			for(int i = 0; i < n; ++i)
				Q[k][i] /= norm;
		}
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j) {
				T[i][j] = 0.0;
				for(int k = 0; k < n; ++k)
					T[i][j] += Q[k][i] * A[k][j];
			}
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j) {
				A[i][j] = 0.0;
				for(int k = 0; k < n; ++k)
					A[i][j] += T[i][k] * Q[k][j];
			}
		printf("%d\n", iter+1);
		print_matrix(A, n);
	}

	//eigenvalues = reserved_vec(n);
	//for(int i = 0; i < n; ++i)
		//push_back(&eigenvalues, A[i][i]);

	puts("Eigenvalues:");
	for(int i = 0; i < n; ++i)
		printf("%8g ", A[i][i]);
	printf("\n");
}
