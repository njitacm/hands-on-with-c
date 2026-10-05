/*
 * buggy.c -- averages three exam scores... or tries to.
 *
 * Exercise 4: this program has FIVE bugs. Some of them -Wall will point
 * out for you; one of them it won't. 
 *
 * Try building it:
 *     make buggy
 *
 * When it's fixed, it should output:
 *     $ echo "90 85 88" | ./buggy
 *     Enter three exam scores: Sum: 263
 *     Average: 87.67
 */

#include <stdio.h>

int main(void)
{
    int a, b, c;
    int sum;

    printf("Enter three exam scores: ");
    scanf("%d %d %d", &a, &b, c);

    sum += a + b + c;
    double average = sum / 3;

    printf("Sum: %f\n", sum);
    printf("Average: %d\n", average);
    return 0;
}
