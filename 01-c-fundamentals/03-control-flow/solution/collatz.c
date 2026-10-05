/*
 * collatz.c -- solution for Exercise 3.
 */
#include <stdio.h>

int main(void)
{
    long n;

    if (scanf("%ld", &n) != 1 || n < 1) {
        printf("Please enter a positive number.\n");
        return 1;
    }

    int steps = 0;
    long peak = n;

    printf("%ld", n);
    while (n != 1) {
        if (n % 2 == 0)
            n = n / 2;
        else
            n = 3 * n + 1;

        printf(" -> %ld", n);
        steps++;
        if (n > peak)
            peak = n;
    }
    printf("\n");
    printf("Steps: %d\n", steps);
    printf("Peak: %ld\n", peak);
    return 0;
}
