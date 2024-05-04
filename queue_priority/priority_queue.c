#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int priority;
  int insertion_stamp;

  int value;
} PQ_Item;

typedef struct {
  int num_insertions;

  size_t capacity;
  size_t length;
  PQ_Item *items;
} PQ;

void handle_failure(char *reason) {
  printf("%s\n", reason);
  exit(EXIT_FAILURE);
}

PQ *pq_create(size_t capacity) {
  PQ *pq = (PQ *)malloc(sizeof(PQ));
  if (pq == NULL) {
    handle_failure("failed to malloc pq in pq_create()");
  }

  PQ_Item *items = (PQ_Item *)malloc(sizeof(PQ_Item) * capacity);
  if (items == NULL) {
    handle_failure("failed to malloc items in pq_create()");
  }

  pq->num_insertions = 0;
  pq->capacity = capacity;
  pq->length = 0;
  pq->items = items;

  return pq;
}

void pq_free(PQ *pq) {
  free(pq->items);
  free(pq);
}

void _pq_swap(PQ *pq, int i, int j) {
  PQ_Item tmp = pq->items[i];

  pq->items[i] = pq->items[j];
  pq->items[j] = tmp;
}

int _pq_item_cmp(const PQ_Item *a, const PQ_Item *b) {
  if (a->priority > b->priority) {
    return 1;
  } else if (a->priority < b->priority) {
    return -1;
  }

  if (a->insertion_stamp < b->insertion_stamp) {
    return 1;
  } else if (a->insertion_stamp > b->insertion_stamp) {
    return -1;
  }

  // cannot be hit as insertion_stamp increments
  return 0;
}

void _pq_percolate_up(PQ *pq, int pq_item_idx) {
  if (pq_item_idx == 0) {
    return;
  }

  int parent_idx = (pq_item_idx - 1) / 2;

  PQ_Item *parent = &pq->items[parent_idx];
  PQ_Item *item = &pq->items[pq_item_idx];

  if (_pq_item_cmp(parent, item) == -1) {
    _pq_swap(pq, pq_item_idx, parent_idx);
    _pq_percolate_up(pq, parent_idx);
  }
}

void _pq_percolate_down(PQ *pq, int pq_item_idx) {
  int left_child_idx = 2 * pq_item_idx + 1;
  int right_child_idx = 2 * pq_item_idx + 2;

  int max_child_idx = pq_item_idx;
  PQ_Item *max_child = &pq->items[max_child_idx];

  if (left_child_idx < pq->length &&
      _pq_item_cmp(&pq->items[left_child_idx], max_child) == 1) {
    max_child_idx = left_child_idx;
    max_child = &pq->items[left_child_idx];
  }

  if (right_child_idx < pq->length &&
      _pq_item_cmp(&pq->items[right_child_idx], max_child) == 1) {
    max_child_idx = right_child_idx;
    max_child = &pq->items[right_child_idx];
  }

  if (max_child_idx != pq_item_idx) {
    _pq_swap(pq, max_child_idx, pq_item_idx);
    _pq_percolate_down(pq, max_child_idx);
  }
}

void pq_queue(PQ *pq, int data, int priority) {
  if (pq->length == pq->capacity) {
    handle_failure("called pq_queue() at max capacity");
    return;
  }

  pq->num_insertions++;

  PQ_Item item;
  item.insertion_stamp = pq->num_insertions;
  item.priority = priority;
  item.value = data;

  pq->items[pq->length] = item;
  _pq_percolate_up(pq, pq->length);

  pq->length++;
}

int pq_dequeue(PQ *pq) {
  if (pq->length == 0) {
    return -999;
  }

  _pq_swap(pq, 0, pq->length - 1);

  pq->length--;
  _pq_percolate_down(pq, 0);

  return pq->items[pq->length].value;
}

int pq_peek(PQ *pq) {
  if (pq->length == 0) {
    return -999;
  }

  return pq->items[0].value;
}

void pq_print(PQ *pq) {
  for (int i = 0; i < pq->length; i++) {
    printf("(v=%d, p=%d), ", pq->items[i].value, pq->items[i].priority);
  }
  printf("\n");
}

int main() {
  PQ *pq = pq_create(10);

  // Test FIFO across equal priorities
  pq_queue(pq, 1, 0);
  pq_queue(pq, 2, 0);
  pq_queue(pq, 3, 0);
  pq_queue(pq, 4, 0);
  assert(pq_dequeue(pq) == 1); 
  assert(pq_dequeue(pq) == 2);
  assert(pq_dequeue(pq) == 3);
  assert(pq_dequeue(pq) == 4);

  // Test general priority
  pq_queue(pq, 4, 7);
  pq_queue(pq, 1, 10);
  pq_queue(pq, 3, 8);
  pq_queue(pq, 2, 9);
  assert(pq_dequeue(pq) == 1); 
  assert(pq_dequeue(pq) == 2);
  assert(pq_dequeue(pq) == 3);
  assert(pq_dequeue(pq) == 4);

  // Test interleaved equal priority
  pq_queue(pq, 1, 10);
  pq_queue(pq, 3, 9);
  pq_queue(pq, 2, 10);
  pq_queue(pq, 4, 8);
  assert(pq_dequeue(pq) == 1); 
  assert(pq_dequeue(pq) == 2);
  assert(pq_dequeue(pq) == 3);
  assert(pq_dequeue(pq) == 4);

  printf("All test cases passed!\n");
  pq_free(pq);
}
