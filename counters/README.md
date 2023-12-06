## Counters

A `counters` is a collection that tracks the _count_ associated with each unique _key_. It starts empty, and allows the caller to increment the count for each _key_ or directly set a specific count for a given _key_.

### Usage

The *counters* module, defined in `counters.h` and implemented in `counters.c`, implements a set of `counters` based on unique `keys`, and exports the following functions:

```c
counters_t* counters_new(void);
int counters_add(counters_t* ctrs, const int key);
int counters_get(counters_t* ctrs, const int key);
bool counters_set(counters_t* ctrs, const int key, const int count);
void counters_print(counters_t* ctrs, FILE* fp);
void counters_iterate(counters_t* ctrs, void* arg, void (*itemfunc)(void* arg, const int key, const int count));
void counters_delete(counters_t* ctrs);
```

### Implementation

We implement this *counter set* as a linked list of counter nodes. Each counter is represented by a unique key and its associated count.

The `counters` structure is represented as a `struct counters` containing a pointer to the head of the list; the head pointer is NULL when the counters set is empty.

Each node in the list is a `struct countersnode`, a type defined internally to the module. Each countersnode includes an `int key`, an `int count`, and a pointer to the next countersnode on the list.

### Assumptions

- The key for a counter is a positive integer.
- The count for a key is non-negative.

Keys and counts inserted cannot be negative. If a negative key or count is provided to any of the functions, they will handle it gracefully without modifying the counters structure.

### Files

* `Makefile` - compilation procedure
* `counters.h` - the interface
* `counters.c` - the implementation
* `counterstest.c` - unit test driver
* `test.integers` - test data
* `testing.out` - result of `make test &> testing.out`

### Compilation

To compile, simply `make counterstest`.

### Testing

The `counterstest.c` program performs various tests on the counters module. It tests adding counters, setting and getting counter values, printing the counters, and deleting the counters.

To test, simply `make test`.
See `testing.out` for details of testing and an example test run.