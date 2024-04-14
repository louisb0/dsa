#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int capacity;
  int length;
  int *data;
} ArrayList;

void handle_failure(char *reason) {
  printf("%s", reason);
  exit(EXIT_FAILURE);
}

ArrayList *create_array_list(int capacity) {
  if (capacity <= 0) {
    handle_failure("create_array_list(): capacity must be positive");
  }

  ArrayList *list = malloc(sizeof(ArrayList));
  if (list == NULL) {
    handle_failure("create_array_list(): failed to malloc struct");
  }

  list->data = malloc(sizeof(int) * capacity);
  if (list->data == NULL) {
    handle_failure("create_array_list(): failed to malloc data");
  }

  list->capacity = capacity;
  list->length = 0;

  return list;
}

void free_array_list(ArrayList *list) {
  free(list->data);

  list->data = NULL;
  list->capacity = 0;
  list->length = 0;

  free(list);
}

void _increase_capacity(ArrayList *list, int new_capacity) {
  if (new_capacity <= list->capacity) {
    return;
  }

  int *new_data = malloc(sizeof(int) * new_capacity);
  memcpy(new_data, list->data, sizeof(int) * list->length);
  free(list->data);

  list->data = new_data;
  list->capacity = new_capacity;
}

int get(ArrayList *list, int index) { return list->data[index]; }

void insert(ArrayList *list, int index, int value) {
  if (index < 0 || index > list->length) {
    handle_failure("insert(): out-of-bounds index");
  }

  if (list->length == list->capacity) {
    _increase_capacity(list, list->capacity * 2);
  }

  for (int i = list->length; i > index; i--) {
    list->data[i] = list->data[i - 1];
  }

  list->data[index] = value;
  list->length += 1;
}

void push(ArrayList *list, int value) {
  if (list->length == list->capacity) {
    _increase_capacity(list, list->capacity * 2);
  }

  list->data[list->length] = value;
  list->length += 1;
}

int pop(ArrayList *list) {
  list->length -= 1;

  return list->data[list->length];
}

void enqueue(ArrayList *list, int value) { insert(list, 0, value); }

void dequeue(ArrayList *list) { pop(list); }

void print_list(ArrayList *list) {
  for (int i = 0; i < list->length; i++) {
    printf("%d ", get(list, i));
  }
  printf("\n");
}

int main() {
  ArrayList *list = create_array_list(1);

  push(list, 1);
  push(list, 2);
  push(list, 3);
  print_list(list);

  insert(list, 1, 9);
  print_list(list);

  printf("popped %d\n", pop(list));
  print_list(list);

  enqueue(list, 5);
  printf("queued 5\n");
  print_list(list);

  dequeue(list);
  printf("dequeued\n");
  print_list(list);

  free_array_list(list);
  return 0;
}
