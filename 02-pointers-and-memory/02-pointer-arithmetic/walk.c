/*
 * walk.c -- watch pointer arithmetic happen (used in the README and in
 * Exercise 5). 
 *
 * Run it with:
 *     make run walk
 *
 * Your addresses will differ from the README's. Look at the DIFFERENCES.
 */

#include <stdio.h>

int main(void)
{
    int    nums[4] = {10, 20, 30, 40};
    char   text[4] = "abc";
    double reals[4] = {1.5, 2.5, 3.5, 4.5};

    int    *ip = nums;      /* an array name decays to &nums[0] */
    char   *cp = text;
    double *dp = reals;

    printf("%-8s%-16s%-16s%s\n", "", "int *", "char *", "double *");
    for (int i = 0; i < 4; i++) {
        printf("p + %d   %p  %p  %p\n", i,
               (void *)(ip + i), (void *)(cp + i), (void *)(dp + i));
    }

    printf("\nnums[2]     = %d\n", nums[2]);
    printf("*(nums + 2) = %d\n", *(nums + 2));
    printf("*(ip + 2)   = %d\n", *(ip + 2));
    printf("ip[2]       = %d\n", ip[2]);

    int *end = nums + 4;    /* one past the last element: OK to point at, not to read */
    printf("\nend - ip    = %td elements\n", end - ip);
    return 0;
}
