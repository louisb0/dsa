#include <stdio.h>

int binary_search(int a[], int l, int r, int value) {
  if (l > r) {
    return -1;
  }

  int mid = l + ((r - l) / 2);
  if (a[mid] == value) {
    return mid;
  } else if (a[mid] < value) {
    return binary_search(a, mid + 1, r, value);
  } else if (a[mid] > value) {
    return binary_search(a, l, mid - 1, value);
  }

  return -1;
}

int main() {
  int a[] = {0, 1, 2, 3, 4, 5, 6, 7};

  printf("%d\n", binary_search(a, 0, 7, 1000));
  printf("%d\n", binary_search(a, 0, 7, 3));

  return 0;
}
