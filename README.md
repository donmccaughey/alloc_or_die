EarMark
=======

A fail-fast wrapper around C library memory allocation functions.

EarMark performs two functions:

  1.  It checks for memory allocation failure and exits if allocation fails.
  2.  It optionally keeps a tally of memory allocations and warns about leaks.


License
-------
EarMark is made available under a BSD-style license; see the LICENSE file for 
details.


Usage
-----

Use `em_malloc()`, `em_free()` and other memory management functions instead of
the standard library ones.  EarMark wrappers have the same names and 
signatures, prefixed with `em_`.

EarMark has wrappers for the following standard functions:

  -   `calloc()`
  -   `malloc()`
  -   `realloc()`
  -   `strdup()`
  -   `asprintf()`
  -   `vasprintf()`
  -   `free()`
  
EarMark also defines the following convenience functions:

  -   `em_arraydup()`: like `strdup()`, makes a copy of an array when you know
      the count of elements and the size of each element.
  -   `em_memdup()`: like `strdup()`, makes a copy of memory given a pointer 
      and a size.
  -   `em_reallocarray()`: like `reallocarray()` from OpenBSD, calls 
      `realloc()` to resize an array given the count of elements and the size
      of each element; checks the resulting memory size for overflow.

To check for memory leaks, define `EM_COUNT_ALLOCS` when building EarMark and 
call `em_expect_alloc_count_zero()` before your program exits.

    #include <earmark.h>

    int
    main(int argc, char *argv[])
    {
      char *message = em_strdup("Hello world!");
      // ...
      em_free(message);
      
      em_expect_alloc_count_zero();
      return EXIT_SUCCESS;
    }

There's no build system yet, but EarMark consists of single header and `.c` 
file, so it's easy to drop into a project.


Rationale: Fail Fast
--------------------

Memory allocation can fail. Under some circumstances, such as when attempting 
to allocate a large memory block for processing a media file, the possibility 
of failure is expected, and the program can handle the failure in a safe and 
rational fashion and continue running.

In most other circumstances, programs are allocating many small blocks of 
memory as part of more complex operations. A failure of one of these routine 
small allocations indicates that the program or the system is in a bad state. 

Writing code that is robust in the face of memory allocation failure has a real
cost in terms of development time and code complexity, and it's difficult to 
test thoroughly. For many programs, it makes more sense to treat the failure
of a routine small allocation as an unrecoverable error.

