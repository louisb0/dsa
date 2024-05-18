#ifndef GRAPH_H
#define GRAPH_H

#include "linked_list.h"

typedef struct {
  size_t capacity;
  size_t len;
  LinkedList **array;
} Graph;

Graph *create_graph(size_t capacity);
void free_graph(Graph *g);

void add_node(Graph *g);
void delete_node(Graph *g, size_t i);

void add_arc(Graph *g, size_t i, size_t j);
void delete_arc(Graph *g, size_t i, size_t j);

void graph_print(Graph *g);

#endif
