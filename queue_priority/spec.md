priority queue is a heap

can store the tree structure in an array, though this means fixed-size, so resizing will be needed similar to what was done in the array list

```
[Node(data, priotity), ... ]
```

where we can access child nodes with `2i+1` or `2i+2`, or parent with `floor(i-1)/2`

so need some kind of encapsulation of our data and a priority. let's say we store ints. 

```c
typedef struct {
    int priority;
    int data;
} Item;
```

a PQ has two operations: queue, dequeue, and peek. queuing is essentially inserting into a max-heap. dequeuing is popping from a max-heap. peeking is just accessing the root.

dequeuing: we swap the root with the last node/leaf, then sink that last leaf down by swapping it with the max of its two children. this gives us operation one: `percolate_down`. 

enqueuing: put the node at the end, and percolate it up by swapping it with its parent continually until it is less than its parent. `percolate_up`

what about elements of duplicate priority? i thought i remembered reading that was no good but apparently is fine. do we want to respect something like insertion order when queuing multiple items of the same priority? probably. is that default behaviour? i don't think it would be - heapsort for example is not a stable sorting algorithm which works extremely similar to this. so, we need to add some logic to do this.

add like an insertion stamp which is just a global order. an element is greater if the insertion stamp is less and the priority is more.

cool now need to think about our two fundamental ops here 

```
fn percolate_down(heap, item):
    max_child = get_max_child()
    
    if max_child > item 
        swap(max_child, item)
        percolate_down(heap, item)
```

 looking overly simplified and ready to miss all possible edge cases and deal with it later

now this one 

```
fn percolate_up(heap, item):
    parent = get_parent()

    if item > parent: 
        swap(parent, item)
        percolate_up(heap, item)
```







