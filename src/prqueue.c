#include <stdlib.h>
#include <stdio.h>

#include "prqueue.h"

PrQueue* prqueue_init(int (*compare)(void*,void*)) {

  PrQueue* p = malloc(sizeof(PrQueue));
  
  p->compare = compare;
  p->num_items = 0;
  p->data = darray_init();
  p->equals = NULL;

  return p;
}

void prqueue_destroy(PrQueue* pq, void (*destructor)(void*)) {
  darray_destroy(pq->data, destructor);
  free(pq);
}

void _swap_nodes(PrQueue* pq, size_t idx1, size_t idx2) {
  void *tmp = darray_get(pq->data,idx1);
  darray_set(pq->data, darray_get(pq->data,idx2),idx1);
  darray_set(pq->data,tmp,idx2);
}

void _reheap_up(PrQueue* pq, int idx) {
  if(idx != 0) {
    int parent_idx = (idx-1) / 2;  // Integer division on purpose (floor)

    if(pq->compare(darray_get(pq->data,idx),darray_get(pq->data,parent_idx)) < 0) {
      _swap_nodes(pq,idx,parent_idx);
      _reheap_up(pq, parent_idx);
    }
  }
}

void _reheap_down(PrQueue* pq, size_t idx) {
  size_t chosen = idx;
  
  size_t left_child = 2*chosen + 1;
  size_t right_child = 2*chosen + 2;

  if(left_child < pq->num_items && pq->compare(darray_get(pq->data,left_child), darray_get(pq->data,chosen)) < 0) {
    chosen = left_child;
  }
  if(right_child < pq->num_items && pq->compare(darray_get(pq->data,right_child), darray_get(pq->data,chosen)) < 0) {
    chosen = right_child;
  }

  if(chosen != idx) {
    _swap_nodes(pq,idx,chosen);
    _reheap_down(pq,chosen);
  }
}


void prqueue_add(PrQueue* pq, void* item) {
  darray_set(pq->data, item, pq->num_items);
  _reheap_up(pq, pq->num_items);

  pq->num_items++;
}

void* prqueue_pop(PrQueue* pq) {
  void* out = darray_get(pq->data,0);

  pq->num_items--;
  darray_set(pq->data,darray_get(pq->data,pq->num_items),0);
  darray_set(pq->data,NULL,pq->num_items);

  _reheap_down(pq,0);

  return out;
}

void prqueue_print(PrQueue* pq, void (*print_elem)(void*)) {
  darray_print(pq->data, print_elem);
} 

void _prqueue_replace(PrQueue *pq, void *old_item, void *new_item, int all) {
  if(pq->equals == NULL) {
    fprintf(stderr, "Please supply an equals function\n");
    return;
  }

  for(size_t ii = 0; ii < pq->num_items; ii++) {
    void *tmp = darray_get(pq->data,ii);
    if(pq->equals(tmp, old_item) != 0) {
      darray_set(pq->data,new_item,ii);

      int cmp = pq->compare(new_item,tmp);
      if(cmp < 0) {
        _reheap_up(pq,ii);
      } else if(cmp > 0) {
        _reheap_down(pq,ii);
      }

      if(!all) return;
    }
  }
}

void prqueue_replace(PrQueue *pq, void *old_item, void *new_item) {
  _prqueue_replace(pq,old_item,new_item,0);
}

void prqueue_replace_all(PrQueue *pq, void *old_item, void *new_item) {
  _prqueue_replace(pq,old_item,new_item,1);
}

unsigned int prqueue_contains(PrQueue *pq, void *item) {
  for(size_t ii = 0; ii < pq->num_items; ii++) {
    if(pq->equals(darray_get(pq->data,ii),item) != 0) {
      return 1;
    }
  }
  return 0;
}

void* prqueue_get(PrQueue *pq, void *item) {

  if(pq->num_items == 0) {
    return NULL;
  }

  for(size_t ii = 0; ii < pq->num_items; ii++) {
    void *tmp = darray_get(pq->data,ii);

    if(pq->equals(tmp,item)) {
      return tmp;
    }
  }
  return NULL;
}
