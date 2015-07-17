/* alloc_or_die. https://github.com/AblePear/alloc_or_die
 Copyright (c) 2014, Able Pear Software. All rights reserved.
 
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
 
 - Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer.
 
 - Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution.
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */

#ifndef ALLOC_OR_DIE_H_INCLUDED
#define ALLOC_OR_DIE_H_INCLUDED


#include <stdarg.h>
#include <stddef.h>


void *
calloc_or_die(size_t count, size_t element_size);

void *
malloc_or_die(size_t size);

void *
arraydup_or_die(void const *memory, size_t count, size_t element_size);

void *
memdup_or_die(void const *memory, size_t size);

void *
realloc_or_die(void *memory, size_t size);

void *
reallocarray_or_die(void *memory, size_t count, size_t element_size);

char *
strdup_or_die(char const *string);

int
asprintf_or_die(char **string, char const *format, ...);

int
vasprintf_or_die(char **string, const char *format, va_list arguments);

void *
not_null_or_die(void *memory);

void
free_or_die(void *memory);

void
expect_alloc_count_zero_or_die(void);


#endif
