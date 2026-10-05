# Challenge 4: Multidimensional Arrays
CC     = gcc
CFLAGS = -std=c11 -Wall -Wextra -g

TESTED = matmul pascal
EXTRAS = layout

RUN_INPUT_matmul = sample.txt

matmul: matmul.c
	$(CC) $(CFLAGS) -o $@ $^

pascal: pascal.c
	$(CC) $(CFLAGS) -o $@ $^

layout: layout.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TESTED) $(EXTRAS) *.o *.i *.s

.PHONY: clean

# `make run` and `make check` work the same way in every challenge; see ../../.rules.mk
include ../../.rules.mk
