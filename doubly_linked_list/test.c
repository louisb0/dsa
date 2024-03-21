#include <assert.h>

#include "test.h"
#include "linked_list.h"


void test_get() {
  LinkedList *linked_list = create_linked_list();
  
  append(linked_list, 1);
  append(linked_list, 2);
  append(linked_list, 3);

  assert(linked_list->len == 3);
  assert(get(linked_list, 0)->value == 1);
  assert(get(linked_list, 1)->value == 2);
  assert(get(linked_list, 2)->value == 3);
 
  free_linked_list(linked_list);
}

void test_find() {
  LinkedList *linked_list = create_linked_list();
  
  append(linked_list, 1);
  append(linked_list, 2);
  append(linked_list, 3);

  assert(linked_list->len == 3);
  assert(find(linked_list, 1)->value == 1);
  assert(find(linked_list, 2)->value == 2);
  assert(find(linked_list, 3)->value == 3);
 
  free_linked_list(linked_list);
}

void test_insert() {
  LinkedList *linked_list = create_linked_list();
  
  insert(linked_list, 1, 0); // head 
  insert(linked_list, 3, 1); // tail 
  insert(linked_list, 2, 1); // inner
  
  assert(linked_list->len == 3);
  assert(get(linked_list, 0)->value == 1);
  assert(get(linked_list, 1)->value == 2);
  assert(get(linked_list, 2)->value == 3);

  free_linked_list(linked_list);
}

void test_delete() {
  LinkedList *linked_list = create_linked_list();

  // setup
  append(linked_list, 1);
  append(linked_list, 2);
  append(linked_list, 3);
  append(linked_list, 4);

  delete_index(linked_list, 1); // inner (2)
  delete_index(linked_list, 0); // head (1)
  delete_index(linked_list, 1); // tail (4)

  assert(linked_list->len == 1);
  assert(get(linked_list, 0)->value == 3);

  free_linked_list(linked_list);
}

void test_all() {
  test_get();
  test_find();
  test_insert();
  test_delete();
}
