# Challenge 3: Control Flow
CC     = gcc
CFLAGS = -std=c11 -Wall -Wextra -g

TESTED = fizzbuzz diamond collatz
EXTRAS = oops
NOT_IN_ALL = oops

fizzbuzz: fizzbuzz.c
	$(CC) $(CFLAGS) -o $@ $^

diamond: diamond.c
	$(CC) $(CFLAGS) -o $@ $^

collatz: collatz.c
	$(CC) $(CFLAGS) -o $@ $^

oops: oops.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TESTED) $(EXTRAS) *.o *.i *.s

.PHONY: clean

# `make run` and `make check` work the same way in every challenge; see ../../.rules.mk
include ../../.rules.mk
