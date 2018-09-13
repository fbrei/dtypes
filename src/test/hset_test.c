#include <stdio.h>

#include "include/hset.h"

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
  return 0l;
  /* MapNode *m = (MapNode*) n; */
  /* return (unsigned long) (m->x * m->y * 1009 + 1037); */
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
  printf("(%d,%d)", m->x, m->y);
}


int main() {

  HSet *h = hset_init(node_hash, node_equals);

  MapNode *m1 = create_node(1,2);
  MapNode *m2 = create_node(3,4);
  MapNode *m3 = create_node(5,6);


  hset_add(h, m1);
  hset_add(h, m2);
  hset_add(h, m3);
  hset_remove(h,m1);

  hset_destroy(h, node_destroy);

  return 0;
}
