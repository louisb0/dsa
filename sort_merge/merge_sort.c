#include <stdio.h>

void merge(int a[], int l, int mid, int r) {
  int left_size = (mid - l) + 1;
  int left[left_size];
  for (int i = 0; i < left_size; i++) {
    left[i] = a[l + i];
  }

  int right_size = r - mid;
  int right[right_size];
  for (int j = 0; j < right_size; j++) {
    right[j] = a[(mid + 1) + j];
  }

  int i = 0;
  int j = 0;
  int k = l;
  while (i < left_size && j < right_size) {
    if (left[i] < right[j]) {
      a[k] = left[i];
      i++;
    } else {
      a[k] = right[j];
      j++;
    }
    k++;
  }

  while (i < left_size) {
    a[k] = left[i];
    i++;
    k++;
  }

  while (j < right_size) {
    a[k] = right[j];
    j++;
    k++;
  }
}

void merge_sort(int a[], int l, int r) {
  if (l >= r) {
    return;
  }

  int mid = l + (r - l) / 2;
  merge_sort(a, l, mid);
  merge_sort(a, mid + 1, r);

  merge(a, l, mid, r);
}

void print_array(int arr[], int size) {
  for (int i = 0; i < size; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

int main() {
    int a[] = {};
    int b[] = {1, 2, 3, 4, 5};
    int c[] = {5, 4, 3, 2, 1, 0};
    int d[] = {1, 1, 1, 1, 1, 1};
    int e[] = {1, -1, 1, -1, 1, -1};

    int len_a = sizeof(a) / sizeof(a[0]);
    int len_b = sizeof(b) / sizeof(b[0]);
    int len_c = sizeof(c) / sizeof(c[0]);
    int len_d = sizeof(d) / sizeof(d[0]);
    int len_e = sizeof(e) / sizeof(e[0]);

    merge_sort(a, 0, len_a - 1);
    print_array(a, len_a);

    merge_sort(b, 0, len_b - 1);
    print_array(b, len_b);

    merge_sort(c, 0, len_c - 1);
    print_array(c, len_c);

    merge_sort(d, 0, len_d - 1);
    print_array(d, len_d);

    merge_sort(e, 0, len_e - 1);
    print_array(e, len_e);

    return 0;
}

