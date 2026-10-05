/*
 * collatz.c -- Exercise 3: the Collatz sequence.
 *
 * Start from a positive number n. While n is not 1:
 *     if n is even, n = n / 2; otherwise, n = 3n + 1.
 * Print the whole sequence on one line, then the number of steps and the
 * largest value reached. For n = 6:
 *
 *     6 -> 3 -> 10 -> 5 -> 16 -> 8 -> 4 -> 2 -> 1
 *     Steps: 8
 *     Peak: 16
 *
 * If the input isn't a number, or is less than 1, print
 *     Please enter a positive number.
 * and return 1.
 *
 * Try it:
 *     echo 6 | make run collatz
 *
 * Test it:
 *     make check collatz
 */

#include <stdio.h>

int main(void)
{
    long n;   /* long, because some sequences climb surprisingly high */

    /* TODO (Exercise 3): read `n` (use `%ld` for a long) and handle bad input. */

    /* TODO (Exercise 3): you don't know in advance how many steps it will
     * take, so this is a job for a while loop, not a for loop. Keep track
     * of the step count and the peak as you go. */

    return 0;
}
