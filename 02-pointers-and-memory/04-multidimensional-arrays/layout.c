/*
 * layout.c -- a static 2D array in memory.
 *
 * Try it:
 *     make run layout
 */

#include <stdio.h>

#define ROWS 3
#define COLS 4

/* The number of COLUMNS must be part of the parameter type; see the README. */
void print_matrix(int rows, int m[][COLS])
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < COLS; j++)
            printf("%4d", m[i][j]);
        printf("\n");
    }
}

/* TODO (Exercise 5): write
 *     void transpose(int rows, int src[][COLS], int dst[][ROWS])
 * so that dst[j][i] = src[i][j], then call it from main and print the
 * 4x3 result (you'll need a print loop for a [][ROWS] matrix too). */

int main(void)
{
    int m[ROWS][COLS] = {
        { 1,  2,  3,  4},
        { 5,  6,  7,  8},
        { 9, 10, 11, 12},
    };

    print_matrix(ROWS, m);

    printf("\nsizeof(m)    = %zu bytes (the whole matrix)\n", sizeof(m));
    printf("sizeof(m[0]) = %zu bytes (one row)\n", sizeof(m[0]));

    printf("\nelement    address         offset from m[0][0]\n");
    char *base = (char *)&m[0][0];
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            printf("m[%d][%d]    %p  %3td bytes\n", i, j,
                   (void *)&m[i][j], (char *)&m[i][j] - base);
    return 0;
}
