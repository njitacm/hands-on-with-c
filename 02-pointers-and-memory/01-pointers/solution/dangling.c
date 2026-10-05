/*
 * dangling.c -- solution (Exercise 5).
 *
 * The bug: buf was a local variable, so it lived in make_greeting's stack
 * frame. That memory is released the moment the function returns, so the
 * returned pointer pointed at nothing valid (a "dangling pointer").
 *
 * The fix: the caller owns the buffer (it lives in main's frame, which is
 * still alive while we use it) and passes a pointer to it in. This is the
 * same out-parameter pattern as swap() and min_max(), and it's how library
 * functions like snprintf() and fgets() work.
 */
#include <stdio.h>

void make_greeting(const char *name, char *out, int out_size)
{
    snprintf(out, out_size, "Hello, %s!", name);
}

int main(void)
{
    char msg[64];
    make_greeting("Highlander", msg, sizeof msg);
    printf("%s\n", msg);
    return 0;
}
