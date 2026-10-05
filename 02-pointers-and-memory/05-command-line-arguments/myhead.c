/*
 * myhead.c -- Exercise 4.
 *
 * A small version of `head`: print the first N lines of standard input.
 *
 *     ./myhead [-n N] [-v]
 *     
 *     -n N   print the first N lines instead of 10
 *     -v     print a "==> standard input <==" header first, like head -v
 *
 * Options can come in any order:  
 *     ./myhead -v -n 3
 *     ./myhead -n 3 -v
 *
 * Try it:
 *     make myhead
 *     seq 1 100 | ./myhead -n 3
 *
 * Test it:
 *     make check myhead
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void usage(const char *prog)
{
    fprintf(stderr, "usage: %s [-n N] [-v]\n", prog);
}

int main(int argc, char *argv[])
{
    long n = 10;
    int verbose = 0;

    /* TODO (Exercise 4): loop over argv[1] .. argv[argc - 1].
     *   "-v"   -> set verbose
     *   "-n"   -> the NEXT argument is the line count. Error if there is no
     *             next argument, or if it isn't a valid number >= 0
     *             (use strtol with full error checking). Skip over it.
     *   other  -> "unknown option" + usage to stderr, return 1
     * Every error message goes to stderr, and the program returns 1. */
    (void)argc;
    (void)argv;

    if (verbose)
        printf("==> standard input <==\n");

    /* Copy characters until we've printed `n` newlines. Working a character
     * at a time means there's no limit on how long a line can be. */
    long lines = 0;
    int c;
    while (lines < n && (c = getchar()) != EOF) {
        putchar(c);
        if (c == '\n')
            lines++;
    }
    return 0;
}
