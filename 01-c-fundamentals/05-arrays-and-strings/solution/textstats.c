/*
 * textstats.c -- solution for Exercise 1.
 *
 * Reads text from stdin, one line at a time, and prints statistics.
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
        line[strcspn(line, "\n")] = '\0';
        lines++;

        int len = strlen(line);
        chars += len;
        if (len > longest)
            longest = len;

        bool in_word = false;
        for (int i = 0; i < len; i++) {
            /* ctype functions need an unsigned char value (or EOF). */
            unsigned char c = line[i];

            if (isalpha(c)) {
                letters++;
                letter_counts[tolower(c) - 'a']++;
            } else if (isdigit(c)) {
                digits++;
            }

            /* A word starts wherever a non-space follows a space (or the
             * start of the line). */
            if (isspace(c)) {
                in_word = false;
            } else if (!in_word) {
                in_word = true;
                words++;
            }
        }
    }

    printf("Lines: %d\n", lines);
    printf("Characters: %d\n", chars);
    printf("Letters: %d\n", letters);
    printf("Digits: %d\n", digits);
    printf("Words: %d\n", words);
    printf("Longest line: %d\n", longest);

    /* Strict > keeps the earliest letter on a tie. */
    int best = 0;
    for (int i = 1; i < 26; i++) {
        if (letter_counts[i] > letter_counts[best])
            best = i;
    }
    if (letter_counts[best] == 0)
        printf("Most common letter: none\n");
    else
        printf("Most common letter: %c (%d)\n", 'a' + best, letter_counts[best]);
    return 0;
}
