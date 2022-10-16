 CC = gcc

all: build/main_ex2 build/skiplist_test

CFLAGS = -g -Wall -Wextra -Wpedantic -Wconversion

INCLUDES = src/*.h

COMMON_DEPS = $(INCLUDES) Makefile

build/%.o: src/%.c $(COMMON_DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

build/main_ex2: build/Ex2.o build/skiplist_utility.o $(COMMON_DEPS)
	$(CC) -o build/main_ex2  build/skiplist_utility.o build/Ex2.o

build/skiplist_test: build/skiplist_test.o build/skiplist_utility.o build/unity.o $(COMMON_DEPS)
	$(CC) -o build/skiplist_test build/skiplist_test.o build/skiplist_utility.o build/unity.o

clean:
	rm -f build/* bin/*
