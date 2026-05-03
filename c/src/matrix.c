#include "matrix.h"
#include "utils.h"
#include <stdlib.h>

double **alloc_matrix(int n) {
	double **m = zalloc(n, sizeof(double*));
	for(int i = 0; i < n; ++i)
		m[i] = zalloc(n, sizeof(double));
	return m;
}

void free_matrix(double **m, int n) {
	if(m != NULL) {
		for(int i = 0; i < n; ++i)
			free(m[i]);
		free(m);
	}
}
