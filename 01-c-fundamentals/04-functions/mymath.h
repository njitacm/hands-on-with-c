/*
 * mymath.h -- the "catalogue" of functions that mymath.c provides.
 *
 * A header holds DECLARATIONS (prototypes): each function's name, return
 * type, and parameter types, with no body. Any .c file that wants to call
 * these functions writes  
 * 
 * #include "mymath.h"  
 * 
 * at the top.
 *
 * NOTE: You don't need to edit this file.
 */
#ifndef MYMATH_H    /* "include guard": if this file gets #included twice, */
#define MYMATH_H    /* the second copy is skipped. More in Section 5.      */

#include <stdbool.h>

/* true if `n` is prime (only divisible by 1 and itself). Numbers below 2
 * are not prime. */
bool is_prime(int n);

/* Greatest common divisor of two non-negative integers, e.g.
 * gcd(12, 18) == 6. gcd(n, 0) == n. */
int gcd(int a, int b);

/* base raised to the power exp, for exp >= 0. power(2, 10) == 1024 and
 * power(anything, 0) == 1. */
long power(int base, int exp);

/* Sum of the decimal digits of `n` (n >= 0), computed RECURSIVELY.
 * sum_digits(12345) == 15. */
int sum_digits(int n);

/* Keep summing digits until a single digit is left (n >= 0).
 * digital_root(98765): 9+8+7+6+5 = 35, 3+5 = 8, so the answer is 8. */
int digital_root(int n);

#endif
