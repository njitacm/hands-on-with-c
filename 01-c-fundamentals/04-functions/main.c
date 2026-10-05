/*
 * main.c -- a tiny calculator that tests the functions in mymath.c.
 *
 * It reads commands from stdin, one per
 * line, and prints the result of calling the matching function:
 *
 *     p N      is_prime(N)
 *     g A B    gcd(A, B)
 *     e B X    power(B, X)       ("e" for exponent)
 *     s N      sum_digits(N)
 *     r N      digital_root(N)
 *
 * Try it:
 *     echo "g 12 18" | make run mathtool
 *
 * or just
 *     make run mathtool
 * and type commands (press Ctrl+D to finish).
 *
 * NOTE: you don't need to edit this file.
 */

#include <stdio.h>
#include "mymath.h"   /* NOTE: quotes on an include statement tells the 
			 preprocessor to look in THIS directory, not the 
			 system's */

int main(void)
{
    char cmd;
    int a, b;

    /* The space before `%c` skips whitespace, including the previous newline. */
    while (scanf(" %c", &cmd) == 1) {
        switch (cmd) {
        case 'p':
            if (scanf("%d", &a) != 1)
                return 1;
            printf("is_prime(%d) = %s\n", a, is_prime(a) ? "true" : "false");
            break;
        case 'g':
            if (scanf("%d %d", &a, &b) != 2)
                return 1;
            printf("gcd(%d, %d) = %d\n", a, b, gcd(a, b));
            break;
        case 'e':
            if (scanf("%d %d", &a, &b) != 2)
                return 1;
            printf("power(%d, %d) = %ld\n", a, b, power(a, b));
            break;
        case 's':
            if (scanf("%d", &a) != 1)
                return 1;
            printf("sum_digits(%d) = %d\n", a, sum_digits(a));
            break;
        case 'r':
            if (scanf("%d", &a) != 1)
                return 1;
            printf("digital_root(%d) = %d\n", a, digital_root(a));
            break;
        default:
            printf("unknown command '%c'\n", cmd);
            return 1;
        }
    }
    return 0;
}
