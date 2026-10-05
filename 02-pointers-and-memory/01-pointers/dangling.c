/*
 * dangling.c -- this program has a classic pointer bug (Exercise 5).
 *
 * make_greeting() builds a string in a LOCAL array and returns a pointer to it.
 *
 * Build it with 
 *     make dangling 
 * read the warning, then run it.
 *
 * TODO (Exercise 5): fix it by having the CALLER provide the buffer:
 *     void make_greeting(const char *name, char *out, int out_size)
 */

#include <stdio.h>

char *make_greeting(const char *name)
{
    char buf[64];
    snprintf(buf, sizeof buf, "Hello, %s!", name);
    return buf;     /* BUG: buf dies when this function returns */
}

int main(void)
{
    char *msg = make_greeting("Highlander");
    printf("%s\n", msg);
    return 0;
}
