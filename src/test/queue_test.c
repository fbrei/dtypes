#include <stdio.h>

#include "include/queue.h"

int main(int argc, const char** argv) {

  Queue *q = queue_init();

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

  while((current = queue_pop(q)) != NULL) {
    printf("Value: %d\n", *((int*) current));
  }

  queue_destroy(q);

  return 0;
}
