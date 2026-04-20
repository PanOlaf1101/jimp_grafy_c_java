#ifndef _MATRIX_H__
#define _MATRIX_H__

double **alloc_matrix(int n);

void multiply_matrix(double **m, double **a, double **b, int n);

void free_matrix(double **m, int n);

#endif
