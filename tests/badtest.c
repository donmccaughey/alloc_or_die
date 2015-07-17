#include <stdio.h>
#include <stdlib.h>

#include "alloc_or_die.h"


int
main(int argc, char *argv[])
{
  char *name;
  if (argc > 1) {
    name = strdup_or_die(argv[1]);
  } else {
    name = strdup_or_die("world");
  }
  
  char *message;
  asprintf_or_die(&message, "Goodbye %s!", name);
  
  printf("%s\n", message);
  free_or_die(message);
  
  alloc_count_is_zero_or_die();
  return EXIT_SUCCESS;
}
