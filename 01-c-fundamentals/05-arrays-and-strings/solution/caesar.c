/*
 * caesar.c -- solution for Exercise 3.
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE 256

/* Shift every letter in s forward by shift places (0..25), wrapping
 * around the alphabet and keeping its case. Other characters stay put. */
void caesar(char s[], int shift)
{
    for (int i = 0; s[i] != '\0'; i++) {
        unsigned char c = s[i];

        if (isupper(c))
            s[i] = 'A' + (c - 'A' + shift) % 26;
        else if (islower(c))
            s[i] = 'a' + (c - 'a' + shift) % 26;
    }
}

int main(void)
{
    int shift;
    char line[MAX_LINE];

    if (scanf("%d", &shift) != 1) {
        printf("The first line must be a number.\n");
        return 1;
    }

    /* scanf left the rest of the first line (at least its '\n') waiting in
     * the input. Throw it away, or the first fgets would read an empty line. */
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;

    /* % can be negative in C (-3 % 26 == -3), so nudge it into 0..25. */
    shift = (shift % 26 + 26) % 26;

    while (fgets(line, sizeof(line), stdin) != NULL) {
        line[strcspn(line, "\n")] = '\0';
        caesar(line, shift);
        printf("%s\n", line);
    }
    return 0;
}
