/*
 * Challenge 2: Variables, Types & printf -- solution
 *
 * Reads "subtotal tip_percent people" from stdin and prints a receipt
 * that splits the bill evenly.
 */
#include <stdio.h>

#define TAX_RATE 0.06625    /* New Jersey sales tax (6.625%) */

int main(void)
{
    double subtotal;
    int tip_percent;
    int people;

    if (scanf("%lf %d %d", &subtotal, &tip_percent, &people) != 3) {
        printf("Expected: subtotal tip_percent people\n");
        return 1;
    }

    double tax = subtotal * TAX_RATE;
    /* 100.0, not 100: with an int on both sides, 18 / 100 would be 0. */
    double tip = subtotal * tip_percent / 100.0;
    double total = subtotal + tax + tip;

    /* Money is easier to split exactly in whole cents. Adding 0.5 before
     * the cast rounds to the nearest cent instead of chopping it off. */
    long cents = (long) (total * 100 + 0.5);
    long each = cents / people;
    long leftover = cents % people;

    printf("Subtotal:   $%8.2f\n", subtotal);
    printf("Tax:        $%8.2f\n", tax);
    printf("Tip (%2d%%):  $%8.2f\n", tip_percent, tip);
    printf("Total:      $%8.2f\n", cents / 100.0);
    printf("Per person (%d): $%ld.%02ld\n", people, each / 100, each % 100);
    printf("Leftover cents: %ld\n", leftover);
    return 0;
}
