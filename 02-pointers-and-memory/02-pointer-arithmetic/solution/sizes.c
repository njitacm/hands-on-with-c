/*
 * sizes.c -- solution (Exercise 6).
 *
 * When you pass an array to a function, it decays to a pointer to its first
 * element. Inside print_all, arr is really an int *, so sizeof(arr) is the
 * size of a pointer (8), not of the array (32): 8 / 4 = 2 elements.
 *
 * A function can't recover an array's length from a pointer, so the caller
 * (which still has the real array) computes it and passes it in.
 */
#include <stdio.h>
#include <stddef.h>

void print_all(const int arr[], size_t n)
{
    printf("print_all thinks there are %zu elements:", n);
    for (size_t i = 0; i < n; i++)
        printf(" %d", arr[i]);
    printf("\n");
}

int main(void)
{
    int data[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    int *p = data;

    printf("sizeof(data)    = %zu\n", sizeof(data));
    printf("sizeof(data[0]) = %zu\n", sizeof(data[0]));
    printf("sizeof(p)       = %zu\n", sizeof(p));
    printf("main counts %zu elements\n", sizeof(data) / sizeof(data[0]));
    print_all(data, sizeof(data) / sizeof(data[0]));
    return 0;
}
