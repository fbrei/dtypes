/**
 *	\file darray.h
 *  \brief Page based dynamicly growing array.
 *
 *	This file contains tools and datatypes to
 *	create and manipulate an array based data
 *	structure that is able to grow as needed.
 *
 *	\date 2018/05/27
 *	\author Felix Brei
 *
 *	\bug No known bugs.
 */

#ifndef DARRAY_H_HVPNU9B1
#define DARRAY_H_HVPNU9B1

const size_t PAGE_SIZE = 8;

/**
 * \brief Dynamically growing array.
 *
 * This struct manages data and metadata of a dynamic array.
 */
typedef struct _DArray {
  void** data; 		    /**< The 2d array that holds the data stored as void pinters. */
  size_t num_pages; 	/**< The number of currently used pages. */
} DArray;

#endif /* end of include guard: DARRAY_H_HVPNU9B1 */
