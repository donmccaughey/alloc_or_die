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


#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


extern long alloc_or_die_count;


////////// Building Blocks //////////

// Calculate the array size in bytes.  Set `errno' to EOVERFLOW and call
// `print_error_and_die()' if the calculated array size overflows.
size_t
array_size_or_die(size_t count, size_t element_size);

// Prints the current error message and calls `exit()' with the value of
// `errno'.  If `errno' is zero, sets it to ENOMEM first.
inline void
print_error_and_die(void)
{
  if ( ! errno) errno = ENOMEM;
  perror(NULL);
  exit(errno);
}

// If `memory' is NULL, calls exit() with an error code, otherwise increments
// `alloc_or_die_count' and returns `memory'.
inline void *
not_null_or_die(void *memory)
{
  if ( ! memory) print_error_and_die();
  ++alloc_or_die_count;
  return memory;
}


////////// Allocation Wrappers //////////

inline void *
calloc_or_die(size_t count, size_t element_size)
{
  return not_null_or_die(calloc(count, element_size));
}

inline void *
malloc_or_die(size_t size)
{
  return not_null_or_die(malloc(size));
}

inline void *
memdup_or_die(void const *memory, size_t size)
{
  void *dupe = malloc_or_die(size);
  memcpy(dupe, memory, size);
  return dupe;
}

inline void *
arraydup_or_die(void const *memory, size_t count, size_t element_size)
{
  return memdup_or_die(memory, array_size_or_die(count, element_size));
}

inline void *
realloc_or_die(void *memory, size_t size)
{
  void *new_memory = realloc(memory, size);
  if ( ! new_memory) print_error_and_die();
  if ( ! memory) ++alloc_or_die_count;
  return new_memory;
}

inline void *
reallocarray_or_die(void *memory, size_t count, size_t element_size)
{
  return realloc_or_die(memory, array_size_or_die(count, element_size));
}

inline char *
strdup_or_die(char const *string)
{
  return not_null_or_die(strdup(string));
}

int
asprintf_or_die(char **string, char const *format, ...);

inline int
vasprintf_or_die(char **string, const char *format, va_list arguments)
{
  int result = vasprintf(string, format, arguments);
  if (-1 == result) print_error_and_die();
  ++alloc_or_die_count;
  return result;
}


////////// Allocation Counting //////////

inline void
free_or_die(void *memory)
{
  free(memory);
  if (memory) --alloc_or_die_count;
}

void
alloc_count_is_zero_or_die(void);


#endif
