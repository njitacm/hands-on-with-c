# Challenge 4: Functions & Scope
CC     = gcc
CFLAGS = -std=c11 -Wall -Wextra -g

TESTED = mathtool
EXTRAS = swap scope recursion

# Two .c files are compiled and linked into ONE program. The header is
# listed as a dependency so that editing it triggers a rebuild.
mathtool: main.c mymath.c mymath.h
	$(CC) $(CFLAGS) -o $@ main.c mymath.c

swap: swap.c
	$(CC) $(CFLAGS) -o $@ $^

scope: scope.c
	$(CC) $(CFLAGS) -o $@ $^

recursion: recursion.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TESTED) $(EXTRAS) *.o *.i *.s

.PHONY: clean

# `make run` and `make check` work the same way in every challenge; see ../../.rules.mk
include ../../.rules.mk
