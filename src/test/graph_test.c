#include "dtype.h"
#include <stdio.h>
#include <math.h>

/*! \struct _MapNode 
 *  \brief Brief struct description
 *
 *  Detailed description
 */
typedef struct _MapNode {
  int x; /*!< Description */
  int y;
} MapNode;

void node_destroy(void *n) {
  MapNode *m = (MapNode*) n;
  free(m);
}

unsigned int node_equals(void *n1, void *n2) {
  MapNode *m1 = (MapNode*) n1;
  MapNode *m2 = (MapNode*) n2;
  return (m1->x == m2->x && m1->y == m2->y) ? 1 : 0;
}

unsigned long node_hash(void *n) {
  MapNode *m = (MapNode*) n;
  return (unsigned long) (m->x * m->y * 1009 + 1037);
}

MapNode *create_node(int x, int y) {

  MapNode *tmp = malloc(sizeof(MapNode));

  tmp->x = x;
  tmp->y = y;

  return tmp;
}

void print_node(void *n) {
  MapNode *m = (MapNode*) n;
  printf("(%d %d) ", m->x, m->y);
}

void print_graph(void *n) {
  if(n != NULL) {
    MapNode *m = (MapNode*) n;
    print_node(m);
    printf("-> ");
  }
}

double euclid(MapNode *m1, MapNode *m2) {
  int dx = m1->x - m2->x, dy = m1->y - m2->y;

  return sqrt(dx * dx + dy * dy);
}

int main() {

  Graph *g = graph_init(GRAPH_DIRECTED);

  MapNode *start = create_node(1, 1);
  MapNode *m1 = create_node(1, 2);
  MapNode *m2 = create_node(6, 1);
  MapNode *goal = create_node(9,1);

  graph_add(g,start);
  graph_add(g,m1);
  graph_add(g,m2);
  graph_add(g,goal);

  graph_connect(g, start, m1, euclid(start,m1));
  graph_connect(g, start, m2, euclid(start,m2));

  graph_connect(g, m1, goal, euclid(m1,goal));
  graph_connect(g, m2, goal, euclid(m2,goal));

  graph_print(g, print_node);

  graph_destroy(g, node_destroy);

  return 0;
}
