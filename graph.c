#include "graph.h"


Graph* graph_init(unsigned short is_directed) {

  Graph *tmp = malloc(sizeof(Graph));

  tmp->is_directed = is_directed;
  tmp->node_list = darray_init();
  tmp->connections = darray_init();

  return tmp;
}


void graph_destroy(Graph *g) {
  darray_destroy(g->node_list);
  darray_destroy_recursive(g->connections, darray_destroy);
  free(g);
}


void graph_add(Graph *g, void *node) {
  darray_set(g->node_list, node, g->node_list->num_items);
}

void graph_print(Graph *g, void (print_elem)(void*)) {
  for(size_t ii = 0; ii < g->node_list->num_items; ii++) {
    print_elem(darray_get(g->node_list,ii));
  }
}

void graph_connect(Graph *g, void *first_node, void *second_node) {
  long first_idx = darray_find(g->node_list, first_node);
  long second_idx = darray_find(g->node_list, second_node);

  void* tmp = darray_get(g->connections, first_idx);
  if(tmp == NULL) {
    tmp = darray_init();
  }

  short *one = malloc(sizeof(short));
  *one = 1;
  darray_set(tmp, one, second_idx);
}
