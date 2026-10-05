/*
 * addresses.c -- see where your variables live (used in the README and in
 * Exercise 6). 
 *
 * Run it with:
 *     make run addresses
 *
 * Your addresses will be different from the README's, and may even change
 * from run to run -- that's normal (look up "ASLR" if you're curious).
 */
#include <stdio.h>

int main(void)
{
    int a = 10;
    int b = 20;
    int *p = &a;            /* `p` holds the address of `a` */

    printf("a  = %d, stored at %p\n", a, (void *)&a);
    printf("b  = %d, stored at %p\n", b, (void *)&b);
    printf("p  = %p (p points to a)\n", (void *)p);
    printf("*p = %d\n", *p);
    printf("p itself is stored at %p\n", (void *)&p);

    *p = 99;                /* follow the arrow and write: changes `a` */
    printf("after *p = 99:  a = %d\n", a);

    p = &b;                 /* re-aim the arrow; `a` is untouched */
    *p = *p + 1;
    printf("after p = &b; *p = *p + 1:  a = %d, b = %d\n", a, b);

    printf("sizeof(int) = %zu, sizeof(int *) = %zu, sizeof(char *) = %zu\n",
           sizeof(int), sizeof(int *), sizeof(char *));
    return 0;
}
