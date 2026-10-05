/*
 * calc.c -- Exercises 1-3.
 *
 * A tiny command-line calculator:
 *     ./calc 3 + 4        ->  7
 *     ./calc 6 x 7        ->  42      (x, because the shell expands a bare *)
 *
 * Operators: +  -  x  /  %
 * 
 * Errors go to stderr and make the program exit with status 1.
 *
 * Try it:
 *     make run calc 3 + 4
 *
 * Test it:
 *     make check calc
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/* Exercise 2: convert `s` to a long. Return 1 and store the value in `*out` on
 * success. Return 0 if `s` isn't a valid base-10 number or is out
 * of range for a long. */
int parse_long(const char *s, long *out)
{
    /* TODO (Exercise 2): atoi can't tell you when something goes wrong
     * ("abc" gives 0, "12abc" gives 12). Replace it with strtol and check
     * all three ways it can fail (see the README). */
    *out = atoi(s);
    return 1;
}

void usage(const char *prog)
{
    fprintf(stderr, "usage: %s NUMBER OP NUMBER   (OP is one of + - x / %%)\n", prog);
}

int main(int argc, char *argv[])
{
    /* TODO (Exercise 1): there must be exactly three arguments after the
     * program name. If not, call usage(argv[0]) and return 1.
     *
     * Try  ./calc 3 +  before you fix this. What happens, and why?
     *
     * Delete the (void) line once you use argc. */
    (void)argc;

    long a, b;
    if (!parse_long(argv[1], &a)) {
        fprintf(stderr, "%s: '%s' is not a valid number\n", argv[0], argv[1]);
        return 1;
    }
    if (!parse_long(argv[3], &b)) {
        fprintf(stderr, "%s: '%s' is not a valid number\n", argv[0], argv[3]);
        return 1;
    }

    const char *op = argv[2];
    long result;

    /* TODO (Exercise 3): support - x / % as well, using a switch on op[0].
     *   - The operator must be exactly ONE character ("++" is an error).
     *   - Accept '*' too, for users who quote it:  ./calc 6 '*' 7
     *   - Dividing (or %) by zero is an error: message to stderr, return 1.
     *   - Any other operator: message + usage to stderr, return 1. */
    if (strcmp(op, "+") == 0) {
        result = a + b;
    } else {
        fprintf(stderr, "%s: unknown operator '%s'\n", argv[0], op);
        usage(argv[0]);
        return 1;
    }

    printf("%ld\n", result);
    return 0;
}
