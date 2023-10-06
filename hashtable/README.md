# CS50 Lab 3
## CS50 Fall 2023

### hashtable

A `hashtable` is an unordered collection of _key-item_ pairs organized into "buckets" based on `hash` values. This structure enables efficient average-case key-value insertion and retrieval operations.

### Usage

The *hashtable* module, defined in `hashtable.h` and implemented in `hashtable.c`, provides a hashtable of `key-item pairs`, and exports the following functions:

```c
hashtable_t* hashtable_new(const int num_slots);
bool hashtable_insert(hashtable_t* ht, const char* key, void* item);
void* hashtable_find(hashtable_t* ht, const char* key);
void hashtable_print(hashtable_t* ht, FILE* fp, void (*itemprint)(FILE* fp, const char* key, void* item));
void hashtable_iterate(hashtable_t* ht, void* arg, void (*itemfunc)(void* arg, const char* key, void* item) );
void hashtable_delete(hashtable_t* ht, void (*itemdelete)(void* item) );
```

### Implementation

We implement the *hashtable* using an array of *set* structures (from the set module). This array is indexed by the hash value of the key modulo the size of the array. Each set then contains key-item pairs as linked lists, allowing us to handle hash collisions.

The `hashtable_insert` function computes the hash value for the key, determines the appropriate index for the array, and then inserts the key-item pair into the associated set.

The `hashtable_find` function, similar to `hashtable_insert`, computes the hash value for the key to find the appropriate index and then attempts to find the key in the associated set.

The `hashtable_print` function prints the hashtable by iterating through each slot and printing the set.

The `hashtable_iterate` function iterates over each key-item pair in the hashtable by iterating over each slot and then each item in the associated set.

The `hashtable_delete` function deletes the hashtable by deleting each set and then the hashtable itself.

### Assumptions

- The key and item inserted cannot be NULL.
- If two keys have the same hash value, they will be stored in the same set (but they remain distinct keys within that set).

### Files

* `Makefile` - compilation procedure
* `hash.c` - contains the hash function used by the hashtable
* `hashtable.h` - the interface
* `hashtable.c` - the implementation
* `hashtabletest.c` - unit test driver
* `testing.out` - result of `make test &> testing.out`

### Compilation

To compile, simply `make hashtabletest`.

### Testing

The `hashtabletest.c` program performs various tests on the hashtable module.
It tests inserting key-item pairs, finding items by their associated keys, printing the hashtable, and iterating over the hashtable, deleting the hashtable, and more.

To test, simply `make test`.
See `testing.out` for details of testing and an example test run.
