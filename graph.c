#include "graph.h"


Graph* graph_init(unsigned short is_directed) {

  Graph *tmp = malloc(sizeof(Graph));

  tmp->is_directed = is_directed;
  tmp->num_nodes = 0;
  tmp->node_list = darray_init();

  return tmp;
}


void graph_destroy(Graph *g) {
  darray_destroy(g->node_list);
  free(g);
}


void graph_add(Graph *g, void *node) {
  /* MOVE ME TO SOURCE FILE */
}
