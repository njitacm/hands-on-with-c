# Challenge 5: Arrays & Strings
CC     = gcc
CFLAGS = -std=c11 -Wall -Wextra -g

TESTED = textstats palindrome caesar
EXTRAS = bounds bounds-asan

RUN_INPUT_textstats = tests/textstats/njit.in

textstats: textstats.c
	$(CC) $(CFLAGS) -o $@ $^

palindrome: palindrome.c
	$(CC) $(CFLAGS) -o $@ $^

caesar: caesar.c
	$(CC) $(CFLAGS) -o $@ $^

bounds: bounds.c
	$(CC) $(CFLAGS) -o $@ $^

# The same program, built with AddressSanitizer, which catches
# out-of-bounds memory accesses while the program runs.
bounds-asan: bounds.c
	$(CC) $(CFLAGS) -fsanitize=address -o $@ $^

clean:
	rm -f $(TESTED) $(EXTRAS) *.o *.i *.s

.PHONY: clean

# `make run` and `make check` work the same way in every challenge; see ../../.rules.mk
include ../../.rules.mk
