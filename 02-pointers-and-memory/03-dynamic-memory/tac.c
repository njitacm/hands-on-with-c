/*
 * tac.c -- Exercises 3 and 4.
 *
 * A tiny version of the Unix `tac` command (`cat` backwards): read lines from
 * stdin and print them in reverse order.
 *
 * Try it: 
 *     printf 'one\ntwo\nthree\n' | make run tac
 * 
 * Test it: 
 *     make check tac
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE  1024
#define MAX_LINES 10000

/* Exercise 3: return a newly malloc'd copy of `s`, or NULL if out of memory.
 * The caller must free() the result. */
char *my_strdup(const char *s)
{
    /* TODO (Exercise 3): how many bytes do you need? (Don't forget the '\0'.)
     * malloc them, check for NULL, copy the string in, return the copy. */
    (void)s;
    return NULL;
}

int main(void)
{
    char buf[MAX_LINE];
    char *lines[MAX_LINES];                 /* an array of POINTERS to strings */
    size_t n = 0;

    while (n < MAX_LINES && fgets(buf, sizeof buf, stdin) != NULL) {
        buf[strcspn(buf, "\n")] = '\0';
        /* TODO (Exercise 4): this line is a bug. Run the program and see.
         * Store a copy made with `my_strdup` instead (and check for NULL). */
        lines[n] = buf;
        n++;
    }

    for (size_t i = n; i > 0; i--)
        printf("%s\n", lines[i - 1]);

    /* TODO (Exercise 4): free every string you got from `my_strdup`. */
    return 0;
}
