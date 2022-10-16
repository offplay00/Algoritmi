CC = gcc

all: bin/ex1_main bin/sorting_test

CFLAGS = -g -Wall -Wextra -Wpedantic

INCLUDES = src/*.h

COMMON_DEPS = $(INCLUDES) Makefile

build/%.o: src/%.c $(COMMON_DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

bin/ex1_main: build/ex1.o build/sorting_utility.o build/records_utility.o $(COMMON_DEPS)
	$(CC) -o bin/ex1_main  build/sorting_utility.o build/records_utility.o build/ex1.o

bin/sorting_test: build/sorting_test.o build/sorting_utility.o build/records_utility.o build/unity.o $(COMMON_DEPS)
	$(CC) -o bin/sorting_test build/sorting_utility.o build/records_utility.o build/unity.o build/sorting_test.o
clean:
	rm -f build/* bin/*
