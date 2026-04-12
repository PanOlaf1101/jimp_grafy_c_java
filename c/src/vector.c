#include "vector.h"
#include "utils.h"
#include <stdlib.h>

//Aby sprawdzić ile pamięci na stercie jest zaalowakowanej przez wektor, musimy skorzystać ze specjalnych funkcji systemowych
//Coś takiego nie istnieje w standardowym języku C, ale możemy skorzystać z niestandardowych funkcji w zależności od systemu operacyjnego
//Poniżej stworzono funkcję o nazwie malloc_size(), która zwraca liczbę bajtów zajętą przez wzkazywany obszar na stercie
//Niniejsza implementacja wspiera systemy: Windows, macOS, (GNU/)Linux oraz FreeBSD

//Windows: https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/msize?view=msvc-170
#ifdef _WIN32
#include <malloc.h>
size_t malloc_size(const void *ptr) {
	return _msize((void*)ptr);
}

//Linux: https://manpages.ubuntu.com/manpages/noble/man3/malloc_usable_size.3.html
#elif defined(__linux__)
#include <malloc.h>
size_t malloc_size(const void *ptr) {
	return malloc_usable_size((void*)ptr);
}

//macOS: https://developer.apple.com/library/archive/documentation/System/Conceptual/ManPages_iPhoneOS/man3/malloc_size.3.html
//akurat ta funkcja już się nazywa malloc_size() na systemach Apple
#elif defined(__APPLE__)
#include <malloc/malloc.h>

//FreeBSD: https://man.freebsd.org/cgi/man.cgi?query=malloc_usable_size&apropos=0&sektion=0&manpath=FreeBSD+7.1-RELEASE&format=html
#elif defined(__FreeBSD__)
#include <malloc_np.h>
size_t malloc_size(const void *ptr) {
	return malloc_usable_size(ptr);
}

//Dla innych systemów operacyjnych zgłaszamy błąd kompilacji
#else
#error "Unsupported OS! Use a Windows, Mac, Linux, or FreeBSD machine!"
#endif

void push_back(Vector *vec, int x) {
	//jeżeli powiększony wektor zajmuje więcej pamięci niż jest aktualnie zaalowakowanej, to korzystamy ze standardowej funkcji realloc
	if(sizeof(vec_elem_t) * vec->size >= malloc_size(vec->ptr)) {
		vec_elem_t *p = realloc(vec->ptr, (vec->size+32) * sizeof(vec_elem_t)); //nowa allokacja może pomieść co najmniej o 32 liczby (128 bajtów) więcej
		if(p == NULL) { //zgłaszamy błąd jeżeli nie można zaalokować pamięci
			free(vec->ptr);
			error_msg("Nie można zalokować pamięci");
		}
		vec->ptr = p;
	}
	//dopisujemy nową liczbę
	vec->ptr[(vec->size)++] = x;
}

void free_vec(Vector *vec) {
	//zwalniamy pamięć i ustawiamy atrybuty wektora na zero
	free(vec->ptr);
	vec->ptr = NULL;
	vec->size = 0;
}
