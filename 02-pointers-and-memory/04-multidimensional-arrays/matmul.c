/*
 * matmul.c -- Exercises 1 and 2.
 *
 * Reads two matrices from stdin and prints their product. Each matrix is
 * ONE malloc'd block of rows * cols ints, stored row by row (row-major),
 * so element (i, j) of a matrix with `cols` columns is at index i * cols + j.
 *
 * Input format:            Example:
 *     R1 C1                    2 3
 *     R1 rows of C1 ints       1 2 3
 *     R2 C2                    4 5 6
 *     R2 rows of C2 ints       3 2
 *                              7 8
 *                              9 10
 *                              11 12
 *
 * Try it: 
 *     make run matmul
 *
 * Test it:
 *     make check matmul
 */
#include <stdio.h>
#include <stdlib.h>

/* NOTE: read_matrix is done for you. Read it: it shows how to allocate and
 * fill a single-block matrix. */

/* Read a "rows cols" header and the values that follow into a new block.
 * Returns NULL on bad input or if out of memory. */
int *read_matrix(int *rows, int *cols)
{
    if (scanf("%d %d", rows, cols) != 2 || *rows < 1 || *cols < 1)
        return NULL;

    int *m = malloc((size_t)*rows * *cols * sizeof *m);
    if (m == NULL)
        return NULL;

    for (int i = 0; i < *rows * *cols; i++) {   /* row-major order = reading order */
        if (scanf("%d", &m[i]) != 1) {
            free(m);
            return NULL;
        }
    }
    return m;
}

/* Exercise 1: c = a * b, where a is n x m, b is m x p, and c is n x p.
 * Element (i, j) of c is the dot product of row i of a and column j of b. */
void multiply(const int *a, const int *b, int *c, int n, int m, int p)
{
    /* TODO (Exercise 1): three nested loops over i, j, and k.
     * 
     * Remember: (i, j) of a matrix with `cols` columns is [i * cols + j],
     * and a has m columns, b has p columns, c has p columns. */
    (void)a;
    (void)b;
    (void)n;
    (void)m;
    (void)p;
    c[0] = 0;
}

/* Exercise 2: print one row per line, values separated by single spaces
 * (no space at the start or end of a line). */
void print_matrix(const int *mat, int rows, int cols)
{
    /* TODO (Exercise 2) */
    (void)mat;
    (void)rows;
    (void)cols;
}

int main(void)
{
    int r1, c1, r2, c2;

    int *a = read_matrix(&r1, &c1);
    if (a == NULL) {
        fprintf(stderr, "matmul: could not read the first matrix\n");
        return 1;
    }
    int *b = read_matrix(&r2, &c2);
    if (b == NULL) {
        fprintf(stderr, "matmul: could not read the second matrix\n");
        free(a);
        return 1;
    }
    if (c1 != r2) {
        fprintf(stderr, "matmul: can't multiply %dx%d by %dx%d\n", r1, c1, r2, c2);
        free(a);
        free(b);
        return 1;
    }

    int *c = malloc((size_t)r1 * c2 * sizeof *c);
    if (c == NULL) {
        fprintf(stderr, "matmul: out of memory\n");
        free(a);
        free(b);
        return 1;
    }

    multiply(a, b, c, r1, c1, c2);
    print_matrix(c, r1, c2);

    free(a);
    free(b);
    free(c);
    return 0;
}
