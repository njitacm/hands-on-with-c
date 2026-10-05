/*
 * stats.c -- solution (Exercises 1 and 2).
 *
 * Reads any number of ints from stdin into a dynamic array that doubles its
 * capacity whenever it fills up, then prints some statistics and the numbers
 * in reverse order.
 */
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    size_t count = 0;
    size_t capacity = 4;
    int *nums = malloc(capacity * sizeof *nums);
    if (nums == NULL) {
        fprintf(stderr, "stats: out of memory\n");
        return 1;
    }

    int value;
    while (scanf("%d", &value) == 1) {
        if (count == capacity) {
            /* Full: double the capacity. Use a temporary so that if realloc
             * fails we still have (and can free) the old block. */
            size_t new_capacity = capacity * 2;
            int *bigger = realloc(nums, new_capacity * sizeof *bigger);
            if (bigger == NULL) {
                fprintf(stderr, "stats: out of memory\n");
                free(nums);
                return 1;
            }
            nums = bigger;
            capacity = new_capacity;
        }
        nums[count++] = value;
    }

    printf("count: %zu\n", count);
    if (count > 0) {
        long long sum = 0;
        int min = nums[0], max = nums[0];
        for (size_t i = 0; i < count; i++) {
            sum += nums[i];
            if (nums[i] < min)
                min = nums[i];
            if (nums[i] > max)
                max = nums[i];
        }
        printf("sum: %lld\n", sum);
        printf("min: %d\n", min);
        printf("max: %d\n", max);
        printf("mean: %.2f\n", (double)sum / count);

        printf("reversed:");
        for (size_t i = count; i > 0; i--)     /* i > 0, not i >= 0: size_t is never negative */
            printf(" %d", nums[i - 1]);
        printf("\n");
    }

    free(nums);
    return 0;
}
