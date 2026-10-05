/*
 * tac.c -- solution (Exercises 3 and 4).
 *
 * A tiny version of the Unix `tac` command (`cat` backwards): reads lines from
 * stdin and prints them in reverse order. Each line is read into one reusable
 * buffer, so it has to be COPIED to the heap before the next fgets overwrites
 * it. That's exactly what my_strdup is for.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE  1024
#define MAX_LINES 10000

/* Exercise 3: return a newly malloc'd copy of s, or NULL if out of memory.
 * The caller must free() the result. */
char *my_strdup(const char *s)
{
    size_t len = strlen(s);
    char *copy = malloc(len + 1);           /* + 1 for the '\0' */
    if (copy == NULL)
        return NULL;
    memcpy(copy, s, len + 1);               /* copies the '\0' too */
    return copy;
}

int main(void)
{
    char buf[MAX_LINE];
    char *lines[MAX_LINES];                 /* an array of POINTERS to strings */
    size_t n = 0;

    while (n < MAX_LINES && fgets(buf, sizeof buf, stdin) != NULL) {
        buf[strcspn(buf, "\n")] = '\0';
        /* Exercise 4: store a copy, not buf itself (every line would point
         * at the same buffer). */
        lines[n] = my_strdup(buf);
        if (lines[n] == NULL) {
            fprintf(stderr, "tac: out of memory\n");
            break;
        }
        n++;
    }

    for (size_t i = n; i > 0; i--)
        printf("%s\n", lines[i - 1]);

    /* Every malloc needs exactly one free. */
    for (size_t i = 0; i < n; i++)
        free(lines[i]);
    return 0;
}
