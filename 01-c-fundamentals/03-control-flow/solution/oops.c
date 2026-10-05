/*
 * oops.c -- solution. The four fixes:
 *   1. 0 <= score <= 100 means (0 <= score) <= 100, and (0 <= score) is
 *      0 or 1, which is always <= 100. Use && to combine two comparisons.
 *   2. score = 100 ASSIGNS 100 (and the result, 100, is true). Use ==.
 *   3. case 'A' had no break, so it fell through into case 'B'.
 *   4. The ; right after the for(...) is an empty loop body. The block
 *      below it ran exactly once, after the loop finished.
 */
#include <stdio.h>

int main(void)
{
    int score;

    printf("Score (0-100): ");
    if (scanf("%d", &score) != 1)
        return 1;

    if (0 <= score && score <= 100) {
        printf("Valid score.\n");
    } else {
        printf("Score must be between 0 and 100.\n");
        return 1;
    }

    if (score == 100)
        printf("Perfect score!\n");

    char letter;
    if (score >= 90)
        letter = 'A';
    else if (score >= 80)
        letter = 'B';
    else
        letter = 'C';

    switch (letter) {
    case 'A':
        printf("Excellent\n");
        break;
    case 'B':
        printf("Good\n");
        break;
    default:
        printf("Keep practicing\n");
        break;
    }

    for (int i = 0; i < 3; i++) {
        printf("Hip hip hooray!\n");
    }
    return 0;
}
