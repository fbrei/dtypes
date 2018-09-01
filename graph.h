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
 * Defines allowed properties for a graph
 */
enum GRAPH_PROP {
  GRAPH_DIRECTED,   /**< Means that the graph should be treated as a directed graph. */
  GRAPH_UNDIRECTED  /**< The graph is undirected, meaning edges can be traversed both ways. */
};


/**
 * \brief Holds data relevant to describe a graph structure.
 *
 * Stores edges and vertices and some properties that make up
 * a graph data structure.
 */
typedef struct _Graph {
  DArray* node_list;            /**<< A dynamic array holding the nodes of the graph */
  DArray* edges;                /**<< Connectivity matrix implemented as 2D dynamic array */

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
 * \brief Connect to nodes in a graph and assign a weight.
 *
 * Works by adding the weight of the edge to the connectivity matrix
 * where the row index corresponds to the index of the first node
 * in the node list and the coloumn index accordingly for the
 * second node.
 * 
 * \param *g The graph that holds the nodes
 * \param *first_node  The first node (origin)
 * \param *second_node The second node (source)
 * \param edge_weight  The weight of the edge.
 */
void graph_connect(Graph *g, void *first_node, void *second_node, double edge_weight);

/**
 * \brief Gets the weight between two edges if exists
 *
 * Looks up the weight and returns a double pointer that
 * dereferences to the weight or NULL if there is no edge
 * 
 * \param *g 
 * \param *first_node  The first node (origin)
 * \param *second_node The second node (source)
 * \return Pointer to the edge weight, NULL if there is no edge
 */
double* graph_get_edge_weight(Graph *g, void *first_node, void *second_node);

/**
 * \brief Prints a strongly simplified version of the graph 
 *
 * Iterates over all nodes and prints them along with their direct
 * successors and the edge weights between them
 * 
 * \param *g The graph
 * \param (print_elem)(void*) Function that prints the node
 */
void graph_print(Graph *g, void (print_elem)(void*));

#endif /* end of include guard: GRAPH_H_YQFBHZUT */
