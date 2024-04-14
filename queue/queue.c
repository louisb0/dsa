#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  struct Node *next;
  void *data;
} Node;

typedef struct {
  Node *head; // front
  Node *tail; // back

  int len;
} Queue;

void handle_failure(char *reason) {
  printf("%s\n", reason);
  exit(EXIT_FAILURE);
}

Queue *create_queue() {
  Queue *queue = malloc(sizeof(Queue));
  if (queue == NULL) {
    handle_failure("create_queue(): failed to malloc");
    return NULL;
  }

  queue->head = queue->tail = NULL;
  queue->len = 0;

  return queue;
}

void free_queue(Queue* queue) {
  if (queue == NULL) {
    return;
  }

  Node *current = queue->head;
  while (current != NULL) {
    Node *tmp = current;
    current = current->next;

    free(tmp);
  }

  queue->head = queue->tail = NULL;
  queue->len = 0;
  free(queue);
}

Node *create_node(void *data) {
  Node *node = malloc(sizeof(Node)); 
  if (node == NULL) {
    handle_failure("create_node(): failed to malloc");
    return NULL;
  }

  node->next = NULL;
  node->data = data;
  return node;
}

void enqueue(Queue *queue, void *data) {
  if (queue == NULL) {
    handle_failure("enqueue(): queue is null");
    return;
  }

  Node *to_queue = create_node(data);

  if (queue->len == 0) {
    queue->head = queue->tail = to_queue;
  } else {
    queue->tail->next = to_queue;
    queue->tail = to_queue;
  }

  queue->len += 1;
}

void *dequeue(Queue *queue) {
  if (queue == NULL) {
    handle_failure("enqueue(): queue is null");
    return NULL;
  }

  if (queue->head == NULL) {
    return NULL;
  }

  Node *to_dequeue = queue->head;
  void *to_return = to_dequeue->data;

  queue->head = to_dequeue->next;
  if (queue->head == NULL) {
    queue->tail = NULL;
  }

  queue->len -= 1;
  free(to_dequeue);

  return to_return;
}

void *peak(Queue *queue) {
  if (queue->head == NULL) { return NULL; }
  return queue->head->data;
}

int main() { 
  int a = 1;
  int b = 2;
  int c = 3;

  Queue *q = create_queue();

  enqueue(q, &a);
  enqueue(q, &b);
  enqueue(q, &c);

  assert(*(int *)peak(q) == 1);

  assert(*(int *)dequeue(q) == 1);
  assert(*(int *)dequeue(q) == 2);
  assert(*(int *)dequeue(q) == 3);

  assert(peak(q) == NULL);
  assert(dequeue(q) == NULL);

  free_queue(q);
}
