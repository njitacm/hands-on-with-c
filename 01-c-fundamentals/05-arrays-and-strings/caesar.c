/*
 * caesar.c -- Exercise 3: the Caesar cipher.
 *
 * The first line of input is the shift. Every line after that is printed
 * with each letter moved "shift" places down the alphabet, wrapping from
 * z back to a and keeping upper/lower case. Everything else (digits,
 * spaces, punctuation) is printed unchanged. With a shift of 3:
 *
 *     Hello, World!   ->   Khoor, Zruog!
 *
 * main() is done for you; you write caesar().
 * 
 * Try it:
 *     printf '3\nHello, World!\n' | make run caesar
 * 
 * Test it:
 *     make check caesar
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE 256

/* Shift every letter in `s` forward by `shift` places, where shift is already
 * between 0 and 25. Change `s` in place. */
void caesar(char s[], int shift)
{
    /* TODO (Exercise 3): loop until you reach the '\0'. For an uppercase
     * letter, c, its position in the alphabet is c - 'A'; add shift, wrap
     * with % 26, and turn it back into a letter by adding 'A'. Lowercase
     * letters work the same way with 'a'. */
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
     * the input. Throw it away, or the first fgets would read an empty line.
     *
     * NOTE: Exercise 5 asks you to see what happens without this. */
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;

    /* % can be negative in C (-3 % 26 == -3), so nudge it into 0..25.
     * That way a shift of -3 decodes a message encoded with 3. */
    shift = (shift % 26 + 26) % 26;

    while (fgets(line, sizeof(line), stdin) != NULL) {
        line[strcspn(line, "\n")] = '\0';
        caesar(line, shift);
        printf("%s\n", line);
    }
    return 0;
}
