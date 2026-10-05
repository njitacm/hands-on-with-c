/*
 * bugs.c -- Exercise 5. 
 *
 * This program has FOUR memory bugs. GCC 12 and newer  warn about two of them 
 * but older compilers say nothing at all (NOTE: AFS is on GCC 11). Find all 
 * four by reading the code (look at every malloc and every free) and fix them.
 *
 * Try it:
 *     make run bugs
 *
 * In Section 5 (Finding Memory Bugs) you'll meet tools that find bugs like
 * these automatically. For now, use your eyes and read *all* the instructions
 * in the README.
 */

#include <stdio.h>
#include <stdlib.h>

/* Return a new array holding 0, 1, 4, 9, ... (n squares). */
int *make_squares(int n)
{
    int *a = malloc(n * sizeof *a);
    for (int i = 0; i < n; i++)
        a[i] = i * i;
    return a;
}

int main(void)
{
    for (int round = 1; round <= 3; round++) {
        int *sq = make_squares(5);
        printf("round %d: last square is %d\n", round, sq[4]);
    }

    int *data = make_squares(4);
    free(data);
    printf("data[3] is %d\n", data[3]);
    free(data);

    printf("done\n");
    return 0;
}
