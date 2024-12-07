__*** Archived *** Archived *** Archived ***__

I've rebuilt this library from the ground up and renamed it to `xmalloc`.
Please find it at https://git.sr.ht/~donmcc/xmalloc.

__*** Archived *** Archived *** Archived ***__

alloc_or_die
============

Fail-fast wrappers around C memory allocation functions for C99.

Alloc_or_die performs two functions:

1. It checks for memory allocation failure and exits if allocation fails.
2. It keeps a tally of memory allocations and warns about leaks.


License
-------
Alloc_or_die is made available under a BSD-style license; see the LICENSE file 
for details.


Usage
-----

Use `malloc_or_die()`, `free_or_die()` and other memory management functions 
instead of the standard library ones.  Alloc_or_die wrappers have the same 
names and signatures, suffixed with `_or_die`.

Alloc_or_die has wrappers for the following standard functions:

- `calloc()`
- `malloc()`
- `realloc()`
- `strdup()`
- `asprintf()`
- `vasprintf()`
- `getcwd()`
- `free()`
  
Alloc_or_die also defines the following convenience functions:

- `arraydup_or_die()`: like `strdup()`, makes a copy of an array when you 
  know the count of elements and the size of each element.
- `memdup_or_die()`: like `strdup()`, makes a copy of memory given a 
  pointer and a size.
- `reallocarray_or_die()`: like `reallocarray()` from OpenBSD, calls 
  `realloc()` to resize an array given the count of elements and the size
  of each element; checks the calculated memory size for overflow.

To check for memory leaks call `alloc_count_is_zero_or_die()` before your 
program exits.

    #include <alloc_or_die.h>

    int
    main(int argc, char *argv[])
    {
        char *message = strdup_or_die("Hello world!");
        // ...
        free_or_die(message);

        alloc_count_is_zero_or_die();
        return EXIT_SUCCESS;
    }

If the count of alloc_or_die allocation calls match the count of 
`free_or_die()` calls, `alloc_count_is_zero_or_die()` is silent; otherwise, 
`alloc_count_is_zero_or_die()` prints a warning to `stderr` with the 
allocation count, like this:

    WARNING: 1 memory allocation not freed.

Note that a _negative_ allocation count usually indicates calls to 
`free_or_die()` were made for memory allocated with plain old `malloc()` or one 
of its relatives.

There's no build system yet, but alloc_or_die consists of single header and 
`.c` file, so it's easy to drop into a project.


Rationale: Fail Fast
--------------------

Memory allocation can fail. Under some circumstances (e.g allocating large 
memory blocks for processing a media file), the possibility of failure is 
expected and dealing with failure is straight-forward.

In most other circumstances, programs are allocating many small blocks of
memory as part of more complex operations. A failure of one of these common 
small allocations usually indicates that the program or the system is in a bad 
state (e.g. allocations are happening in an infinite loop or virtual memory is 
exhausted). Recovering from this type of failure state is tricky at best and 
may not be possible.

Writing code that is robust in the face of memory allocation failure has a real
cost in terms of development time and code complexity, and is difficult to test 
thoroughly. For many programs, it makes more sense to treat the failure of a 
common small allocation as an unrecoverable error.

