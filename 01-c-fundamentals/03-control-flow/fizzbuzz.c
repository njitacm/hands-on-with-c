/*
 * fizzbuzz.c -- Exercise 1: FizzBuzzBang
 *
 * Read a number n, then print one line for each number from 1 to n:
 *   - multiples of 3 print "Fizz"
 *   - multiples of 5 print "Buzz"
 *   - multiples of 7 print "Bang"
 *   - a multiple of several prints all of them, in that order
 *     (15 -> "FizzBuzz", 21 -> "FizzBang", 105 -> "FizzBuzzBang")
 *   - anything else prints the number itself
 * If the input isn't a number, or is less than 1, print
 *     Please enter a positive number.
 * and return 1.
 *
 * Try it:
 *     echo 15 | make run fizzbuzz
 *
 * Test it:
 *     make check fizzbuzz
 */

#include <stdio.h>
#include <stdbool.h>

int main(void)
{
    int n;

    /* TODO (Exercise 1): read `n` with scanf and handle bad input. */

    /* TODO (Exercise 1): loop from 1 to `n`. Hint: a bool that remembers
     * whether you've printed a word yet makes the "print the number"
     * case easy. */

    return 0;
}
