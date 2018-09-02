#include "dtype.h"
#include <stdio.h>
#include <math.h>

typedef struct _MapNode {
  int x; 
  int y;

  double total_dist;
  double estimate;

  void *parent;
} MapNode;

void node_destroy(void *n) {
  MapNode *m = (MapNode*) n;
  free(m);
}

unsigned int node_equals(void *n1, void *n2) {

  if( (n1 == NULL && n2 != NULL) || (n1 != NULL && n2 == NULL) ) {
    return 0;
  }

  if(n1 == NULL && n2 == NULL) {
    return 1;
  }

  MapNode *m1 = (MapNode*) n1;
  MapNode *m2 = (MapNode*) n2;
  return (m1->x == m2->x && m1->y == m2->y) ? 1 : 0;
}

unsigned long node_hash(void *n) {
  MapNode *m = (MapNode*) n;
  return (unsigned long) (m->x * m->y * 1009 + 1037);
}

int node_comare_to(void *n1, void *n2) {

  MapNode *m1 = (MapNode*) n1;
  MapNode *m2 = (MapNode*) n2;

  double first_score = m1->total_dist + m1->estimate;
  double second_score = m2->total_dist + m2->estimate;

  if(first_score > second_score) {
    return 1;  
  } else if(first_score < second_score) {
    return -1;
  } else {
    return 0;
  }
}

MapNode *create_node(int x, int y) {

  MapNode *tmp = malloc(sizeof(MapNode));

  tmp->x = x;
  tmp->y = y;
  tmp->total_dist = 0.0;
  tmp->estimate = 0.0;
  tmp->parent = NULL;

  return tmp;
}

void print_node(void *n) {
  MapNode *m = (MapNode*) n;
  printf("(%d %d) ", m->x, m->y);
}

double euclid(MapNode *m1, MapNode *m2) {
  int dx = m1->x - m2->x, dy = m1->y - m2->y;

  return sqrt(dx * dx + dy * dy);
}

DArray* expand_node(Graph *g, MapNode *m) {

  DArray *neighbors = graph_get_neighbors(g,m);
  return neighbors;

}

int main() {

  Graph *g = graph_init(GRAPH_DIRECTED);

  MapNode *start = create_node(1, 1);
  MapNode *m1 = create_node(1, 2);
  MapNode *m2 = create_node(6, 1);
  MapNode *goal = create_node(9,1);

  start->estimate = euclid(start,start) + euclid(start, goal);

  graph_add(g,start);
  graph_add(g,m1);
  graph_add(g,m2);
  graph_add(g,goal);

  graph_connect(g, start, m1, euclid(start,m1));
  graph_connect(g, start, m2, euclid(start,m2));

  graph_connect(g, m1, goal, euclid(m1,goal));
  graph_connect(g, m2, goal, euclid(m2,goal));

  // Let's try some A*
  
  PrQueue *frontier = prqueue_init(node_comare_to);
  HSet *explored = hset_init(node_hash, node_equals);

  prqueue_add(frontier, start);


  void *tmp = NULL;
  int n_steps = 0;
  while(1) {
    n_steps++;
    tmp = prqueue_pop(frontier);
    if(tmp == NULL) {
      break;
    }
    MapNode *current = (MapNode*) tmp;

    if(node_equals(current, goal) == 1) {
      printf("Hurray!\n");
      break;
    }

    DArray *neighbors = expand_node(g, current);

    if(neighbors == NULL) {
      continue;
    }

    void *tmp2 = NULL;
    while((tmp2 = darray_iterate(neighbors,tmp2)) != NULL) {
      MapNode *m = (MapNode*) tmp2;
      m->total_dist = current->total_dist + *graph_get_edge_weight(g,current,m);
      m->estimate = euclid(m, goal);
      m->parent = current;
      prqueue_add(frontier, m);
    }

    darray_destroy(neighbors, NULL);
  }

  printf("%d\n",n_steps);

  while(1) {
    print_node((MapNode*) tmp);
    tmp = ((MapNode*) tmp)->parent;
    if(tmp) {
      printf(" -> ");
    } else {
      break;
    }
  }

  prqueue_destroy(frontier, NULL);
  hset_destroy(explored, NULL);

  graph_destroy(g, node_destroy);

  return 0;
}
