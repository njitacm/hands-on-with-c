# Challenge 5: Command-Line Arguments
CC     = gcc
CFLAGS = -std=c11 -Wall -Wextra -g

TESTED = calc myhead
EXTRAS = args

RUN_ARGS_calc = 3 + 4

calc: calc.c
	$(CC) $(CFLAGS) -o $@ $^

myhead: myhead.c
	$(CC) $(CFLAGS) -o $@ $^

args: args.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TESTED) $(EXTRAS) *.o *.i *.s

.PHONY: clean

# `make run` and `make check` work the same way in every challenge; see ../../.rules.mk
include ../../.rules.mk
