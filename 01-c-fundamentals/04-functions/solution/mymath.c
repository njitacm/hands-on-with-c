/*
 * mymath.c -- solution for Exercises 1 and 2.
 */
#include "mymath.h"

bool is_prime(int n)
{
    if (n < 2)
        return false;
    /* Divisors come in pairs (d, n/d), and one of each pair is <= sqrt(n),
     * so checking up to sqrt(n) is enough. d <= n / d avoids the overflow
     * that d * d could hit near INT_MAX. */
    for (int d = 2; d <= n / d; d++) {
        if (n % d == 0)
            return false;
    }
    return true;
}

int gcd(int a, int b)
{
    /* Euclid: gcd(a, b) == gcd(b, a % b), and gcd(a, 0) == a. */
    while (b != 0) {
        int r = a % b;
        a = b;
        b = r;
    }
    return a;
}

long power(int base, int exp)
{
    long result = 1;
    for (int i = 0; i < exp; i++)
        result *= base;
    return result;
}

int sum_digits(int n)
{
    if (n < 10)
        return n;                          /* base case */
    return n % 10 + sum_digits(n / 10);    /* last digit + sum of the rest */
}

int digital_root(int n)
{
    while (n >= 10)
        n = sum_digits(n);
    return n;
}
