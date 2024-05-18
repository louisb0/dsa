#include "graph.h"
#include "linked_list.h"

#include <assert.h>
#include <stdlib.h>

Graph *create_graph(size_t capacity) {
  Graph *g = (Graph *)malloc(sizeof(Graph));
  assert(g != NULL);

  LinkedList **array = (LinkedList **)malloc(sizeof(LinkedList) * capacity);
  assert(array != NULL);

  g->capacity = capacity;
  g->len = 0;
  g->array = array;

  return g;
}

void free_graph(Graph *g) {
  assert(g != NULL);

  for (int i = 0; i < g->len; i++)
    free_linked_list(g->array[i]);

  free(g->array);
  free(g);
}

void add_node(Graph *g) {
  assert(g != NULL);

  LinkedList *list = create_linked_list();

  g->array[g->len] = list;
  g->len++;
}

void delete_node(Graph *g, size_t i) {
  assert(g != NULL);
  assert(i >= 0);
  assert(i < g->len);

  // remove references to i, o(m)
  for (int j = 0; j < g->len; j++) {
    LinkedList *neighbours = g->array[j];
    if (neighbours->len == 0) continue;

    int arc = find_idx(neighbours, i);
    if (arc == -1)
      continue;

    delete_index(neighbours, arc);
  }

  // delete i, shift everything back, o(n)
  free_linked_list(g->array[i]);
  g->array[i] = NULL;

  for (int j = i; j < g->len - 1; j++) {
    g->array[j] = g->array[j + 1];
  }

  g->len--;
}

void add_arc(Graph *g, size_t i, size_t j) {
  assert(g != NULL);
  assert(i >= 0);
  assert(j >= 0);
  assert(i < g->len);
  assert(j < g->len);

  LinkedList *neighbours = g->array[i];
  append(neighbours, j);
}

void delete_arc(Graph *g, size_t i, size_t j) {
  assert(g != NULL);
  assert(i >= 0);
  assert(j >= 0);
  assert(i < g->len);
  assert(j < g->len);

  LinkedList *neighbours = g->array[i];

  // vbad api exposing node
  Node *arc = find(neighbours, j);
  assert(arc != NULL);

  int arc_idx = find_idx(neighbours, j);
  delete_index(neighbours, arc_idx);
}

void graph_print(Graph *g) {
  assert(g != NULL);

  printf("%d\n", (int)g->len);
  for (int i = 0; i < g->len; i++) {
    printf("%d: ", i);
    
    LinkedList *neighbours = g->array[i];
    for (int j = 0; j < neighbours->len; j++) {
      printf("%d ", get(neighbours, j)->value);
    }
    printf("\n");
  }
  printf("------\n");
}

