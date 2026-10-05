/*
 * sizes.c -- Exercise 6. 
 *
 * Predict the output BEFORE you run it, then run:
 *     make run sizes
 *
 * print_all() has a bug. Read the compiler warning, then work on Exercise 6.
 */

#include <stdio.h>

/* TODO (Exercise 6): fix print_all() so it prints all 8 numbers */
void print_all(int arr[])
{
    /* BUG: inside this function, arr is NOT an array */
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("print_all thinks there are %d elements:", n);
    for (int i = 0; i < n; i++)
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
    print_all(data);
    return 0;
}
