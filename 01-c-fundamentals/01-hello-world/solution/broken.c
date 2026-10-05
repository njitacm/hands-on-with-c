/*
 * broken.c -- solution. The three fixes:
 *   1. Added #include <stdio.h> so the compiler knows what printf is.
 *   2. Fixed the typo prinft -> printf.
 *   3. Added the missing semicolon at the end of the printf statement.
 */
#include <stdio.h>

int main(void)
{
    printf("If you can read this, you fixed me!\n");
    return 0;
}
