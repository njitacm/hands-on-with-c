/*
 * pascal.c -- Exercise 3.
 *
 * Builds the first N rows of Pascal's triangle as a JAGGED array: an array
 * of N row pointers, where row i is its own malloc'd block of i + 1 ints.
 *
 *   tri ──► [ row 0 ] ──► 1
 *           [ row 1 ] ──► 1 1
 *           [ row 2 ] ──► 1 2 1
 *           [ row 3 ] ──► 1 3 3 1
 *
 * Try it:
 *     echo 5 | make run pascal
 *
 * Test it:
 *     make check pascal
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_ROWS 30     /* row 30's biggest value still fits in an int */

/* Free rows 0..n-1, then the array of row pointers itself. */
void free_triangle(int **tri, int n)
{
    /* TODO (Exercise 3): free each row, THEN free `tri`. 
     *
     * Why that order? */
    (void)tri;
    (void)n;
}

/* Return a new jagged array holding `n` rows of Pascal's triangle,
 * or NULL if out of memory. */
int **build_triangle(int n)
{
    /* TODO (Exercise 3):
     *   1. malloc an array of `n` row pointers: `int **tri, sizeof *tri`
     *   2. for each row `i`, malloc i + 1 ints: `tri[i], sizeof *tri[i]`
     *   3. the first and last entries of a row are 1; every other entry is
     *      the sum of the two entries above it: `tri[i-1][j-1] + tri[i-1][j]`
     *
     * If a malloc fails, free whatever you already made and return NULL. */
    (void)n;
    return NULL;
}

int main(void)
{
    int n;
    if (scanf("%d", &n) != 1 || n < 0 || n > MAX_ROWS) {
        fprintf(stderr, "pascal: expected a number of rows from 0 to %d\n", MAX_ROWS);
        return 1;
    }
    if (n == 0)
        return 0;

    int **tri = build_triangle(n);
    if (tri == NULL) {
        fprintf(stderr, "pascal: build_triangle failed (out of memory?)\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++)
            printf(j == 0 ? "%d" : " %d", tri[i][j]);
        printf("\n");
    }

    free_triangle(tri, n);
    return 0;
}
