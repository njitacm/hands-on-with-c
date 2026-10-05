/*
 * Challenge 1: Pointers & Addresses -- solution
 *
 * Every function here "returns" its answers through pointer parameters
 * (out-parameters), because a C function can only return one value.
 */
#include <stdio.h>
#include <string.h>

/* Exercise 1: swap the two ints that a and b point to. */
void swap(int *a, int *b)
{
    int tmp = *a;   /* save the value a points to */
    *a = *b;        /* overwrite it with the value b points to */
    *b = tmp;       /* put the saved value where b points */
}

/* Exercise 2: find the smallest and largest of arr[0..n-1] (n >= 1). */
void min_max(int arr[], int n, int *min, int *max)
{
    /* Start from the first element, not 0: the array might be all negative. */
    *min = arr[0];
    *max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < *min)
            *min = arr[i];
        if (arr[i] > *max)
            *max = arr[i];
    }
}

/*
 * Exercise 3: divide a by b. Store the quotient in *quot and the remainder
 * in *rem and return 1. If b is 0, leave *quot and *rem alone and return 0.
 */
int div_mod(int a, int b, int *quot, int *rem)
{
    if (b == 0)
        return 0;   /* the return value reports success; the answers go out via pointers */
    *quot = a / b;
    *rem = a % b;
    return 1;
}

/* Exercise 4: split a number of seconds into hours, minutes, and seconds. */
void split_time(int total, int *hours, int *minutes, int *seconds)
{
    *hours = total / 3600;
    *minutes = (total % 3600) / 60;
    *seconds = total % 60;
}

/* ------------------------------------------------------------------------
 * Test driver. You don't need to change anything below this line.
 *
 * It reads commands from stdin, one per line:
 *     swap A B
 *     minmax N V1 V2 ... VN
 *     divmod A B
 *     time SECONDS
 * ------------------------------------------------------------------------ */
#define MAX_VALUES 100

int main(void)
{
    char cmd[16];

    while (scanf("%15s", cmd) == 1) {
        if (strcmp(cmd, "swap") == 0) {
            int x, y;
            if (scanf("%d %d", &x, &y) != 2)
                break;
            swap(&x, &y);
            printf("swap: x=%d y=%d\n", x, y);
        } else if (strcmp(cmd, "minmax") == 0) {
            int n, values[MAX_VALUES];
            if (scanf("%d", &n) != 1 || n < 1 || n > MAX_VALUES)
                break;
            for (int i = 0; i < n; i++)
                if (scanf("%d", &values[i]) != 1)
                    return 1;
            int lo = 0, hi = 0;
            min_max(values, n, &lo, &hi);
            printf("minmax: min=%d max=%d\n", lo, hi);
        } else if (strcmp(cmd, "divmod") == 0) {
            int a, b, q = 0, r = 0;
            if (scanf("%d %d", &a, &b) != 2)
                break;
            if (div_mod(a, b, &q, &r))
                printf("divmod: %d / %d = %d remainder %d\n", a, b, q, r);
            else
                printf("divmod: %d / %d is undefined\n", a, b);
        } else if (strcmp(cmd, "time") == 0) {
            int total, h = 0, m = 0, s = 0;
            if (scanf("%d", &total) != 1)
                break;
            split_time(total, &h, &m, &s);
            printf("time: %d s = %dh %02dm %02ds\n", total, h, m, s);
        } else {
            printf("unknown command: %s\n", cmd);
            return 1;
        }
    }
    return 0;
}
