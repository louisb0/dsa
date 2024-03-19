#include "bubble_sort.h"
#include <stdio.h>

void swap(int array[], int i, int j) {
  int temp = array[i];

  array[i] = array[j];
  array[j] = temp;
}

void bubble_sort(int array[], int len) {
  for (int i = 0; i < len; i++) {
    for (int j = 0; j < len - i - 1; j++) {
      if (array[j] > array[j + 1]) {
        swap(array, j, j + 1);
      }
    }
  }
}

int main() {
  int array[] = {6, 1, 2, 5, 3};
  int len = 5;

  bubble_sort(array, len);

  for (int i = 0; i < len; i++) {
    printf("%d", array[i]);
  }
}
