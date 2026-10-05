/*
 * swap.c -- "solution" for Exercise 4.
 *
 * There is no way to fix this with what you know so far, and that's the
 * point. C passes arguments BY VALUE: swap() gets its own copies a and b,
 * swaps the copies, and the copies vanish when swap() returns. x and y in
 * main are never touched.
 *
 * The real fix needs pointers (Section 2, Challenge 1): pass the
 * ADDRESSES of x and y, and swap what they point to. Here it is as a
 * preview; don't worry about the * and & yet.
 */
#include <stdio.h>

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
    printf("  inside swap: *a = %d, *b = %d\n", *a, *b);
}

int main(void)
{
    int x = 1, y = 2;

    printf("before swap:   x = %d, y = %d\n", x, y);
    swap(&x, &y);
    printf("after swap:    x = %d, y = %d\n", x, y);
    return 0;
}
