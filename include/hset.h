/**
 *  \file hset.h
 *  \brief Hashset with DArray backend
 *
 *  A growing hashset using the DArray struct as backend.
 *
 *  \date 2018/05/27
 *  \author Felix Brei
 *
 *  \bug No known bugs.
 */

#ifndef SET_H_OHIG380N
#define SET_H_OHIG380N

#include "darray.h"

/**
 * \brief The Hashset struct
 *
 * The struct that holds the data together with a hash function.
 */
typedef struct _HSet {
  DArray* data;                           /**< The actual data */
  unsigned long (*hash)(void*);           /**< Calculates the hash of an item */
  unsigned int (*equals)(void*,void*);    /**< Checks whether two items are actually equal (should check for NULL) */
  void* marker;                           /**< Special value that marks entries as deleted. */
  size_t num_items;                       /**< Number of items currently inside. */
  size_t max_items;                       /**< Maximum number of slots available (grows dynamically) */
} HSet;

/**
 * \brief Creates a hash set
 *
 * Creates and initializes a hash set
 * 
 * \param (*hash)(void*) The hash function
 * \param (*equals)(void*,void*) The equals function
 * \return A ready to use hash set
 */
HSet* hset_init(unsigned long (*hash)(void*), unsigned int (*equals)(void*,void*));

/**
 * \brief Destroys a hash set
 *
 * Destroy a given hash set completely.
 * 
 * \param h The hashset
 * \param (*destructor)(void*) An optional destructor function. NULL means not to use free
 */
void hset_destroy(HSet* h, void (*destructor)(void*));

/**
 * \brief Adds an item to a hash set.
 *
 * Adds the given item to the has hset
 * 
 * \param h The hash set
 * \param item The item
 */
void hset_add(HSet* h, void* item);

/**
 * \brief Delete an item from a hash set
 *
 * Deletes the first item that matches the
 * supplied one
 * 
 * \param h The hash set
 * \param item The item
 */
void hset_remove(HSet* h, void* item);

/**
 * \brief Checks if a hash set contains a certain item.
 *
 * Checks if a hash set contains a certain item.
 * 
 * \param *h The hash set
 * \param *item The item
 * \return The index of the item, -1 if not found.
 */
long hset_contains(HSet *h, void *item);

/**
 * \brief Prints the contents of the set in a neat fashion.
 *
 * Prints the contents of the set in a neat fashion.
 * 
 * \param *h The set
 * \param (*print_elem)(void*) The print function for one element.
 */
void hset_print(HSet *h, void (*print_elem)(void*));


/**
 * \brief Apply a function to all elements.
 *
 * Takes a function and applies it to every
 * single element in the set.
 * 
 * \param *h The set
 * \param (*f)(void*) The function
 */
void hset_apply(HSet *h, void (*f)(void*));

#endif /* end of include guard: SET_H_OHIG380N */
