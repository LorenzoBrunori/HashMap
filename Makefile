CC=clang
CFLAGS=-O2 -Wall -Werror -I.
BINARY_TESTS=run_test

all: run_test

run_test: Test.o HashMap.o
	$(CC) -o $(BINARY_TESTS) $^
	./$(BINARY_TESTS)


HashMap.o: HashMap.c HashMap.h 
	$(CC) -c -o $@ $(CFLAGS) $<

Test.o: Test.c aiv_unit_test.h
	$(CC) -c -o $@ $(CFLAGS) $<
