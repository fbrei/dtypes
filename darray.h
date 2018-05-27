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

#include "config.h"

/**
 * \brief Dynamically growing array.
 *
 * This struct manages data and metadata of a dynamic array.
 */
typedef struct _DArray {
  void** data;        /**< The 2d array that holds the data stored as void pinters. */
  size_t num_pages;   /**< The number of currently used pages. */
} DArray;


/**
 * \brief Creates a DArray struct.
 *
 * Creates a DArray struct and initializes data array.
 * 
 * \return The initialized DArray
 */
DArray darray_init();


/**
 * \brief Destroys a DArray
 *
 * Destroys a DArray while taking care of memory allocation.
 * 
 * \param d The DArray that should be destroyed.
 */
void darray_destroy(DArray* d);

#endif /* end of include guard: DARRAY_H_HVPNU9B1 */
