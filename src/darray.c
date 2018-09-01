#include "darray.h"
#include "config.h"

#include <stdio.h>
#include <stdlib.h>

DArray* darray_init() {

  DArray* d = malloc(sizeof(DArray));

  d->num_pages = 1;
  d->num_items = 0;
  d->data = malloc(sizeof(void**));
  d->data[0] = malloc(DARRAY_PAGE_SIZE * sizeof(void*));

  for(size_t ii = 0; ii < DARRAY_PAGE_SIZE; ii++) {
    d->data[0][ii] = NULL;
  }

  return d;

}


void darray_destroy(DArray* d, void (*destructor)(void*)) {

  size_t num_found = 0;
  for(size_t ii = 0; ii < d->num_pages; ii++) {
    for(size_t jj = 0; jj < DARRAY_PAGE_SIZE; jj++) {
      if(d->data[ii][jj] != NULL) {
        if(destructor == NULL) {
          free(d->data[ii][jj]);
        } else {
          destructor(d->data[ii][jj]);
        }
        num_found++;
      }
      if(num_found == d->num_items) {
        break;
      }
    }
    free(d->data[ii]);
  }
  free(d->data);
  free(d);
}

void darray_set(DArray* d, void* item, size_t idx) {
  size_t needed_page = idx / DARRAY_PAGE_SIZE;

  if(needed_page > (d->num_pages-1)) {
    void*** new_data = malloc((needed_page+1) * sizeof(void**));

    for(size_t ii = 0; ii < d->num_pages; ii++) {
      new_data[ii] = d->data[ii];
    }
    for(size_t ii = d->num_pages; ii < needed_page+1; ii++) {
      new_data[ii] = malloc(DARRAY_PAGE_SIZE * sizeof(void*));
      for(size_t jj = 0; jj < DARRAY_PAGE_SIZE; jj++) {
        new_data[ii][jj] = NULL;
      }
    }

    free(d->data);
    d->data = new_data;
    d->num_pages = needed_page+1;
  }

  void *current = d->data[needed_page][idx % DARRAY_PAGE_SIZE];

  d->data[needed_page][idx % DARRAY_PAGE_SIZE] = item;
  if(current == NULL && item != NULL) {
    d->num_items++;
  } else if(item == NULL && current != NULL) {
    d->num_items--;
  }

}

void* darray_get(DArray* d, size_t idx) {
  size_t needed_page = idx / DARRAY_PAGE_SIZE;

  if(needed_page > d->num_pages-1) {
    return NULL;
  } else {
    return (d->data[needed_page]) ? d->data[needed_page][idx % DARRAY_PAGE_SIZE] : NULL;
  }
}

void darray_print(DArray* d, void (*print_item)(void*)) {
  printf("   ");
  for(size_t ii = 0; ii < DARRAY_PAGE_SIZE; ii++) {
    printf("%4lu",ii);
  }
  printf("\n");
  for(size_t ii = 0; ii < d->num_pages; ii++) {
    printf("%lu: ",ii);
    for(size_t jj = 0; jj < DARRAY_PAGE_SIZE; jj++) {
      if(d->data[ii][jj] == NULL) {
        printf("   -");
      } else {
        print_item(d->data[ii][jj]);
      }
    }
    printf("\n");
  }
}


long darray_find(DArray *d, void *item) {
  for(size_t ii = 0; ii < d->num_pages * DARRAY_PAGE_SIZE; ii++) {
    if(darray_get(d,ii) == item) {
      return ii;
    }
  }
  return -1;
}
