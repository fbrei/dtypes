/**
 *  \file darray.h
 *  \brief Page based dynamicly growing array.
 *
 *  This file contains tools and datatypes to
 *  create and manipulate an array based data
 *  structure that is able to grow as needed.
 *
 *  \date 2018/05/27
 *  \author Felix Brei
 *
 *  \bug No known bugs.
 */

#ifndef DARRAY_H_HVPNU9B1
#define DARRAY_H_HVPNU9B1

#include "include/config.h"

/**
 * \brief Dynamically growing array.
 *
 * This struct manages data and metadata of a dynamic array.
 */
typedef struct _DArray {
  void*** data;       /**< The 2d array that holds the data stored as void pinters. */
  size_t num_pages;   /**< The number of currently used pages. */

  size_t num_items;   /**< The number of items in the array (non-NULL) */
} DArray;


/**
 * \brief Creates a DArray struct.
 *
 * Creates a DArray struct and initializes data array.
 * 
 * \return The initialized DArray
 */
DArray* darray_init();


/**
 * \brief Destroys a DArray
 *
 * Destroys a DArray while taking care of memory allocation.
 * 
 * \param d The DArray that should be destroyed.
 * \param (*destructor)(void*) An optional destructor function. NULL means not to use free
 */
void darray_destroy(DArray* d, void (*destructor)(void*));

/**
 * \brief Inserts an item into the DArray.
 *
 * Inserts an item into the specified DArray.
 * 
 * \param d The Darray.
 * \param item The item
 * \param idx The desired index.
 */
void darray_set(DArray* d, void* item, size_t idx);

/**
 * \brief Gets the item at the desired position.
 *
 * Retrieves an item at a given position, if possible.
 * 
 * \param d The DArray
 * \param idx The desired index.
 * \return The value if exists, or NULL
 */
void* darray_get(DArray* d, size_t idx);

/**
 * \brief Print the whole array.
 *
 * Print the whole array using a user
 * supplied print function.
 * 
 * \param d The DArray
 * \param void (*print_item)(void*)  The print funtion
 */
void darray_print(DArray* d, void (*print_item)(void*));

/**
 * \brief Find the index of an item
 *
 * Searches the list to find the desired item
 * 
 * \param *d The dynamic array
 * \param *item The item to be found
 * \return The index of the item if exists, -1 otherwise
 */
long darray_find(DArray *d, void *item);


/**
 * \brief Iterates over the elements in the array
 *
 * Loops over the element trying to find the first non-NULL
 * element after the specified one.
 * 
 * \param *d The dynamic array to iterate over
 * \param *start_after Tells the function to find the first element after this one.
 * \return The first match, or NULL if nonexistent.
 */
void* darray_iterate(DArray *d, void *start_after);

#endif /* end of include guard: DARRAY_H_HVPNU9B1 */
