#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "include/queue.h"

/**
 * \brief Brief description
 *
 * Long description
 */
typedef struct __QueueItem {
  struct __QueueItem *prev; 		/**< description */
  struct __QueueItem *next; 		/**< description */
  void *data; 		/**< description */
} _QueueItem;

Queue* queue_init() {

  Queue *q = malloc(sizeof(Queue));
  q->_first = NULL;
  q->_last = NULL;
  q->equals = NULL;

  return q;
}

void queue_push(Queue *q, void *data) {
  if(q->_first == NULL && q->_last == NULL) {
    q->_first = malloc(sizeof(_QueueItem));
    q->_first->data = data;
    q->_first->next = NULL;
    q->_first->prev = NULL;
    q->_last = q->_first;
  } else {
    q->_last->next = malloc(sizeof(_QueueItem));

    q->_last->next->prev = q->_last;
    q->_last->next->next = NULL;

    q->_last = q->_last->next;
    q->_last->data = data;
  }
}

void *queue_pop(Queue *q) {

  // Grab the data
  if(q->_first == NULL) {
    return NULL;
  }

  void *data = q->_first->data;

  // Update the structure
  if(q->_first == q->_last) {
    q->_last = NULL;
  }
  struct __QueueItem *new_first = q->_first->next;

  free(q->_first);
  q->_first = new_first;
  if(new_first) {
    q->_first->prev = NULL;
  }

  return data;
}

void *queue_top(Queue *q) {
  return q->_first;
}

void queue_destroy(Queue *q) {
  while(q->_first) {
    free(q->_first);
    q->_first = q->_first->next;
  }
  free(q);
}

unsigned int queue_contains(Queue *q, void *item) {
  assert(q->equals != NULL);

  struct __QueueItem *current = q->_first;

  while(current != NULL) {
    if(q->equals(current->data, item)) {
      return 1;
    }
    current = current->next;
  }

  return 0;
}
