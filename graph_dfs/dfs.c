#include "graph.h"

void _dfs_visit(Graph *g, int n, int *time, int pred[], int seen[], int done[], int colour[]) {
  colour[n] = 1;
  seen[n] = (*time)++;
  
  Node *w = g->array[n]->head;
  while (w) {
    if (colour[w->value] == 0) {
      pred[w->value] = n;
      _dfs_visit(g, w->value, time, pred, seen, done, colour);
    }

    w = w->next;
  }

  colour[n] = 2;
  done[n] = (*time)++;
}

void dfs(Graph *g, int pred[], int seen[], int done[]) {
  int time = 0;
  int colour[g->len];
  for (int i = 0; i < g->len; i++) {
    colour[i] = 0;
    pred[i] = seen[i] = done[i] = -1;
  }

  for (int i = 0; i < g->len; i++) {
    if (colour[i] == 0) {
      _dfs_visit(g, i, &time, pred, seen, done, colour);
    }
  }
}

int main() { 
  Graph *g = create_graph(5);

  for (int i = 0; i < 5; i++) add_node(g);

  add_arc(g, 0, 1);
  add_arc(g, 0, 3);
  add_arc(g, 1, 2);
  add_arc(g, 1, 3);
  add_arc(g, 2, 1);
  add_arc(g, 3, 4);
  add_arc(g, 4, 2);
  graph_print(g);

  int seen[5], done[5], pred[5];
  dfs(g, pred, seen, done);

  printf("seen: ");
  for (int i = 0; i < 5; i++) {
    printf("%d ", seen[i]);
  }
  printf("\n");

  printf("done: ");
  for (int i = 0; i < 5; i++) {
    printf("%d ", done[i]);
  }
  printf("\n");

  free_graph(g);
}
