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


enum GRAPH_PROP {
  GRAPH_DIRECTED,
  GRAPH_UNDIRECTED
};


/**
 * \brief Brief description
 *
 * Long description
 */
typedef struct _Graph {
  DArray* node_list;

  DArray* edges;

  enum GRAPH_PROP is_directed;  /**<< Stores whether the graph is directed. */
} Graph;


/**
 * \brief Initialize an empty graph
 *
 * Creates an empty graph
 * 
 * \param is_directed 1 if graph is directed, 0 if not
 * \return Pointer to a graph object
 */
Graph* graph_init(enum GRAPH_PROP is_directed);

/**
 * \brief Frees all memory allocated by a graph.
 *
 * Frees used memory by a graph while taking care
 * of all used substructues. This also frees all
 * nodes in the graph!
 * 
 * \param g The graph to be destroyed
 * \param (*destructor)(void*) An optional destructor function, pass NULL for default free
 */
void graph_destroy(Graph* g, void (*destructor)(void*));


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

/**
 * \brief Brief description
 *
 * Long description
 * 
 * \param *g 
 * \param *first_node 
 * \param *second_node 
 */
void graph_connect(Graph *g, void *first_node, void *second_node);

/**
 * \brief Brief description
 *
 * Long description
 * 
 * \param *g 
 * \param (print_elem)(void*) 
 */
void graph_print(Graph *g, void (print_elem)(void*));

#endif /* end of include guard: GRAPH_H_YQFBHZUT */
