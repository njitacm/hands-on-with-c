/*
 * layout.c -- solution (Exercise 5 adds transpose).
 * Run it with:  make layout && ./layout
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

/* Exercise 5: row i of src becomes column i of dst. */
void transpose(int rows, int src[][COLS], int dst[][ROWS])
{
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < COLS; j++)
            dst[j][i] = src[i][j];
}

/* A COLS x ROWS matrix has a different row length, so it needs its own
 * parameter type (and therefore its own function). */
void print_transposed(int t[][ROWS])
{
    for (int i = 0; i < COLS; i++) {
        for (int j = 0; j < ROWS; j++)
            printf("%4d", t[i][j]);
        printf("\n");
    }
}

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

    int t[COLS][ROWS];
    transpose(ROWS, m, t);
    printf("\ntransposed:\n");
    print_transposed(t);
    return 0;
}
