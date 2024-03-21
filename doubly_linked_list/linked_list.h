#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>

typedef struct Node {
  struct Node *next;
  struct Node *prev;

  int value;
} Node;

typedef struct {
  Node *head;
  Node *tail;

  size_t len;
} LinkedList;

LinkedList *create_linked_list();
void free_linked_list(LinkedList *list);

Node *create_node(int value);
void free_node(Node *node);

Node *get(LinkedList *list, int index);
Node *find(LinkedList *list, int value);

void prepend(LinkedList *list, int value);
void append(LinkedList *list, int value);
void insert(LinkedList *list, int value, int index);

void delete_index(LinkedList *list, int index);
// void delete_value(LinkedList *list, int value);

#endif // LINKED_LIST_H
