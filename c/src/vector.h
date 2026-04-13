#ifndef _VECTOR_H__
#define _VECTOR_H__

#include <stddef.h>

size_t malloc_size(const void *ptr);

typedef double vec_elem_t;

typedef struct Vector {
	vec_elem_t *ptr;
	size_t size;
} Vector;

Vector reserved_vec(size_t res);

void push(Vector *vec, int x);

void free_vec(Vector *vec);

#endif //_VECTOR_H__
