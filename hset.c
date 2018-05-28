#include <stdio.h>
#include "hset.h"
#include "darray.h"
#include "config.h"

HSet* hset_init(unsigned long (*hash)(void*), unsigned int (*equals)(void*, void*)) {
  HSet* h = malloc(sizeof(HSet));

  h->hash = hash;
  h->equals = equals;
  h->data = darray_init();
  h->marker = malloc(1);

  return h;
}

void hset_destroy(HSet* h) {
  darray_destroy(h->data);
  free(h->marker);
  free(h);
}

void hset_add(HSet* h, void* item) {

  unsigned long idx = h->hash(item) % DARRAY_PAGE_SIZE;
  
  unsigned long real_idx = idx;
  void* tmp;

  while(1) {
    tmp = darray_get(h->data, real_idx);
    if(tmp == h->marker || tmp == NULL) {
      darray_set(h->data,item,real_idx);
      return;
    }
    real_idx = (real_idx + 1) % DARRAY_PAGE_SIZE;
    if(real_idx == idx) {
      return;
    }
  }
}

void hset_remove(HSet* h, void* item) {

  unsigned long idx = h->hash(item) % DARRAY_PAGE_SIZE;
  unsigned long real_idx = idx;
  void* tmp;

  while(1) {
    tmp = darray_get(h->data, real_idx);
    if(tmp == NULL) {
      return;
    } else if(h->equals(tmp,item) == 0) {
      darray_set(h->data,h->marker,real_idx);
      return;
    } else {
      real_idx = (real_idx + 1) % DARRAY_PAGE_SIZE;
    }
  }

}

long hset_contains(HSet *h, void *item) {
  unsigned long idx = h->hash(item) % DARRAY_PAGE_SIZE;
  unsigned long real_idx = idx;
  void* tmp;

  while(1) {
    tmp = darray_get(h->data, real_idx);

    if(tmp == NULL) {
      return -1;
    } else if(tmp == h->marker) {
      real_idx = (real_idx + 1) % DARRAY_PAGE_SIZE;
    } else if(h->equals(tmp,item) == 0) {
      return real_idx;
    } else {
      real_idx = (real_idx + 1) % DARRAY_PAGE_SIZE;
    }

    if(real_idx == idx) {
      return -1;
    }
  }
}

void hset_print(HSet *h, void (*print_elem)(void*)) {
  void _print_element(void* v) {
    if(v == NULL) {
      printf("   -");
    } else if(v == h->marker) {
      printf("   x");
    } else {
      print_elem(v);
    }
  }
  darray_print(h->data, _print_element);
}
