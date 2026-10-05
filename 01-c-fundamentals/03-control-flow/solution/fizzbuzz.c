/*
 * fizzbuzz.c -- solution for Exercise 1.
 *
 * Multiples of 3 say "Fizz", of 5 say "Buzz", of 7 say "Bang". A number
 * that is a multiple of several says all of them, in that order.
 */
#include <stdio.h>
#include <stdbool.h>

int main(void)
{
    int n;

    if (scanf("%d", &n) != 1 || n < 1) {
        printf("Please enter a positive number.\n");
        return 1;
    }

    for (int i = 1; i <= n; i++) {
        /* Three independent ifs (not else-if), so 15 gets both words. */
        bool said_something = false;

        if (i % 3 == 0) {
            printf("Fizz");
            said_something = true;
        }
        if (i % 5 == 0) {
            printf("Buzz");
            said_something = true;
        }
        if (i % 7 == 0) {
            printf("Bang");
            said_something = true;
        }
        if (!said_something)
            printf("%d", i);
        printf("\n");
    }
    return 0;
}
