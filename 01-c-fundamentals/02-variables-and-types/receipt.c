/*
 * Challenge 2: Variables, Types & printf
 *
 * Exercise 2: read "subtotal tip_percent people" from stdin and print a
 * receipt that splits the bill evenly. For the input  84.50 18 4  the
 * output must be EXACTLY:
 *
 *     Subtotal:   $   84.50
 *     Tax:        $    5.60
 *     Tip (18%):  $   15.21
 *     Total:      $  105.31
 *     Per person (4): $26.32
 *     Leftover cents: 3
 *
 * Try it:
 *     echo "84.50 18 4" | make run receipt
 *
 * Test it:
 *     make check receipt
 */

#include <stdio.h>

/* TODO (Exercise 2): #define TAX_RATE as New Jersey's sales tax, 6.625%
 * (written as a decimal, 0.06625). */

int main(void)
{
    double subtotal;
    int tip_percent;
    int people;

    /* TODO: read subtotal, tip_percent, and people with ONE scanf call.
     * Remember: %lf reads a double, %d reads an int, and every variable
     * needs an & in front of it. */

    /* TODO: compute tax (subtotal * TAX_RATE), tip (tip_percent percent
     * of the subtotal -- watch out for integer division), and total. */

    /* TODO: convert the total to a whole number of cents, ROUNDED to the
     * nearest cent:  long cents = (long) (total * 100 + 0.5);
     * Then use / and % to split the cents among the people. */

    /* TODO: print the six lines shown above. Hints:
     *   - %8.2f prints a double in a field 8 characters wide, 2 decimals
     *   - %% prints a literal percent sign
     *   - %2d pads the tip percent to 2 characters: "Tip ( 5%)"
     *   - to print 2632 cents as 26.32, print cents / 100 and cents % 100,
     *     using %02ld for the second part so 5 cents shows as "05" */

    return 0;
}
