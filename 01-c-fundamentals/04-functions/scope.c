/*
 * scope.c -- Exercise 3: predict the output BEFORE you run it.
 *
 * Write down the 7 lines you expect, then run:  
 *     make run scope
 */

#include <stdio.h>

int x = 100;                 /* global */

void bump(void)
{
    static int count = 0;    /* initialized once, remembered across calls */
    int temp = 0;            /* initialized on every call */

    count++;
    temp++;
    x++;
    printf("bump: count = %d, temp = %d, x = %d\n", count, temp, x);
}

void shadow(int x)           /* this parameter x hides the global x */
{
    x = x * 2;
    printf("shadow: x = %d\n", x);
}

int main(void)
{
    bump();
    bump();
    shadow(5);
    printf("main: x = %d\n", x);

    int x = 1;               /* a local x hides the global from here on */
    {
        int x = 2;           /* ...and this one hides the local, in this block */
        printf("inner block: x = %d\n", x);
    }
    printf("main again: x = %d\n", x);
    bump();
    return 0;
}
