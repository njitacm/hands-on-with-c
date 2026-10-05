/*
 * bounds.c -- Exercise 6: C does not check array bounds.
 *
 * This program has an off-by-one bug. Run it both ways and compare:
 *     make run bounds
 *     make run bounds-asan
 */

#include <stdio.h>

int main(void)
{
    int scores[5] = {90, 85, 77, 100, 62};
    int sum = 0;

    for (int i = 0; i <= 5; i++)    /* the bug: valid indexes are 0..4 */
        sum += scores[i];

    printf("sum = %d\n", sum);
    return 0;
}
