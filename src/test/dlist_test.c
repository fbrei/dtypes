#include "dtype.h"
#include <stdio.h>


int main(int argc, const char** argv) {

  DList *l = dlist_init();

  for(int ii = 0; ii < argc; ii++) {
    dlist_push(l, (void*) argv[ii]);
  }

  void *tmp = NULL;
  while((tmp = dlist_iterate(l,tmp)) != NULL) {
    printf("%s\n", (char*) tmp);
  }

  dlist_destroy(l, NULL);

  return 0;
}
