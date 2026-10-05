/*
 * palindrome.c -- Exercise 2: reverse strings and detect palindromes.
 *
 * main() is done for you: for every line of input it prints the line, the
 * line reversed, and whether it's a palindrome. You just have towrite the 
 * two functions it calls. 
 *
 * Try it:
 *     $ echo "Taco cat" | ./palindrome
 *     "Taco cat" reversed is "tac ocaT" -> palindrome
 *
 * Test it: 
 *     make check palindrome
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_LINE 256

/* Reverse `s` IN PLACE: "abc" becomes "cba". */
void reverse(char s[])
{
    /* TODO (Exercise 2): use two indexes, one starting at the first
     * character and one at the last (`strlen(s) - 1`). Swap the characters
     * they point at and move both inward until they meet. */
}

/* true if `s` reads the same forwards and backwards, considering only
 * letters and digits (isalnum) and ignoring case. So
 * "A man, a plan, a canal: Panama!" is a palindrome. An empty string is
 * a palindrome too. Don't change `s` (that's what the const promises). */
bool is_palindrome(const char s[])
{
    /* TODO (Exercise 2): the same two-index idea as `reverse()`, but compare
     * instead of swap. Skip over any character that isn't a letter or a
     * digit, and compare with `tolower()` on both sides. */
    return false;
}

int main(void)
{
    char line[MAX_LINE];
    char backwards[MAX_LINE];

    while (fgets(line, sizeof(line), stdin) != NULL) {
        line[strcspn(line, "\n")] = '\0';

        /* `reverse()` changes its argument, so work on a copy. `backwards` is
         * the same size as `line`, so strcpy can't overflow it. */
        strcpy(backwards, line);
        reverse(backwards);

        printf("\"%s\" reversed is \"%s\" -> %s\n", line, backwards,
               is_palindrome(line) ? "palindrome" : "not a palindrome");
    }
    return 0;
}
