/*
 * oops.c -- Exercise 4: four classic control-flow bugs.
 *
 * This program compiles, but it's wrong in four places, and every one of
 * them is a mistake that real programmers make. 
 *
 * Build it with:
 *     make oops
 * and let the warnings guide you. 
 *
 * When it's fixed, it builds with zero warnings and should print:
 *
 *     $ echo 85 | ./oops
 *     Score (0-100): Valid score.
 *     Good
 *     Hip hip hooray!
 *     Hip hip hooray!
 *     Hip hip hooray!
 *
 *     $ echo 150 | ./oops
 *     Score (0-100): Score must be between 0 and 100.
 */

#include <stdio.h>

int main(void)
{
    int score;

    printf("Score (0-100): ");
    if (scanf("%d", &score) != 1)
        return 1;

    if (0 <= score <= 100) {
        printf("Valid score.\n");
    } else {
        printf("Score must be between 0 and 100.\n");
        return 1;
    }

    if (score = 100)
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
    case 'B':
        printf("Good\n");
        break;
    default:
        printf("Keep practicing\n");
        break;
    }

    for (int i = 0; i < 3; i++);
    {
        printf("Hip hip hooray!\n");
    }
    return 0;
}
