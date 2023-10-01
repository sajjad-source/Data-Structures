OBJS = counterstest.o counters.o ../lib/file.o ../lib/mem.o 
LIBS =

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../lib
CC = gcc
MAKE = make
# for memory-leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

counterstest: $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

counterstest.o: counters.h ../lib/file.h
counter.o: counters.h
../lib/file.o: ../lib/file.h

.PHONY: test valgrind clean

# expects a file `test.integers` to exist; it can contain any text.
test: counterstest test.integers
	./counterstest < test.integers

valgrind: counterstest test.integers
	$(VALGRIND) ./counterstest < test.integers

clean:
	rm -rf *.dSYM
	rm -f *~ *.o
	rm -f counterstest
	rm -f core