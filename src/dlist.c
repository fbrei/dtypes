#include "include/dlist.h"

DList* dlist_init() {
  DList *tmp = malloc(sizeof(DList));
  tmp->data = darray_init();
  tmp->num_items = 0;

  return tmp;
}

void dlist_destroy(DList *list, void (*destructor)(void*)) {
  darray_destroy(list->data, destructor);
  free(list);
}

void dlist_push(DList *list, void *item) {
  darray_set(list->data, item, list->num_items);
  list->num_items++;
}

void* dlist_iterate(DList *list, void *start_after) {
  if(start_after) {
    long tmp_idx = darray_find(list->data, start_after);
    size_t idx = (tmp_idx > -1) ? tmp_idx : 0;
    return darray_get(list->data, idx+1);
  } else {
    return darray_get(list->data, 0);
  }
}
