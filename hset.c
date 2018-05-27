#include <stdio.h>
#include "hset.h"
#include "darray.h"
#include "config.h"

HSet* hset_init(unsigned long (*hash)(void*), unsigned int (*equals)(void*, void*)) {
  HSet* h = malloc(sizeof(HSet));

  h->hash = hash;
  h->equals = equals;
  h->data = darray_init();
}

void hset_destroy(HSet* h) {
  darray_destroy(h->data);
  free(h);
}

unsigned long _find_idx(HSet *h, void *item, unsigned long start_idx) {
  
  unsigned long tmp_idx = start_idx;
  void* tmp = darray_get(h->data, start_idx);

  while(h->equals(item, tmp) != 0) {
    tmp_idx = (tmp_idx+1) % DARRAY_PAGE_SIZE;
    tmp = darray_get(h->data, tmp_idx);
    if(tmp_idx == start_idx) {
      return -1;
    }
  }

  return tmp_idx;
}

void hset_add(HSet* h, void* item) {

  unsigned long idx = h->hash(item) % DARRAY_PAGE_SIZE;
  
  unsigned long real_idx = _find_idx(h,NULL,idx);

  if(real_idx != idx) {
    fprintf(stderr, "Collision!\n");
  }

  darray_set(h->data,item,real_idx);
}

void hset_remove(HSet* h, void* item) {

  unsigned long idx = h->hash(item) % DARRAY_PAGE_SIZE;
  unsigned long real_idx = _find_idx(h,item,idx);

  darray_set(h->data,NULL,real_idx);
}

long hset_contains(HSet *h, void *item) {
  unsigned long idx = h->hash(item) % DARRAY_PAGE_SIZE;
  unsigned long real_idx = _find_idx(h,item,idx);

  return real_idx;
}
