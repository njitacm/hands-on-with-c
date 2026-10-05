/*
 * diamond.c -- solution for Exercise 2.
 */
#include <stdio.h>

int main(void)
{
    int n;

    if (scanf("%d", &n) != 1 || n < 1) {
        printf("Size must be at least 1.\n");
        return 1;
    }

    /* Row r (counting from 0 at the top) is r rows away from the middle
     * row n-1. Its distance d from the middle sets both the indentation
     * (d spaces) and the width (2 * (n - 1 - d) + 1 stars). */
    for (int r = 0; r < 2 * n - 1; r++) {
        int d = r < n ? n - 1 - r : r - (n - 1);

        for (int s = 0; s < d; s++)
            printf(" ");
        for (int s = 0; s < 2 * (n - 1 - d) + 1; s++)
            printf("*");
        printf("\n");
    }
    return 0;
}
