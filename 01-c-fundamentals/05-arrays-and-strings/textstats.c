/*
 * textstats.c -- Exercise 1: statistics about text on stdin.
 *
 * Read the input one line at a time with fgets and count:
 *   Lines          - number of lines
 *   Characters     - characters on all lines, NOT counting the newlines
 *   Letters        - isalpha()
 *   Digits         - isdigit()
 *   Words          - runs of non-space characters ("a  b" is 2 words)
 *   Longest line   - length of the longest line, without its newline
 * 
 * and then the most common letter, ignoring case (on a tie, the one that
 * comes first in the alphabet).
 *
 * Try it:  
 *     ./textstats < tests/textstats/njit.in
 * 
 * Test it:  
 *     make check textstats
 *
 * Or run 
 *     ./textstats
 * type some lines, and press Ctrl+D to end the input.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_LINE 256

int main(void)
{
    char line[MAX_LINE];
    int letter_counts[26] = {0};    /* letter_counts[0] is 'a', [25] is 'z' */
    int lines = 0, chars = 0, letters = 0, digits = 0, words = 0;
    int longest = 0;

    while (fgets(line, sizeof(line), stdin) != NULL) {
        /* TODO (Exercise 1): strip the newline from line. */

        lines++;

        /* TODO (Exercise 1): update chars and longest using strlen. */

        /* TODO (Exercise 1): loop over the characters in line and update
         * letters, digits, words, and letter_counts. 
	 *
	 * Tips:
         *   - copy each character into an `unsigned char c` before
         *     passing it to isalpha() and friends
         *   - `tolower(c)`: example: 'a' turns a letter into an index 0..25
         *   - for words, keep a `bool in_word`: a word starts whenever you
         *     see a non-space character while `in_word` is false */
    }

    printf("Lines: %d\n", lines);
    printf("Characters: %d\n", chars);
    printf("Letters: %d\n", letters);
    printf("Digits: %d\n", digits);
    printf("Words: %d\n", words);
    printf("Longest line: %d\n", longest);

    /* TODO (Exercise 1): find the most common letter in `letter_counts` and
     * print it as:
     *     Most common letter: e (9)
     * 
     * or, if there were no letters at all:
     *     Most common letter: none */

    return 0;
}
