#ifndef EARMARK_EARMARK_H_INCLUDED
#define EARMARK_EARMARK_H_INCLUDED


#include <stdarg.h>
#include <stddef.h>


void *
em_calloc(size_t count, size_t element_size);

void *
em_malloc(size_t size);

void *
em_arraydup(void const *memory, size_t count, size_t element_size);

void *
em_memdup(void const *memory, size_t size);

void *
em_realloc(void *memory, size_t size);

void *
em_reallocarray(void *memory, size_t count, size_t element_size);

char *
em_strdup(char const *string);

int
em_asprintf(char **string, char const *format, ...);

int
em_vasprintf(char **string, const char *format, va_list arguments);

void
em_free(void *memory);

void
em_expect_alloc_count_zero(void);


#endif
