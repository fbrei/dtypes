#include "darray.h"
#include "config.h"

DArray darray_init() {

  DArray d = { .num_pages = 1, .data = malloc(sizeof(void*)) };
  d.data[0] = malloc(DARRAY_PAGE_SIZE * sizeof(void*));

  return d;

}

void darray_destroy(DArray* d) {
  for(size_t ii = 0; ii < d->num_pages; ii++) {
    free(d->data[ii]);
  }
  free(d->data);
}
