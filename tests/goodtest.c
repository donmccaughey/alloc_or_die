#include <earmark.h>
#include <stdio.h>
#include <stdlib.h>


int
main(int argc, char *argv[])
{
  char *name;
  if (argc > 1) {
    name = em_strdup(argv[1]);
  } else {
    name = em_strdup("world");
  }
  
  char *message;
  em_asprintf(&message, "Hello %s!", name);
  em_free(name);
  
  printf("%s\n", message);
  em_free(message);
  
  em_expect_alloc_count_zero();
  return EXIT_SUCCESS;
}
