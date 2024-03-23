array list
  - capacity
  - length

.get(): constant time indexing of underlying array
.insert():
  - if need increase: increase 
  - shift all to right of index (inclusive of)
  - write at index

.push():
  - if need increase: increase 
  - add to end 
  - increase length 

.pop()
  - decrease length
  - return the old value

.enqueue()
  - insert() at idx 0

.dequeue()
  - shift all to left 

