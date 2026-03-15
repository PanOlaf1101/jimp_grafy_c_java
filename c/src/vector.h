#ifndef _VECTOR_H__
#define _VECTOR_H__

#include <stddef.h>

size_t malloc_size(const void *ptr);

typedef struct Vector {
	int *ptr;
	size_t size;
} Vector;

Vector reserved_vec(size_t res);

void push(Vector *vec, int x);

#endif //_VECTOR_H__
