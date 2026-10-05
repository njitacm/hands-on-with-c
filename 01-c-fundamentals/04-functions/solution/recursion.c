/*
 * recursion.c -- solution for Exercise 5.
 */
#include <stdio.h>

/* A global counter, so main can reset and read it. (A static local inside
 * fib would also survive between calls, but main couldn't reset it.) */
long fib_calls = 0;

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
    fib_calls++;
    if (n < 2)
        return n;
    return fib(n - 1) + fib(n - 2);
}

int main(void)
{
    printf("5! = %ld\n\n", factorial(5, 0));

    for (int n = 10; n <= 30; n += 10) {
        fib_calls = 0;
        long f = fib(n);
        printf("fib(%d) = %ld (%ld calls)\n", n, f, fib_calls);
    }
    return 0;
}
