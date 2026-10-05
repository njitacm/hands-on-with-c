/*
 * myhead.c -- solution (Exercise 4).
 *
 * A small version of `head`: print the first N lines of standard input.
 *
 *     ./myhead [-n N] [-v]
 *
 *   -n N   print the first N lines instead of 10
 *   -v     print a "==> standard input <==" header first, like head -v
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

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-v") == 0) {
            verbose = 1;
        } else if (strcmp(argv[i], "-n") == 0) {
            if (i + 1 >= argc) {            /* "-n" was the last argument */
                fprintf(stderr, "%s: option -n needs a number\n", argv[0]);
                usage(argv[0]);
                return 1;
            }
            i++;                            /* consume the number, too */
            char *end;
            errno = 0;
            n = strtol(argv[i], &end, 10);
            if (end == argv[i] || *end != '\0' || errno == ERANGE || n < 0) {
                fprintf(stderr, "%s: invalid number of lines: '%s'\n", argv[0], argv[i]);
                return 1;
            }
        } else {
            fprintf(stderr, "%s: unknown option '%s'\n", argv[0], argv[i]);
            usage(argv[0]);
            return 1;
        }
    }

    if (verbose)
        printf("==> standard input <==\n");

    /* Copy characters until we've printed n newlines. Working a character
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
