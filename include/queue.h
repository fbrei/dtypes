/**
 *	\file queue.h
 *  \brief API for a simple queue (FIFO)
 *
 *  Manages a queue based on a linked list.
 *
 *	\date 2019/04/16
 *	\author Felix Brei
 *
 *	\bug No known bugs.
 */

#ifndef QUEUE_H_2QBZFVYI
#define QUEUE_H_2QBZFVYI

struct __QueueItem;

/**
 * \brief Holds a simple Queue based on a linked list
 *
 * Insertion and removal is O(1). Please do not manipulate the pointers directly.
 */
typedef struct _Queue {
  struct __QueueItem *_first; 		/**< Pointer to first element */
  struct __QueueItem *_last; 		/**< Pointer to last element */
} Queue;

#endif /* end of include guard: QUEUE_H_2QBZFVYI */

/**
 * \brief Brief description
 *
 * Long description
 * 
 * \return Return value, delete if void
 */
Queue* queue_init();

/**
 * \brief Push an item to the end of a given Queue
 *
 * Adds an item at the final position
 * 
 * \param *q The queue
 * \param *data The item/data
 */
void queue_push(Queue *q, void *data);



/**
 * \brief Pop the front item from the queue (removes it)
 *
 * Grab the first item from the queue, removing it in the process
 * 
 * \param *q The queue
 * \return Pointer to the item that was removed
 */
void *queue_pop(Queue *q);

/**
 * \brief Peek at the front item of a queue
 *
 * The item stays in the queue. Note that you could also access it by
 * q->_first, but this way is more conventional.
 * 
 * \param *q The queue
 * \return Pointer to the first item
 */
void *queue_top(Queue *q);


/**
 * \brief Frees the memory occupied by a queue.
 *
 * This does not destroy the data itself, just the structure that holds the data
 * 
 * \param *q The queue to be deleted
 */
void queue_destroy(Queue *q);
