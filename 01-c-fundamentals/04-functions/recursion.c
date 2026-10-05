/*
 * recursion.c -- Exercise 5: watch recursion happen.
 *
 * Build and run with:
 *     make run recursion
 */

#include <stdio.h>

/* Prints a trace of every call and return. depth is how many calls deep
 * we are, used only to indent the output. `%*s` prints the string "" padded
 * to a width of 2 * depth spaces, which is a handy indentation trick. */
long factorial(int n, int depth)
{
    printf("%*sfactorial(%d)\n", 2 * depth, "", n);
    if (n <= 1) {
        printf("%*s-> 1 (base case)\n", 2 * depth, "");
        return 1;
    }
    long result = n * factorial(n - 1, depth + 1);
    printf("%*s-> %ld\n", 2 * depth, "", result);
    return result;
}

long fib(int n)
{
    /* TODO (Exercise 5): count how many times `fib` is called. Add a
     * counter that survives between calls (a global, or a static local)
     * and increment it here. */
    if (n < 2)
        return n;
    return fib(n - 1) + fib(n - 2);
}

int main(void)
{
    printf("5! = %ld\n\n", factorial(5, 0));

    for (int n = 10; n <= 30; n += 10) {
        /* TODO (Exercise 5): reset your counter, then print how many calls
         * each `fib(n)` took. */
        printf("fib(%d) = %ld\n", n, fib(n));
    }
    return 0;
}
