#include <stdio.h>
#include "hset.h"
#include "darray.h"
#include "config.h"

HSet* hset_init(unsigned long (*hash)(void*)) {
  HSet* h = malloc(sizeof(HSet));

  h->hash = hash;
  h->data = darray_init();
}

void hset_destroy(HSet* h) {
  darray_destroy(h->data);
  free(h);
}

void hset_add(HSet* h, void* item) {

    unsigned long idx = h->hash(item) % DARRAY_PAGE_SIZE;
    
    size_t tmp_idx = idx;
    void* tmp = darray_get(h->data, tmp_idx);
    while(tmp != NULL) {
      tmp_idx = (tmp_idx+1) % DARRAY_PAGE_SIZE;
      tmp = darray_get(h->data, tmp_idx);
      if(tmp_idx == idx) {
        fprintf(stderr, "The set is full!\n");
        return;
      }
    }
    darray_set(h->data,item,tmp_idx);
}

void hset_remove(HSet* h, void* item) {
  /* MOVE ME TO SOURCE FILE */
}
