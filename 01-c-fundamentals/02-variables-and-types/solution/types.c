/*
 * types.c -- solution for Exercise 1.
 * The numbers below are for x86-64 Linux; on 64-bit Windows, long is 4 bytes.
 */
#include <stdio.h>
#include <limits.h>
#include <float.h>

int main(void)
{
    printf("Type       Bytes\n");
    printf("----       -----\n");
    printf("char       %zu\n", sizeof(char));
    printf("short      %zu\n", sizeof(short));
    printf("int        %zu\n", sizeof(int));
    printf("long       %zu\n", sizeof(long));
    printf("long long  %zu\n", sizeof(long long));
    printf("float      %zu\n", sizeof(float));
    printf("double     %zu\n", sizeof(double));

    printf("\n");
    printf("INT_MAX  = %d\n", INT_MAX);
    printf("INT_MIN  = %d\n", INT_MIN);
    printf("SHRT_MAX = %d\n", SHRT_MAX);
    printf("LONG_MAX = %ld\n", LONG_MAX);
    printf("UINT_MAX = %u\n", UINT_MAX);
    return 0;
}
