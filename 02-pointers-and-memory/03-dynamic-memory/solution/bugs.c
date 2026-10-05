/*
 * bugs.c -- solution (Exercise 5). The four bugs were:
 *
 *   1. make_squares never checked malloc's result for NULL.
 *   2. Memory leak: each round's array was never freed, so three blocks were
 *      lost for good once `sq` went out of scope.
 *   3. Use-after-free: data[3] was read AFTER free(data). The block no longer
 *      belongs to us; reading it is undefined behavior.
 *   4. Double free: data was freed a second time, which corrupts the heap
 *      (glibc notices and aborts the program).
 */
#include <stdio.h>
#include <stdlib.h>

/* Return a new array holding 0, 1, 4, 9, ... (n squares), or NULL. */
int *make_squares(int n)
{
    int *a = malloc(n * sizeof *a);
    if (a == NULL)                              /* fix 1 */
        return NULL;
    for (int i = 0; i < n; i++)
        a[i] = i * i;
    return a;
}

int main(void)
{
    for (int round = 1; round <= 3; round++) {
        int *sq = make_squares(5);
        if (sq == NULL) {
            fprintf(stderr, "out of memory\n");
            return 1;
        }
        printf("round %d: last square is %d\n", round, sq[4]);
        free(sq);                               /* fix 2 */
    }

    int *data = make_squares(4);
    if (data == NULL) {
        fprintf(stderr, "out of memory\n");
        return 1;
    }
    printf("data[3] is %d\n", data[3]);         /* fix 3: use it BEFORE freeing */
    free(data);                                 /* fix 4: free it exactly once */
    data = NULL;                                /* a NULL can't dangle */

    printf("done\n");
    return 0;
}
