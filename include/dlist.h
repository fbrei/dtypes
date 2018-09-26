/**
 *	\file dlist.h
 *  \brief Dynamically growing list that allows appending and removing.
 *
 *	Mostly used for simple collections of objects where order does not matter
 *	and that are mostly read only.
 *
 *	\date 2018/09/12
 *	\author Felix Brei
 *
 *	\bug No known bugs.
 */

#ifndef DLIST_H_9UYFSIDA
#define DLIST_H_9UYFSIDA

#include "include/dtype.h"

/**
 * \brief Struct that holds a simple list for data storing
 *
 * Actually just a simple wrapper around DArray if the user
 * just cares about items being present and not about any
 * kind of ordering or fancy manipulations.
 */
typedef struct _DList {
  DArray *data; 		/**< description */
  size_t num_items; 		/**< description */
} DList;

/**
 * \brief Initializes an empty DList
 *
 * Initializes an empty list and sets initial values.
 * 
 * \return An empty DList
 */
DList* dlist_init();

/**
 * \brief Destroy a DList
 *
 * Frees all memory occupied by a DList
 * 
 * \param *list The list to be destroyed
 * \param (*destructor)(void*) Optional destructor, can be NULL
 */
void dlist_destroy(DList *list, void (*destructor)(void*));

/**
 * \brief Adds an item to the list
 *
 * The item will be added at the end of the list
 * 
 * \param *list The list that will hold the item
 * \param *item The actual item
 */
void dlist_push(DList *list, void *item);

/**
 * \brief Removes an item from the list
 *
 * Removes the specified item from the list if present
 * 
 * \param *list The list to delete from
 * \param *item The item to be deleted
 */
void dlist_remove(DList *list, void *item);

/**
 * \brief Iterates over the elements in a DList
 *
 * Loops over the element trying to find the first non-NULL
 * element after the specified one.
 * 
 * \param *d The DList to iterate over
 * \param *start_after Tells the function to find the first element after this one.
 * \return The first match, or NULL if nonexistent.
 */
void* dlist_iterate(DList *list, void *start_after);

#endif /* end of include guard: DLIST_H_9UYFSIDA */
