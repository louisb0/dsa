#include <stdlib.h>

#include "linked_list.h"

void handle_failure(char *reason) {
  printf("%s", reason);
  exit(EXIT_FAILURE);
}

LinkedList *create_linked_list() {
  LinkedList *list = malloc(sizeof(LinkedList));
  if (list == NULL) {
    handle_failure("Failed to create list.");
    return NULL;
  }

  list->head = list->tail = NULL;
  list->len = 0;
  return list;
}

void free_linked_list(LinkedList *list) {
  Node *target = list->head;
  while (target != NULL) {
    Node *to_delete = target;
    target = target->next;

    free_node(to_delete);
  }

  free(list);
}

Node *create_node(int value) {
  Node *node = malloc(sizeof(Node));
  if (node == NULL) {
    handle_failure("Failed to create node.");
    return NULL;
  }

  node->next = node->prev = NULL;
  node->value = value;
  return node;
}

void free_node(Node *node) { free(node); }

Node *get(LinkedList *list, int index) {
  if (list->head == NULL) {
    handle_failure("get(): list is empty.");
    return NULL;
  }

  if (index >= list->len || index < 0) {
    handle_failure("get(): invalid index.");
    return NULL;
  }

  Node *to_return = list->head;
  for (int i = 0; i < index; i++) {
    to_return = to_return->next;
  }

  return to_return;
}

Node *find(LinkedList *list, int value) {
  if (list->head == NULL) {
    handle_failure("find(): list is empty.");
    return NULL;
  }

  Node *target = list->head;
  while (target != NULL) {
    if (target->value == value) {
      return target;
    }

    target = target->next;
  }

  return NULL;
}

int find_idx(LinkedList *list, int value) {
  if (list->head == NULL) {
    handle_failure("find(): list is empty.");
    return -1;
  }

  int i = 0;
  Node *target = list->head;
  while (target != NULL) {
    if (target->value == value) {
      return i;
    }

    target = target->next;
    i += 1;
  }

  return -1;
}

void prepend(LinkedList *list, int value) {
  Node *to_insert = create_node(value);

  if (list->len == 0) {
    list->head = list->tail = to_insert;
  } else {
    to_insert->next = list->head;

    list->head->prev = to_insert;
    list->head = to_insert;
  }

  list->len += 1;
}

void append(LinkedList *list, int value) {
  Node *to_insert = create_node(value);

  if (list->len == 0) {
    list->head = list->tail = to_insert;
  } else {
    to_insert->prev = list->tail;

    list->tail->next = to_insert;
    list->tail = to_insert;
  }

  list->len += 1;
}

void insert(LinkedList *list, int value, int index) {
  if (index < 0 || index > list->len) {
    handle_failure("insert(): out-of-bounds index.");
    return;
  }

  if (index == 0) {
    prepend(list, value);
    return;
  }
  if (index == list->len) {
    append(list, value);
    return;
  }

  Node *to_insert = create_node(value);
  Node *to_replace = get(list, index);

  to_insert->prev = to_replace->prev;
  to_insert->next = to_replace;

  to_replace->prev->next = to_insert;
  to_replace->prev = to_insert;

  list->len += 1;
}

void delete_index(LinkedList *list, int index) {
  if (list->len == 0) {
    handle_failure("delete(): list is empty.");
    return;
  }

  if (index < 0 || index >= list->len) {
    handle_failure("delete(): out-of-bounds index.");
    return;
  }

  Node *to_delete = get(list, index);

  if (to_delete->prev) {
    to_delete->prev->next = to_delete->next;
  } else {
    list->head = to_delete->next;
  }

  if (to_delete->next) {
    to_delete->next->prev = to_delete->prev;
  } else {
    list->tail = to_delete->prev;
  }

  free_node(to_delete);
  list->len -= 1;
}
