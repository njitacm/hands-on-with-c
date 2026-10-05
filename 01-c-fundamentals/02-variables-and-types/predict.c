/*
 * predict.c -- Exercise 3: predict the output BEFORE you run it.
 *
 * Write your guess for each line in the comment next to it, then run:
 *     make run predict
 *
 * For every line you got wrong, figure out why.
 */

#include <stdio.h>

int main(void)
{
    int a = 17, b = 5;
    double x = 17;

    printf("1: %d\n", a / b);              /* guess: */
    printf("2: %d\n", a % b);              /* guess: */
    printf("3: %.2f\n", x / b);            /* guess: */
    printf("4: %.2f\n", (double) (a / b)); /* guess: */
    printf("5: %.2f\n", (double) a / b);   /* guess: */
    printf("6: %d\n", (int) 9.99);         /* guess: */
    printf("7: %c\n", 'A' + 25);           /* guess: */
    printf("8: %d\n", '7' - '0');          /* guess: */
    printf("9: %x\n", 3054);               /* guess: */
    printf("10: [%6.2f]\n", 2.675);        /* guess: */
    printf("11: %d\n", 1 / 2 * 10);        /* guess: */
    printf("12: %.1f\n", 1.0 / 2 * 10);    /* guess: */
    return 0;
}
