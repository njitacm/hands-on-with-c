# Challenge 2: Pointer Arithmetic & Arrays
CC     = gcc
CFLAGS = -std=c11 -Wall -Wextra -g

TESTED = ptrs
EXTRAS = walk sizes
NOT_IN_ALL = sizes

ptrs: ptrs.c
	$(CC) $(CFLAGS) -o $@ $^

walk: walk.c
	$(CC) $(CFLAGS) -o $@ $^

sizes: sizes.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TESTED) $(EXTRAS) *.o *.i *.s

.PHONY: clean

# `make run` and `make check` work the same way in every challenge; see ../../.rules.mk
include ../../.rules.mk
