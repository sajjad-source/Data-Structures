OBJS = hashtabletest.o hashtable.o ../lib/file.o ../lib/mem.o  ../set/set.o hash.o
LIBS =

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../lib -I../set
CC = gcc
MAKE = make
# for memory-leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

hashtabletest: $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

hashtabletest.o: hashtable.h ../lib/file.h
hashtable.o: hashtable.h
../lib/file.o: ../lib/file.h

.PHONY: test valgrind clean

# expects a file `test.names` to exist; it can contain any text.
test: hashtabletest test.names
	./hashtabletest < test.names

valgrind: hashtabletest test.names
	$(VALGRIND) ./hashtabletest < test.names

clean:
	rm -rf *.dSYM
	rm -f *~ *.o
	rm -f hashtabletest
	rm -f core