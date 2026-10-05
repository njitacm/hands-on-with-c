/*
 * args.c -- print every command-line argument
 *
 * Try it:
 *     make args
 *     ./args hello "two words" 42
 */

#include <stdio.h>

int main(int argc, char *argv[])
{
    printf("argc = %d\n", argc);
    for (int i = 0; i < argc; i++)
        printf("argv[%d] = \"%s\"\n", i, argv[i]);
    printf("argv[%d] = %s\n", argc, argv[argc] == NULL ? "NULL" : "not NULL?!");
    return 0;
}
