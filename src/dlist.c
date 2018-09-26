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

void dlist_remove(DList *list, void *item) {
  long tmp_idx = darray_find(list->data, item);
  if(tmp_idx > -1) {
    darray_set(list->data, NULL, tmp_idx);
  }
}

void* dlist_iterate(DList *list, void *start_after) {
  return darray_iterate(list->data, start_after);
}
