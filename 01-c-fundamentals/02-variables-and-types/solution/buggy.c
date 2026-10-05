/*
 * buggy.c -- solution. The five fixes:
 *   1. scanf needs the ADDRESS of c: &c, not c.
 *   2. sum was never initialized, so "sum +=" added to garbage. Start it at 0
 *      (or just write sum = a + b + c).
 *   3. sum / 3 is int / int, which truncates. Divide by 3.0 (or cast sum to
 *      double) to keep the fraction.
 *   4. sum is an int, so print it with %d, not %f.
 *   5. average is a double, so print it with %f (here %.2f), not %d.
 */
#include <stdio.h>

int main(void)
{
    int a, b, c;
    int sum = 0;

    printf("Enter three exam scores: ");
    scanf("%d %d %d", &a, &b, &c);

    sum += a + b + c;
    double average = sum / 3.0;

    printf("Sum: %d\n", sum);
    printf("Average: %.2f\n", average);
    return 0;
}
