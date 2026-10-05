# Challenge 3: Dynamic Memory
CC     = gcc
CFLAGS = -std=c11 -Wall -Wextra -g

TESTED = stats tac
EXTRAS = where bugs
NOT_IN_ALL = bugs

stats: stats.c
	$(CC) $(CFLAGS) -o $@ $^

tac: tac.c
	$(CC) $(CFLAGS) -o $@ $^

where: where.c
	$(CC) $(CFLAGS) -o $@ $^

bugs: bugs.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TESTED) $(EXTRAS) *.o *.i *.s

.PHONY: clean

# `make run` and `make check` work the same way in every challenge; see ../../.rules.mk
include ../../.rules.mk
