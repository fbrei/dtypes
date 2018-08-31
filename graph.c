#include "graph.h"
#include <stdio.h>


Graph* graph_init(unsigned short is_directed) {

  Graph *tmp = malloc(sizeof(Graph));

  tmp->is_directed = is_directed;
  tmp->node_list = darray_init();
  tmp->edges = darray_init();

  return tmp;
}


void graph_destroy(Graph* g, void (*destructor)(void*)) {
  darray_destroy(g->node_list, destructor);
  for(size_t ii = 0; ii < g->edges->num_pages * DARRAY_PAGE_SIZE; ii++) {
    void *tmp = darray_get(g->edges, ii);
    if(tmp != NULL) {
      darray_destroy(tmp, NULL);
      darray_set(g->edges, NULL, ii);
    }
  }
  darray_destroy(g->edges, NULL);
  free(g);
}


void graph_add(Graph *g, void *node) {
  darray_set(g->node_list, node, g->node_list->num_items);
}

void graph_print(Graph *g, void (print_elem)(void*)) {
  for(size_t ii = 0; ii < g->node_list->num_items; ii++) {
    print_elem(darray_get(g->node_list,ii));
    void *tmp = darray_get(g->edges, ii);
    if(tmp != NULL) {
      printf(" -> ");
      DArray* neighbors = (DArray*) tmp;
      for(size_t jj = 0; jj < neighbors->num_pages * DARRAY_PAGE_SIZE; jj++) {
        void *n = darray_get(neighbors, jj);
        if(n != NULL) {
          if(*((int*) n) == 1) {
            print_elem(darray_get(g->node_list, jj));
          }
        }
      }
    }
    printf("\n");
  }
}

void graph_connect(Graph *g, void *first_node, void *second_node) {
  long first_idx = darray_find(g->node_list, first_node);
  long second_idx = darray_find(g->node_list, second_node);

  void* tmp = darray_get(g->edges, first_idx);
  if(tmp == NULL) {
    tmp = darray_init();
    darray_set(g->edges, tmp, first_idx);
  }

  short *one = malloc(sizeof(short));
  *one = 1;
  darray_set(tmp, one, second_idx);
}
