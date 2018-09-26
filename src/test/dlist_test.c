#include "include/dtype.h"
#include <stdio.h>


int main(int argc, const char** argv) {

  DList *l = dlist_init();

  for(int ii = 0; ii < argc; ii++) {
    dlist_push(l, (void*) argv[ii]);
  }

  void *tmp = NULL;
  int idx = 0;
  while((tmp = dlist_iterate(l,tmp)) != NULL) {
    printf("%d -> %s\n", idx, (char*) tmp);
    idx += 1;
  }

  dlist_remove(l, (void*) argv[2]);

  tmp = NULL;
  idx = 0;
  while((tmp = dlist_iterate(l,tmp)) != NULL) {
    printf("%d -> %s\n", idx, (char*) tmp);
    idx += 1;
  }

  dlist_destroy(l, NULL);

  return 0;
}
