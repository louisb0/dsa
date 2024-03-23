#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void handle_failure(char *reason) {
  printf("%s", reason);
  exit(EXIT_FAILURE);
}

typedef struct Node {
  struct Node *next;
  void *data;
} Node;

typedef struct {
  Node *head;
} Stack;

Stack *create_stack() {
  Stack *stack = malloc(sizeof(Stack));
  if (stack == NULL) {
    handle_failure("create_stack(): failed to malloc");
  }

  stack->head = NULL;
  return stack;
}

void free_stack(Stack *stack) {
  Node *current = stack->head;
  while (current) {
    Node *tmp = current;
    current = current->next;
    free(tmp);
  }

  stack->head = NULL;
  free(stack);
}

Node *create_node(void *data) {
  Node *node = malloc(sizeof(Node));
  if (node == NULL) {
    handle_failure("create_node(): failed to malloc");
  }

  node->data = data;
  return node;
}

void push(Stack *stack, void *data) {
  Node *to_push = create_node(data);

  to_push->next = stack->head;
  stack->head = to_push;
}

void *pop(Stack *stack) {
  if (stack->head == NULL) {
    return NULL;
  }

  Node *old_head = stack->head;
  void *data = old_head->data;

  stack->head = stack->head->next;

  free(old_head);
  return data;
}

void *peak(Stack *stack) { return stack->head->data; }

int main() {
  int a = 1;
  int b = 2;
  int c = 3;

  Stack *stack = create_stack();

  push(stack, &a);
  push(stack, &b);
  push(stack, &c);

  assert(*(int *)peak(stack) == 3);

  assert(*(int *)pop(stack) == 3);
  assert(*(int *)pop(stack) == 2);
  assert(*(int *)pop(stack) == 1);

  assert(pop(stack) == NULL);

  free_stack(stack);

  printf("All tests passed.\n");
}
