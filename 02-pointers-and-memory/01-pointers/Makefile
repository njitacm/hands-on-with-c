# Challenge 1: Pointers & Addresses
CC     = gcc
CFLAGS = -std=c11 -Wall -Wextra -g

TESTED = pointers
EXTRAS = addresses predict dangling
NOT_IN_ALL = dangling

pointers: pointers.c
	$(CC) $(CFLAGS) -o $@ $^

addresses: addresses.c
	$(CC) $(CFLAGS) -o $@ $^

predict: predict.c
	$(CC) $(CFLAGS) -o $@ $^

dangling: dangling.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TESTED) $(EXTRAS) *.o *.i *.s

.PHONY: clean

# `make run` and `make check` work the same way in every challenge; see ../../.rules.mk
include ../../.rules.mk
