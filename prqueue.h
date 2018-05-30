/**
 *	\file prqueue.h
 *  \brief API for a heap based priority queue
 *
 *	A priority queue that is backed by an array with an implied
 *	heap structure. The number of elements should be known beforehand.
 *
 *	\date 2018/05/27
 *	\author Felix Brei
 *
 *	\bug No known bugs.
 */

#ifndef PRQUEUE_H_P3USRWA2
#define PRQUEUE_H_P3USRWA2

#include "darray.h"

/**
 * \brief Priority queue
 *
 * Heap based implementation of a priority queue. The heap is
 * backed by a DArray.
 */
typedef struct _PrQueue {
  DArray* data;		                        /**< Array of pointers that point to the actual objects */

  int (*compare)(void*,void*); 	          /**< The comparison function, should return -1, 0, or 1 for <, =, or > (considering priority) */
  unsigned int (*equals)(void*,void*);    /**< Checks whether two elements are equal (not necessarily in priority) */

  int _highest_idx;                        /**< Stores the highest used index. */
} PrQueue;


/**
 * \brief Initialize a priority queue
 *
 * Initializes a priority queue with given parameters.
 * 
 * \param num_items The number of items to hold.
 * \param (*compare)(void*,void*) The comparison function.
 * \return The constructed queue.
 */
PrQueue* prqueue_init(int (*compare)(void*,void*));

/**
 * \brief Destroy a given queue
 *
 * Frees the memory that is occupied by a queue
 * 
 * \param pq The queue that should be destroyed.
 */
void prqueue_destroy(PrQueue* pq);

/**
 * \brief Prints all elements to the screen
 * 
 * Turns all items into strings using the represent method
 * and then prints it out.
 *  
 * \param pq The queue that holds the items
 */
void prqueue_print(PrQueue* pq, void (*print_elem)(void*));

/**
 * \brief Inserts an element into the queue
 *
 * Inserts an element into the queue in the right place,
 * determined by the compare method.
 *
 * \param pq The queue.
 * \param item The item.
 */
void prqueue_insert(PrQueue* pq, void* item);

/**
 * \brief Removes the front element.
 *
 * Returns a pointer to the element with the highest priority
 * according to the comparison function and restores the
 * heap property.
 * 
 * \param pq The queue.
 * \return A pointer to the front element.
 */
void* prqueue_pop(PrQueue* pq);

/**
 * \brief Replaces the first instance of old_item with new_item
 *
 * Replaces the first instance of old_item with new_item
 * 
 * \param *pq The priority queue
 * \param *new_item The new item
 * \param *old_item The old item
 */
void prqueue_replace(PrQueue *pq, void *old_item, void *new_item);

/**
 * \brief Replaces all instances of old_item with new_item
 *
 *  Replaces all instances of old_item with new_item
 * 
 * \param *pq The priority queue
 * \param *new_item The new item
 * \param *old_item The old item
 */
void prqueue_replace_all(PrQueue *pq, void *old_item, void *new_item);


/**
 * \brief Checks if an item exists in the queue.
 *
 * Checks if an item exists in the queue.
 * 
 * \param *pq The priority queue
 * \param *item The item to look for
 * \return 1 if it is in the queue, 0 otherwise
 */
unsigned int prqueue_contains(PrQueue *pq, void *item);

/**
 * \brief Finds an element with a given specification.
 *
 * Returns a pointer to the first element that appears to be
 * equal to the specified one for further investigation.
 * 
 * \param *pq The priority queue
 * \param *item The item to look for
 * \return Pointer to the first item found.
 */
void* prqueue_get(PrQueue *pq, void *item);

#endif /* end of include guard: PRQUEUE_H_P3USRWA2 */
