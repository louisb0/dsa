#include <stdio.h>

void swap(int arr[], int i, int j) {
  int tmp = arr[i];

  arr[i] = arr[j];
  arr[j] = tmp;
}

int partition(int arr[], int l, int r) {
  int pivot_idx = l + (r - l) / 2;
  int pivot_val = arr[pivot_idx];

  swap(arr, pivot_idx, r);

  int store_idx = l; // exclusive index of lesser segment
  for (int i = l; i < r; i++) {
    if (arr[i] < pivot_val) {
      swap(arr, i, store_idx);
      store_idx++;
    }
  }

  // put the pivot at the end of the lesser segment
  // i.e. in the middle
  swap(arr, store_idx, r);

  return store_idx;
}

void qsort(int arr[], int l, int r) {
  if (l >= r) {
    return;
  }

  int pivot_idx = partition(arr, l, r);
  qsort(arr, l, pivot_idx - 1);
  qsort(arr, pivot_idx + 1, r);
}

void sort(int arr[], int len) { qsort(arr, 0, len - 1); }

int main() {
  int arr[] = {5, 3, 6, 4, 7};
  int len = sizeof(arr) / sizeof(arr[0]);

  sort(arr, len);

  for (int i = 0; i < len; i++) {
    printf("%d ", arr[i]);
  }
}
