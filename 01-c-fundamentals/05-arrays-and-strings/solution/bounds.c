/*
 * bounds.c -- solution for Exercise 6.
 *
 * The valid indexes of a 5-element array are 0..4, so the loop must use
 * i < 5, not i <= 5. Better still, compute the length from the array so
 * it can never get out of sync with the declaration.
 */
#include <stdio.h>

int main(void)
{
    int scores[5] = {90, 85, 77, 100, 62};
    int sum = 0;
    int n = sizeof(scores) / sizeof(scores[0]);

    for (int i = 0; i < n; i++)
        sum += scores[i];

    printf("sum = %d\n", sum);
    return 0;
}
