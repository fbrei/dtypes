#include "graph.h"
#include <stdio.h>


Graph* graph_init(enum GRAPH_PROP is_directed) {

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
      DArray* neighbors = (DArray*) tmp;
      for(size_t jj = 0; jj < neighbors->num_pages * DARRAY_PAGE_SIZE; jj++) {
        void *n = darray_get(neighbors, jj);
        if(n != NULL) {
          double w = *((double*) n);
          if(w != 0.0) {
            printf(" -- %4.2lf --> ", w);
            print_elem(darray_get(g->node_list, jj));
          }
        }
      }
    }
    printf("\n");
  }
}

void graph_connect(Graph *g, void *first_node, void *second_node, double edge_weight) {
  long first_idx = darray_find(g->node_list, first_node);
  long second_idx = darray_find(g->node_list, second_node);

  void* tmp = darray_get(g->edges, first_idx);
  if(tmp == NULL) {
    tmp = darray_init();
    darray_set(g->edges, tmp, first_idx);
  }

  double *weight = malloc(sizeof(double));
  *weight = edge_weight;
  darray_set(tmp, weight, second_idx);
}
