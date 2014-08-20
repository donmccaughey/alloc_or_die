/* Copyright (c) 2014, Able Pear Software. All rights reserved.
 
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
