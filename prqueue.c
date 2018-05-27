#include <stdlib.h>
#include <stdio.h>

#include "prqueue.h"

PrQueue* prqueue_init(int (*compare)(void*,void*)) {

  PrQueue* p = malloc(sizeof(PrQueue));
  
  p->compare = compare;
  p->_highest_idx = -1;
  p->data = darray_init();

  return p;
}

void prqueue_destroy(PrQueue* pq) {
  darray_destroy(pq->data);
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

void _reheap_down(PrQueue* pq, int idx) {
  int chosen = idx;
  
  int left_child = 2*chosen + 1;
  int right_child = 2*chosen + 2;

  if(left_child <= pq->_highest_idx && pq->compare(darray_get(pq->data,left_child), darray_get(pq->data,chosen)) < 0) {
    chosen = left_child;
  }
  if(right_child <= pq->_highest_idx && pq->compare(darray_get(pq->data,right_child), darray_get(pq->data,chosen)) < 0) {
    chosen = right_child;
  }

  if(chosen != idx) {
    _swap_nodes(pq,idx,chosen);
    _reheap_down(pq,chosen);
  }
}


void prqueue_insert(PrQueue* pq, void* item) {
  pq->_highest_idx++;

  darray_set(pq->data, item, pq->_highest_idx);
  _reheap_up(pq, pq->_highest_idx);
}

void* prqueue_pop(PrQueue* pq) {
  void* out = darray_get(pq->data,0);

  darray_set(pq->data,darray_get(pq->data,pq->_highest_idx),0);
  darray_set(pq->data,NULL,pq->_highest_idx);
  pq->_highest_idx--;

  _reheap_down(pq,0);

  return out;
}

void prqueue_print(PrQueue* pq, void (*print_elem)(void*)) {
  darray_print(pq->data, print_elem);
} 
