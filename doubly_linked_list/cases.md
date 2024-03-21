get()
  - list->head DNE: return
  - else: linear iteration from head
find():
  - list->head DNE: return
  - else: linear search from head

 

prepend()
  - list->len == 0: list->head = list->tail = new
  - else:
      new->next = list->head 
      list->head->prev = new 
      list->head = new

append()
  - list->len == 0: list->head = list->tail = new
  - else:
      new->prev = list->tail 
      list->tail->next = new 
      list->tail = new

insert()
  - idx == 0 (head): prepend()
  - idx == len (new tail): append()
  - else: (len>2, inner)
      new->prev = to_replace->prev 
      new->next = to_replace
      
      to_replace->prev->next = new;
      to_replace->prev = new;



delete(idx)
  - list->len == 1:
      list->head = list->tail = NULL
  - list->len == 2:
      to_delete == list->head:
        list->head = list->tail;
      to_delete == list->tail;
        list->tail = list->head;
  - list->len > 2:
      to_delete == list->head:
        list->head = to_delete->next;
        list->head->prev = NULL;
      to_delete == list->tail:
        list->tail = to_delete->prev;
        list->tail->next == NULL
      else: (inner)
        to_delete->prev->next = to_delete->next;
        to_delete->next->prev = to_delete->prev;

^ but that's disgusting so we will simplify it once we see the code

