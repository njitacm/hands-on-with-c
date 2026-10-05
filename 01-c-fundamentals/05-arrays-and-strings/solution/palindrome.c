/*
 * palindrome.c -- solution for Exercise 2.
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_LINE 256

/* Reverse s in place by swapping characters from both ends inward. */
void reverse(char s[])
{
    int i = 0;
    int j = strlen(s) - 1;

    while (i < j) {
        char tmp = s[i];
        s[i] = s[j];
        s[j] = tmp;
        i++;
        j--;
    }
}

/* true if s reads the same forwards and backwards, looking only at
 * letters and digits and ignoring case. */
bool is_palindrome(const char s[])
{
    int i = 0;
    int j = strlen(s) - 1;

    while (i < j) {
        if (!isalnum((unsigned char) s[i])) {
            i++;
        } else if (!isalnum((unsigned char) s[j])) {
            j--;
        } else {
            if (tolower((unsigned char) s[i]) != tolower((unsigned char) s[j]))
                return false;
            i++;
            j--;
        }
    }
    return true;
}

int main(void)
{
    char line[MAX_LINE];
    char backwards[MAX_LINE];

    while (fgets(line, sizeof(line), stdin) != NULL) {
        line[strcspn(line, "\n")] = '\0';

        /* reverse() changes its argument, so work on a copy. backwards is
         * the same size as line, so strcpy can't overflow it. */
        strcpy(backwards, line);
        reverse(backwards);

        printf("\"%s\" reversed is \"%s\" -> %s\n", line, backwards,
               is_palindrome(line) ? "palindrome" : "not a palindrome");
    }
    return 0;
}
