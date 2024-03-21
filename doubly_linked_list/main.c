#include "test.h"

#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  test_all();
  printf("All tests passed.\n");
  // LinkedList *list = create_linked_list();
  //
  // prepend(list, 1);
  // append(list, 3);
  //
  // printf("head: %d\n", list->head->value);
  // printf("tail: %d\n", list->tail->value);
  // printf("len: %d\n", (int)list->len);
  //
  // insert(list, 2, 1);
  //
  // for(int i = 0; i < list->len; i++) {
  //   printf("%d\n", get(list, i)->value);
  // } 
  //
  // free_linked_list(list);
  //
  return 0;
}
