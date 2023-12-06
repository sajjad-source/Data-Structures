## Set

A `set` is an unordered collection of _key-item_ pairs.
The `set` starts empty and allows the caller to add _key-item_ pairs one at a time and retrieve _items_ by their associated _keys_.
Each _key_ in the set must be unique; attempting to insert a duplicate key will not change the set.

### Usage

The *set* module, defined in `set.h` and implemented in `set.c`, implements a set of `key-item pairs`, and exports the following functions:

```c
set_t* set_new(void);
bool set_insert(set_t* set, const char* key, void* item);
void* set_find(set_t* set, const char* key);
void set_print(set_t* set, FILE* fp, void (*itemprint)(FILE* fp, const char* key, void* item));
void set_iterate(set_t* set, void* arg, void (*itemfunc)(void* arg, const char* key, void* item));
void set_delete(set_t* set, void (*itemdelete)(void* item));
```

### Implementation

We implement this set as a linked list of key-item pairs.
The *set* itself is represented as a `struct set` containing a pointer to the head of the list; the head pointer is NULL when the set is empty.

Each node in the list is a `struct setnode`, a type defined internally to the module.
Each setnode includes a pointer to the `char* key`, a pointer to the `void* item`, and a pointer to the next setnode on the list.

The `set_insert` function allows you to insert a new key-item pair into the set. It takes three parameters: a pointer to the set (`set_t* set`), the key (`const char* key`), and the item (`void* item`) to be associated with that key. The function ensures that keys in the set are unique; if you attempt to insert a duplicate key, the insertion will fail, and the set will remain unchanged. If successful, the function inserts the key-item pair at the head of the list.

The `set_find` function allows you to retrieve an item from the set by its associated key. It takes two parameters: a pointer to the set (`set_t* set`) and the key (`const char* key`) for which you want to find the item. The function searches the set for the specified key and returns the associated item if found. If the key is not found in the set, it returns NULL.

`The set_print` function prints the contents of the set to a specified file stream `(FILE* fp)` in a human-readable format. It takes an additional function pointer parameter void `(*itemprint)(FILE* fp, const char* key, void* item)`, which is used to print each key-item pair. The function surrounds the set with curly braces and prints each key-item pair using the provided `itemprint` function. If the `itemprint` function is NULL, it prints "(null)" for the entire set.

The `set_iterate` method calls the `itemfunc` function on each key-item pair by scanning the linked list.

The `set_delete` method calls the `itemdelete` function on each item, frees the memory allocated for keys, frees the memory allocated for setnodes, and finally frees the memory allocated for the `struct set`.

### Assumptions

No assumptions beyond those that are clear from the spec.

The `key` and `item` inserted cannot be NULL, and thus a NULL return from `set_find` must indicate either an error or a non-existent key, not simply a NULL `item` in the set.

### Files

* `Makefile` - compilation procedure
* `set.h` - the interface
* `set.c` - the implementation
* `settest.c` - unit test driver
* `test.names` - test data
* `testing.out` - result of `make test &> testing.out`

### Compilation

To compile, simply `make settest`.

### Testing

The `settest.c` program performs various tests on the set module. 
It tests inserting key-item pairs, finding items by their associated keys, printing the set, and iterating over the set, deleting the set, and more.

To test, simply `make test`.
See `testing.out` for details of testing and an example test run.