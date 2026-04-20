#ifndef _UTILS_H__
#define _UTILS_H__

#include <stddef.h>

extern void cleanup(void);

__attribute__((noreturn))
void error_msg(const char *restrict msg);

__attribute__((noreturn))
void verror_msg(const char *restrict msg, ...);

void check_null(const void *const ptr);

//"bezpieczne" malloc(), jeśli nie można zaalokować pamięci, wywołuje error_msg()
void *alloc(size_t bytes);

//to samo co alloc(), ale wykorzystuje calloc() zamiast malloc()
void *zalloc(size_t n, size_t s);

#endif //_UTILS_H__
