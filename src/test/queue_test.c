#include <stdio.h>

#include "include/queue.h"

unsigned int equals(void *a, void *b) {
  return a == b ? 1 : 0;
}

int main(int argc, const char** argv) {

  Queue *q = queue_init();
  q->equals =  equals;

  int x = 3, y = -4 , z = 12;

  queue_push(q, &x);
  queue_push(q, &y);
  queue_push(q, &z);

  void *current = NULL;

  while((current = queue_pop(q)) != NULL) {
    printf("Value: %d\n", *((int*) current));
  }

  x = 1, y = 2, z = 3;

  queue_push(q, &x);
  queue_push(q, &y);
  queue_push(q, &z);
  if(queue_contains(q, &x)) {
    printf("Containment test No. 1 passed.\n");
  } else {
    printf("Containment test No. 1 failed.\n");
  }

  while((current = queue_pop(q)) != NULL) {
    printf("Value: %d\n", *((int*) current));
  }

  if(!queue_contains(q, &x)) {
    printf("Containment test No. 2 passed.\n");
  } else {
    printf("Containment test No. 2 failed.\n");
  }

  queue_destroy(q);

  return 0;
}
