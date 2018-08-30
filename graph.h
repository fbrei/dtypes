/**
 *	\file graph.h
 *  \brief File header for graph data type
 *
 *	Contains declarations of methods to initialize,
 *	use and destroy a graph data structure
 *
 *	\date 2018/08/30
 *	\author Felix Brei
 *
 *	\bug No known bugs.
 */

#ifndef GRAPH_H_YQFBHZUT
#define GRAPH_H_YQFBHZUT

#include "darray.h"

/**
 * \brief Brief description
 *
 * Long description
 */
typedef struct _Graph {
  DArray* node_list;
  size_t num_nodes;

  unsigned short is_directed;  /**<< Stores whether the graph is directed. */
} Graph;


/**
 * \brief Initialize an empty graph
 *
 * Creates an empty graph
 * 
 * \param is_directed 1 if graph is directed, 0 if not
 * \return Pointer to a graph object
 */
Graph* graph_init(unsigned short is_directed);

/**
 * \brief Frees all memory allocated by a graph.
 *
 * Frees used memory by a graph while taking care
 * of all used substructues. This also frees all
 * nodes in the graph!
 * 
 * \param g The graph to be destroyed
 */
void graph_destroy(Graph* g);


/**
 * \brief Add a node to a graph
 *
 * Inserts a node into a graph's node
 * list without any connections yet.
 * 
 * \param *g The graph
 * \param *node The node
 */
void graph_add(Graph *g, void *node);

#endif /* end of include guard: GRAPH_H_YQFBHZUT */
