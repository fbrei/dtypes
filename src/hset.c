#include "include/hset.h"
#include "include/darray.h"
#include "include/config.h"

HSet* hset_init(unsigned long (*hash)(void*), unsigned int (*equals)(void*, void*)) {
  HSet* h = malloc(sizeof(HSet));

  h->hash = hash;
  h->equals = equals;
  h->data = darray_init();
  h->marker = malloc(1);

  h->num_items = 0;
  h->max_items = DARRAY_PAGE_SIZE;

  return h;
}

void hset_destroy(HSet* h, void (*destructor)(void*)) {
  size_t num_found = 0;
  for(size_t ii = 0; ii < h->data->num_pages; ii++) {
    for(size_t jj = 0; jj < DARRAY_PAGE_SIZE; jj++) {
      if(h->data->data[ii][jj] == h->marker) {
        continue;
      }
      if(h->data->data[ii][jj] != NULL) {
        if(destructor != NULL) {
          destructor(h->data->data[ii][jj]);
        } 
        num_found++;
      }
      if(num_found == h->num_items) {
        break;
      }
    }
    free(h->data->data[ii]);
  }
  free(h->data->data);
  free(h->data);
  free(h->marker);
  free(h);
}

void _rehash(HSet *h) {
  void **tmp = malloc(h->max_items * sizeof(void*));

  for(size_t ii = 0; ii < h->max_items; ii++) {
    tmp[ii] = darray_get(h->data,ii);
    darray_set(h->data,NULL,ii);
  }

  h->num_items = 0;
  h->max_items = h->max_items + DARRAY_PAGE_SIZE;

  for(size_t ii = 0; ii < h->max_items - DARRAY_PAGE_SIZE; ii++) {
    if(tmp[ii] != NULL && tmp[ii] != h->marker) {
      hset_add(h,tmp[ii]);
    }
  }

  free(tmp);
}

void hset_add(HSet* h, void* item) {

  if(h->num_items > h->max_items * HSET_MAX_RATIO) {
    _rehash(h);
  }

  unsigned long idx = h->hash(item) % h->max_items;
  
  unsigned long real_idx = idx;
  void* tmp;

  while(1) {
    tmp = darray_get(h->data, real_idx);
    if(tmp == h->marker || tmp == NULL) {
      darray_set(h->data,item,real_idx);
      h->num_items++;
      return;
    }
    if(h->equals(tmp, item)) {
      return;
    }
    real_idx = (real_idx + 1) % h->max_items;
    if(real_idx == idx) {
      return;
    }
  }
}

void hset_remove(HSet* h, void* item) {

  unsigned long idx = h->hash(item) % h->max_items;
  unsigned long real_idx = idx;
  void* tmp;

  while(1) {
    tmp = darray_get(h->data, real_idx);
    if(tmp == NULL) {
      return;
    } else if(h->equals(tmp,item) == 1) {
      darray_set(h->data,h->marker,real_idx);
      return;
    } else {
      real_idx = (real_idx + 1) % h->max_items;
    }
  }

}

long hset_contains(HSet *h, void *item) {
  size_t idx = h->hash(item) % h->max_items;
  size_t real_idx = idx;
  void* tmp;

  while(1) {
    tmp = darray_get(h->data, real_idx);

    if(tmp == NULL) {
      return -1;
    } else if(tmp == h->marker) {
      real_idx = (real_idx + 1) % h->max_items;
    } else if(h->equals(tmp,item) == 1) {
      return real_idx;
    } else {
      real_idx = (real_idx + 1) % h->max_items;
    }

    if(real_idx == idx) {
      return -1;
    }
  }
}

void hset_print(HSet *h, void (*print_elem)(void*)) {
  darray_print(h->data, print_elem);
}

void hset_apply(HSet *h, void (*f)(void*)) {
  size_t num_found = 0;
  for(size_t ii = 0; ii < h->max_items; ii++) {
    void *item = darray_get(h->data,ii);
    if(item != NULL && item != h->marker) {
      num_found++;
      f(item);
    }
    if(num_found >= h->num_items) {
      break;
    }
  }
}

unsigned long NULLHASH(void *item) {
  (void)(item);
  return 0l;
}
