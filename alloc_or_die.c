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

#include "alloc_or_die.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define SQRT_SIZE_MAX_PLUS_1 (1UL << (sizeof(size_t) * 4))


long alloc_or_die_count = 0;


size_t
array_size_or_die(size_t count, size_t element_size)
{
  if (count >= SQRT_SIZE_MAX_PLUS_1 || element_size >= SQRT_SIZE_MAX_PLUS_1) {
    if (element_size && count > SIZE_MAX / element_size) {
      errno = EOVERFLOW;
      print_error_and_die();
    }
  }
  return count * element_size;
}


int
asprintf_or_die(char **string, char const *format, ...)
{
  va_list arguments;
  va_start(arguments, format);
  int result = vasprintf_or_die(string, format, arguments);
  va_end(arguments);
  return result;
}


void
alloc_count_is_zero_or_die(void)
{
  if (alloc_or_die_count) {
    char const *plural = (1 == alloc_or_die_count) ? "" : "s";
    fprintf(stderr, "WARNING: %li memory allocation%s not freed.\n",
            alloc_or_die_count, plural);
    exit(EXIT_FAILURE);
  }
}


////////// extern inline declarations //////////

extern inline void *
arraydup_or_die(void const *memory, size_t count, size_t element_size);

extern inline void *
calloc_or_die(size_t count, size_t element_size);

extern inline void
free_or_die(void *memory);

extern inline void *
malloc_or_die(size_t size);

extern inline void *
memdup_or_die(void const *memory, size_t size);

extern inline void *
not_null_or_die(void *memory);

extern inline void
print_error_and_die(void);

extern inline void *
realloc_or_die(void *memory, size_t size);

extern inline void *
reallocarray_or_die(void *memory, size_t count, size_t element_size);

extern inline char *
strdup_or_die(char const *string);

extern inline int
vasprintf_or_die(char **string, const char *format, va_list arguments);
