/*
 * where.c -- where do different kinds of variables live? 
 *
 * Run it with:
 *     make run where
 *
 * Your addresses will differ. Look at which ones are close to each other.
 */

#include <stdio.h>
#include <stdlib.h>

int global_counter = 0;                 /* lives for the whole program */

int main(void)
{
    int local = 42;                     /* on the stack: dies when main returns */
    int *heap = malloc(sizeof *heap);   /* on the heap: lives until free() */
    const char *literal = "hello";      /* read-only data: next to the code */

    if (heap == NULL)
        return 1;
    *heap = 7;

    printf("code    (main)           %p\n", (void *)main);
    printf("literal (\"hello\")        %p\n", (void *)literal);
    printf("global  (global_counter) %p\n", (void *)&global_counter);
    printf("heap    (*heap)          %p\n", (void *)heap);
    printf("stack   (local)          %p\n", (void *)&local);
    printf("stack   (heap, the ptr)  %p\n", (void *)&heap);

    free(heap);
    return 0;
}
