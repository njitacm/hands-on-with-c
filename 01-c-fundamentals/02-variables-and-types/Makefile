# Challenge 2: Variables, Types & printf
CC     = gcc
CFLAGS = -std=c11 -Wall -Wextra -g

TESTED = receipt
EXTRAS = types predict buggy
NOT_IN_ALL = buggy

receipt: receipt.c
	$(CC) $(CFLAGS) -o $@ $^

types: types.c
	$(CC) $(CFLAGS) -o $@ $^

predict: predict.c
	$(CC) $(CFLAGS) -o $@ $^

buggy: buggy.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TESTED) $(EXTRAS) *.o *.i *.s

.PHONY: clean

# `make run` and `make check` work the same way in every challenge; see ../../.rules.mk
include ../../.rules.mk
