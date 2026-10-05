/*
 * stats.c -- Exercises 1 and 2.
 *
 * Read ANY number of ints from stdin (until end of input) into a dynamic
 * array that doubles its capacity whenever it fills up. Then print:
 *
 *     count: 6
 *     sum: 31
 *     min: 1
 *     max: 9
 *     mean: 5.17
 *     reversed: 7 4 1 9 3 7
 *
 * If there are no numbers at all, print only the "count: 0" line.
 *
 * Try it:
 *     echo 7 3 9 1 4 7 | make run stats
 *
 * Test it:
 *     make check stats
 */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    size_t count = 0;       /* how many ints are stored */
    size_t capacity = 4;    /* how many ints fit in the current block */
    int *nums = NULL;

    /* TODO (Exercise 1): malloc room for `capacity` ints (use the
     * sizeof *nums idiom) and handle a NULL result. */

    int value;
    while (scanf("%d", &value) == 1) {
        /* TODO (Exercise 1): if the array is full (count == capacity),
         * double capacity with realloc. Assign realloc's result to a
         * TEMPORARY pointer first and check it for NULL. */

        /* TODO (Exercise 1): store value at the end and bump count. */
    }

    printf("count: %zu\n", count);

    /* TODO (Exercise 2): if count > 0, print sum, min, max, mean (with %.2f),
     * and the numbers in reverse order, exactly as shown above.
     * Keep the sum in a long long: one of the tests adds three copies of
     * the largest possible int. */

    (void)capacity;         /* delete this line once you use capacity */
    free(nums);             /* free(NULL) is allowed and does nothing */
    return 0;
}
