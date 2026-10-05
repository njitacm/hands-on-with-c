/*
 * types.c -- a playground for C's basic types.
 *
 * Exercise 1: finish the sizeof table and print the limits below.
 * 
 * Build & run it with:  
 *     make run types
 */

#include <stdio.h>
#include <limits.h>   /* INT_MAX, INT_MIN, CHAR_MAX, ... */
#include <float.h>    /* FLT_MAX, DBL_MAX, ...           */

int main(void)
{
    printf("Type     Bytes\n");
    printf("----     -----\n");
    printf("char     %zu\n", sizeof(char));
    printf("int      %zu\n", sizeof(int));
    /* TODO (Exercise 1): add rows for short, long, long long, float,
     * and double. Use %zu, because sizeof gives you a size_t. */

    printf("\n");
    printf("INT_MAX  = %d\n", INT_MAX);
    /* TODO (Exercise 1): print INT_MIN, SHRT_MAX, LONG_MAX (needs %ld),
     * and UINT_MAX (needs %u). */

    return 0;
}
