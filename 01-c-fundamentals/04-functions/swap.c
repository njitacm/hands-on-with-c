/*
 * swap.c -- Exercise 4: why doesn't this work?
 * 
 * Build and run with:  
 *     make run swap
 */

#include <stdio.h>

void swap(int a, int b)
{
    int tmp = a;
    a = b;
    b = tmp;
    printf("  inside swap: a = %d, b = %d\n", a, b);
}

int main(void)
{
    int x = 1, y = 2;

    printf("before swap:   x = %d, y = %d\n", x, y);
    swap(x, y);
    printf("after swap:    x = %d, y = %d\n", x, y);
    return 0;
}
