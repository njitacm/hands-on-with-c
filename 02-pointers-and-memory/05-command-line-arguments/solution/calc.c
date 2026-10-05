/*
 * calc.c -- solution (Exercises 1-3).
 *
 * A tiny command-line calculator:
 *     ./calc 3 + 4        ->  7
 *     ./calc 6 x 7        ->  42      (x, because the shell expands a bare *)
 *
 * Operators: +  -  x  /  %
 * Errors go to stderr and make the program exit with status 1.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/* Exercise 2: convert s to a long. Return 1 and store the value in *out on
 * success; return 0 if s isn't entirely a valid base-10 number or is out
 * of range for a long. */
int parse_long(const char *s, long *out)
{
    char *end;
    errno = 0;                      /* strtol only SETS errno on error */
    long value = strtol(s, &end, 10);

    if (end == s)                   /* no digits at all: "", "abc" */
        return 0;
    if (*end != '\0')               /* junk after the number: "12abc" */
        return 0;
    if (errno == ERANGE)            /* too big or too small for a long */
        return 0;

    *out = value;
    return 1;
}

void usage(const char *prog)
{
    fprintf(stderr, "usage: %s NUMBER OP NUMBER   (OP is one of + - x / %%)\n", prog);
}

int main(int argc, char *argv[])
{
    /* Exercise 1: exactly three arguments after the program name. */
    if (argc != 4) {
        usage(argv[0]);
        return 1;
    }

    long a, b;
    if (!parse_long(argv[1], &a)) {
        fprintf(stderr, "%s: '%s' is not a valid number\n", argv[0], argv[1]);
        return 1;
    }
    if (!parse_long(argv[3], &b)) {
        fprintf(stderr, "%s: '%s' is not a valid number\n", argv[0], argv[3]);
        return 1;
    }

    /* Exercise 3: the operator must be exactly one character long. */
    const char *op = argv[2];
    if (strlen(op) != 1) {
        fprintf(stderr, "%s: unknown operator '%s'\n", argv[0], op);
        usage(argv[0]);
        return 1;
    }

    long result;
    switch (op[0]) {
    case '+':
        result = a + b;
        break;
    case '-':
        result = a - b;
        break;
    case 'x':
    case '*':                       /* works if the user quotes it: '*' */
        result = a * b;
        break;
    case '/':
    case '%':
        if (b == 0) {
            fprintf(stderr, "%s: division by zero\n", argv[0]);
            return 1;
        }
        result = (op[0] == '/') ? a / b : a % b;
        break;
    default:
        fprintf(stderr, "%s: unknown operator '%s'\n", argv[0], op);
        usage(argv[0]);
        return 1;
    }

    printf("%ld\n", result);
    return 0;
}
