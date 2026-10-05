/*
 * predict.c -- Exercise 7. 
 *
 * Before running this, write down what you think each printf prints. 
 * 
 * Draw boxes and arrows! Then run:
 *     make run predict
 */

#include <stdio.h>

int main(void)
{
    int x = 5, y = 10;
    int *p = &x;
    int *q = &y;

    /* Puzzle 1 */
    *p = *q + 1;
    printf("1: x=%d y=%d\n", x, y);

    /* Puzzle 2 */
    p = q;
    *p = 7;
    printf("2: x=%d y=%d\n", x, y);

    /* Puzzle 3 */
    q = &x;
    *q = *p * 2;
    printf("3: x=%d y=%d *p=%d *q=%d\n", x, y, *p, *q);

    /* Puzzle 4: is p == q? Do they point at the same place? */
    printf("4: p == q is %d, *p == *q is %d\n", p == q, *p == *q);
    return 0;
}
