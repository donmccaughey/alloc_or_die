/* EarMark. https://github.com/AblePear/EarMark
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

#include "earmark.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define SQRT_SIZE_MAX_PLUS_1 (1UL << (sizeof(size_t) * 4))


#ifdef EM_COUNT_ALLOCS

static int alloc_count = 0;

#define INCREMENT_ALLOC_COUNT() (++alloc_count)

#define DECREMENT_ALLOC_COUNT() (--alloc_count)

#define EXPECT_ALLOC_COUNT_ZERO() \
    if (alloc_count) { \
      char const *plural = (1 == alloc_count) ? "" : "s"; \
      fprintf(stderr, "WARNING: %i memory allocation%s not freed.\n", \
              alloc_count, plural); \
    }

#else

#define INCREMENT_ALLOC_COUNT()
#define DECREMENT_ALLOC_COUNT()
#define EXPECT_ALLOC_COUNT_ZERO()

#endif


static size_t
array_size(size_t count, size_t element_size);

static void
fail_and_exit(void);


static size_t
array_size(size_t count, size_t element_size)
{
  if (count >= SQRT_SIZE_MAX_PLUS_1 || element_size >= SQRT_SIZE_MAX_PLUS_1) {
    if (element_size && count > SIZE_MAX / element_size) {
      errno = EOVERFLOW;
      fail_and_exit();
    }
  }
  return count * element_size;
}


static void
fail_and_exit(void)
{
  if (errno) {
    perror(NULL);
    exit(errno);
  } else {
    fprintf(stderr, "Memory allocation failure\n");
    exit(EXIT_FAILURE);
  }
}


void *
em_calloc(size_t count, size_t element_size)
{
  void *memory = calloc(count, element_size);
  if ( ! memory) fail_and_exit();
  INCREMENT_ALLOC_COUNT();
  return memory;
}


void *
em_malloc(size_t size)
{
  void *memory = malloc(size);
  if ( ! memory) fail_and_exit();
  INCREMENT_ALLOC_COUNT();
  return memory;
}


void *
em_arraydup(void const *memory, size_t count, size_t element_size)
{
  size_t size = array_size(count, element_size);
  return em_memdup(memory, size);
}


void *
em_memdup(void const *memory, size_t size)
{
  void *dupe = em_malloc(size);
  memcpy(dupe, memory, size);
  return dupe;
}


void *
em_realloc(void *memory, size_t size)
{
  void *new_memory = realloc(memory, size);
  if ( ! new_memory) fail_and_exit();
  if ( ! memory) INCREMENT_ALLOC_COUNT();
  return new_memory;
}


void *
em_reallocarray(void *memory, size_t count, size_t element_size)
{
  size_t size = array_size(count, element_size);
  return em_realloc(memory, size);
}


char *
em_strdup(char const *string)
{
  char *dupe = strdup(string);
  if ( ! dupe) fail_and_exit();
  INCREMENT_ALLOC_COUNT();
  return dupe;
}


int
em_asprintf(char **string, char const *format, ...)
{
  va_list arguments;
  va_start(arguments, format);
  int result = em_vasprintf(string, format, arguments);
  va_end(arguments);
  return result;
}


int
em_vasprintf(char **string, const char *format, va_list arguments)
{
  int result = vasprintf(string, format, arguments);
  if (-1 == result) fail_and_exit();
  INCREMENT_ALLOC_COUNT();
  return result;
}


void
em_free(void *memory)
{
  free(memory);
  if (memory) DECREMENT_ALLOC_COUNT();
}


void
em_expect_alloc_count_zero(void)
{
  EXPECT_ALLOC_COUNT_ZERO();
}
