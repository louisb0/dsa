#ifndef ARRAY_H
#define ARRAY_H

#include <stdlib.h>

typedef struct {
  size_t el_size;
  size_t length;

  int *data;
} IntArray;

IntArray *create_array(int length);
void free_array(IntArray *array);

int get(IntArray *array, int index);
void set(IntArray *array, int index, int value);

void print_array(IntArray *array);

#endif // ARRAY_H
