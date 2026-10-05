# Challenge 1: Hello, World!
CC     = gcc
CFLAGS = -std=c11 -Wall -Wextra -g

TESTED = hello
EXTRAS = broken
NOT_IN_ALL = broken

hello: hello.c
	$(CC) $(CFLAGS) -o $@ $^

broken: broken.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TESTED) $(EXTRAS) *.o *.i *.s

.PHONY: clean

# `make run` and `make check` work the same way in every challenge; see ../../.rules.mk
include ../../.rules.mk
