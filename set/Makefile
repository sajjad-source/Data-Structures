OBJS = settest.o set.o ../lib/file.o ../lib/mem.o 
LIBS =

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../lib
CC = gcc
MAKE = make
# for memory-leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

settest: $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

settest.o: set.h ../lib/file.h
set.o: set.h
../lib/file.o: ../lib/file.h

.PHONY: test valgrind clean

# expects a file `test.names` to exist; it can contain any text.
test: settest test.names
	./settest < test.names

valgrind: settest test.names
	$(VALGRIND) ./settest < test.names

clean:
	rm -rf *.dSYM
	rm -f *~ *.o
	rm -f settest
	rm -f core