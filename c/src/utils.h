#ifndef _UTILS_H__
#define _UTILS_H__

#include <stddef.h>

extern void cleanup(void);

__attribute__((noreturn))
void error_msg(const char *restrict msg);

__attribute__((noreturn))
void verror_msg(const char *restrict msg, ...);

void check_null(const void *const ptr);

void *alloc(size_t bytes);

#endif //_UTILS_H__
