#include <stdio.h>
#include <stdlib.h>

#include "array.h"

void handle_failure(char *message) {
  printf("%s", message);
  exit(EXIT_FAILURE);
}

IntArray *create_array(int length) {
  IntArray *array = malloc(sizeof(IntArray));
  if (array == NULL) {
    handle_failure("Failed to allocate memory.");
  }

  array->el_size = sizeof(int);
  array->length = length;

  array->data = malloc(array->length * array->el_size);
  if (array->data == NULL) {
    free(array);
    handle_failure("Failed to allocate memory.");
  }

  return array;
}

void free_array(IntArray *array) {
  free(array->data);
  free(array);
}

int get(IntArray *array, int index) {
  if (index < 0 || index >= array->length) {
    handle_failure("Out of bounds index for get().");
  }

  return *(array->data + index);
}

void set(IntArray *array, int index, int value) {
  if (index < 0 || index >= array->length) {
    handle_failure("Out of bounds index for set().");
  }

  *(array->data + index) = value;
}

void print_array(IntArray *array) {
  printf("[");
  for (int i = 0; i < array->length; i++) {
    if (i == (array->length - 1)) {
      printf("%d", get(array, i));
    } else {
      printf("%d, ", get(array, i));
    }
  }
  printf("]\n");
}

int main() {
  IntArray *array = create_array(10);

  for (int i = 0; i < 10; i++) {
    set(array, i, i + 1);
  }
  print_array(array);

  free_array(array);
}
