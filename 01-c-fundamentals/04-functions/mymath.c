/*
 * mymath.c -- Exercises 1 and 2: implement the functions declared in
 * mymath.h. Each one currently returns a placeholder value so that the
 * program compiles (until you use them, -Wextra warns about "unused
 * parameters").
 *
 * Build:
 *     make
 *
 * Try it:
 *     echo "p 7" | make run mathtool
 *
 * Test it:
 *     make check mathtool
 */

#include "mymath.h"

bool is_prime(int n)
{
    /* TODO (Exercise 1): numbers below 2 are not prime. Otherwise, try
     * every divisor d from 2 upward. You can stop once d * d > n -- if n had
     * a divisor bigger than its square root, it would also have a 
     * corresponding one smaller than it. */
    return false;
}

int gcd(int a, int b)
{
    /* TODO (Exercise 1): Euclid's algorithm. While `b` is not 0, replace
     * (a, b) with (b, a % b). When `b` reaches 0, `a` is the answer.
     *
     * Tip: Try it on paper with gcd(12, 18) first. */
    return 0;
}

long power(int base, int exp)
{
    /* TODO (Exercise 2): multiply a long result (starting at 1) by `base`,
     * `exp` times. */
    return 0;
}

int sum_digits(int n)
{
    /* TODO (Exercise 2): solve this RECURSIVELY (without a loop).
     *     Base case: a single digit (n < 10) is its own digit sum.
     *     Recursive case: the last digit is n % 10, and the rest of the
     *                     number is n / 10. */
    return 0;
}

int digital_root(int n)
{
    /* TODO (Exercise 2): call `sum_digits` again and again until the
     * result is a single digit. */
    return 0;
}
