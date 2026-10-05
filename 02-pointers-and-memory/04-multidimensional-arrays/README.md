# Challenge 4: Multidimensional Arrays

Build matrices three different ways, see exactly how each one is laid out in memory, and use them to multiply matrices and build Pascal's triangle.

**Difficulty:** Intermediate &nbsp;·&nbsp; **Time:** ~50 min &nbsp;·&nbsp; **Course tie-in:** CS288 Wk 8 (multidimensional arrays, dynamic & pointer-pointer variables), CS350 Ch. 3 (multi-dimensional arrays)

## Learning Objectives

- Explain **row-major** order and compute the address of `m[i][j]` by hand
- Pass a static 2D array to a function, and explain why the column count is required
- Allocate and free a 2D array as an **array of pointers** (`int **`), including jagged rows
- Allocate a matrix as **one block** and index it with `i * cols + j`
- Implement matrix multiplication and transpose

> **Trying the snippets:** each example that shows a `$ ./name` run is either a file in this directory (`make name`) or was saved as `name.c` and built with `gcc -std=c11 -Wall -Wextra -o name name.c`. Type them in and run them yourself.

## Static 2D Arrays

You can declare an array of arrays directly:

```c
int m[3][4] = {
    { 1,  2,  3,  4},
    { 5,  6,  7,  8},
    { 9, 10, 11, 12},
};
```

Read `int m[3][4]` as "`m` is an array of 3 things, and each thing is an array of 4 `int`s." So `m[1]` is a whole row, and `m[1][2]` is the element in row 1, column 2 (which is `7`).

We *think* of it as a grid:

```
          col 0  col 1  col 2  col 3
 row 0  [   1      2      3      4  ]
 row 1  [   5      6      7      8  ]
 row 2  [   9     10     11     12  ]
```

But memory is one-dimensional: just a row of numbered boxes. So C lays the rows out **one after another**. This is called **row-major order**:

```
 offset:  0    4    8    12   16   20   24   28   32   36   40   44
        ┌────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┐
        │ 1  │ 2  │ 3  │ 4  │ 5  │ 6  │ 7  │ 8  │ 9  │ 10 │ 11 │ 12 │
        └────┴────┴────┴────┴────┴────┴────┴────┴────┴────┴────┴────┘
        └────── row 0 ──────┘└────── row 1 ──────┘└────── row 2 ──────┘
```

`layout.c` proves it by printing the address of every element:

```bash
$ make run layout
   1   2   3   4
   5   6   7   8
   9  10  11  12

sizeof(m)    = 48 bytes (the whole matrix)
sizeof(m[0]) = 16 bytes (one row)

element    address         offset from m[0][0]
m[0][0]    0x7fffcc24d480    0 bytes
m[0][1]    0x7fffcc24d484    4 bytes
m[0][2]    0x7fffcc24d488    8 bytes
m[0][3]    0x7fffcc24d48c   12 bytes
m[1][0]    0x7fffcc24d490   16 bytes
m[1][1]    0x7fffcc24d494   20 bytes
m[1][2]    0x7fffcc24d498   24 bytes
m[1][3]    0x7fffcc24d49c   28 bytes
m[2][0]    0x7fffcc24d4a0   32 bytes
m[2][1]    0x7fffcc24d4a4   36 bytes
m[2][2]    0x7fffcc24d4a8   40 bytes
m[2][3]    0x7fffcc24d4ac   44 bytes
```

`m[0][3]` and `m[1][0]` are right next to each other: no gaps between rows.

### The address formula

For an array declared `T m[R][C]`:

```
&m[i][j]  ==  (start of m)  +  (i * C + j) * sizeof(T)
```

Skip `i` full rows of `C` elements each, then `j` more elements. Check it: `m[2][1]` should be at `(2 * 4 + 1) * 4 = 36` bytes, which matches the output. Notice the formula needs `C` (the number of columns) but **not** `R`. This is exactly the address arithmetic the compiler generates for `m[i][j]`. CS350 Chapter 3 shows it in x86 assembly, and you'll do that yourself in [Section 5](../../05-tools-and-the-machine/04-c-to-assembly/).

## Passing a 2D Array to a Function

Since the formula needs the column count, so does any function that takes a 2D array:

```c
void print_matrix(int rows, int m[][COLS])   /* COLS is required, rows is not */
```

Leave the column count out and the compiler refuses, because it couldn't compute `m[i][j]`:

```bash
$ gcc -std=c11 -Wall -Wextra -c nocols.c
nocols.c:1:33: error: array type has incomplete element type ‘int[]’
    1 | void print_matrix(int rows, int m[][])
      |                                 ^
nocols.c:1:33: note: declaration of ‘m’ as multidimensional array must have bounds for all dimensions except the first
```

Just like a 1D array, a 2D array decays to a pointer to its first element when you pass it. Its first element is a whole *row*, so `m` becomes a "pointer to an array of 4 ints," written `int (*)[4]`. That's **not** the same as `int **`, and mixing them up is a common bug:

```bash
$ gcc -std=c11 -Wall -Wextra -o wrongtype wrongtype.c
wrongtype.c: In function ‘main’:
wrongtype.c:6:10: error: passing argument 1 of ‘show’ from incompatible pointer type [-Wincompatible-pointer-types]
    6 |     show(grid);
      |          ^~~~
      |          |
      |          int (*)[2]
wrongtype.c:2:17: note: expected ‘int **’ but argument is of type ‘int (*)[2]’
```

(GCC 14 and newer make this an error. Older versions only *warn*, and the program then crashes when it runs. Never ignore this warning.)

The catch with static 2D arrays: the column count is baked in at compile time. To choose the size while the program runs, you need the heap, and there are two good ways to do it.

## Way 1: An Array of Pointers (`int **`)

Allocate an array of row pointers, then allocate each row separately:

```c
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int rows = 3, cols = 4;

    /* Step 1: an array of `rows` pointers, one per row */
    int **m = malloc(rows * sizeof *m);
    if (m == NULL)
        return 1;

    /* Step 2: each row is its own block of `cols` ints */
    for (int i = 0; i < rows; i++) {
        m[i] = malloc(cols * sizeof *m[i]);
        if (m[i] == NULL)
            return 1;   /* (a real program would free what it already made) */
        for (int j = 0; j < cols; j++)
            m[i][j] = 10 * i + j;
    }

    for (int i = 0; i < rows; i++)
        printf("m[%d] = %p   m[%d][3] = %d\n", i, (void *)m[i], i, m[i][3]);

    /* Free in reverse: rows first, then the array of row pointers */
    for (int i = 0; i < rows; i++)
        free(m[i]);
    free(m);
    return 0;
}
```

```bash
$ ./rows
m[0] = 0x5840a2d60330   m[0][3] = 3
m[1] = 0x5840a2d60350   m[1][3] = 13
m[2] = 0x5840a2d60370   m[2][3] = 23
```

Here's what you built. `m` is a **pointer to a pointer**: it points at the first of three `int *`s, and each of those points at a row:

```
   m                  array of row pointers         the rows
 ┌─────┐             ┌────────┐                ┌────┬────┬────┬────┐
 │  ●──┼───────────► │ m[0] ●─┼──────────────► │  0 │  1 │  2 │  3 │
 └─────┘             ├────────┤                └────┴────┴────┴────┘
  int **             │ m[1] ●─┼───────────┐    ┌────┬────┬────┬────┐
  (stack)            ├────────┤           └──► │ 10 │ 11 │ 12 │ 13 │
                     │ m[2] ●─┼────────┐       └────┴────┴────┴────┘
                     └────────┘        │       ┌────┬────┬────┬────┐
                      3 x int *        └─────► │ 20 │ 21 │ 22 │ 23 │
                      (1 heap block)           └────┴────┴────┴────┘
                                                4 x int each (3 more heap blocks)
```

`m[i][j]` now means *two* pointer lookups: `m[i]` follows `m` to get row `i`'s pointer, and `[j]` follows that to the element. The syntax looks identical to a static 2D array, but the memory underneath is completely different.

Look at the addresses: each row is 32 bytes after the previous one, even though a row only needs 16. The rows are separate blocks, and `malloc` adds its own bookkeeping between them. **The rows are not guaranteed to be contiguous or even in order.**

Two big advantages of this layout:

- **Jagged arrays:** every row can have a *different length*. Pascal's triangle (Exercise 3) needs exactly that: row `i` has `i + 1` numbers.
- **Swapping rows is cheap:** swap two pointers instead of copying whole rows.

And the costs: `rows + 1` calls to `malloc` (each of which can fail), `rows + 1` calls to `free` in the right order, and rows scattered around memory.

> **Free order matters.** Free the rows *before* the array of row pointers. If you `free(m)` first, the pointers to the rows are gone, and so is your only way to free them: a leak (and reading `m[i]` after `free(m)` would be a use-after-free).

## Way 2: One Block and Index Math

Alternatively, allocate all `rows * cols` elements as one block and do the row-major math yourself:

```c
int rows = 3, cols = 4;
int *m = malloc(rows * cols * sizeof *m);   /* ONE block for everything */
if (m == NULL)
    return 1;

for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++)
        m[i * cols + j] = 10 * i + j;       /* (i, j) lives at i*cols + j */
...
free(m);                                    /* ONE free */
```

```bash
$ ./block
  0  1  2  3
 10 11 12 13
 20 21 22 23
```

```
 m ──► ┌────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┐
       │  0 │  1 │  2 │  3 │ 10 │ 11 │ 12 │ 13 │ 20 │ 21 │ 22 │ 23 │
       └────┴────┴────┴────┴────┴────┴────┴────┴────┴────┴────┴────┘
 index:  0    1    2    3    4    5    6    7    8    9    10   11
                                       ▲
                              m[1 * 4 + 2] = m[6] = 12
```

That's the same layout as a static 2D array, with the size chosen at run time. One `malloc`, one `free`, and all the data sits together in memory, which turns out to make it *faster* (you'll measure why in [Caches & Locality](../../05-tools-and-the-machine/06-caches-and-locality/), CS350 Chapter 6). The price is writing `i * cols + j` everywhere, and every row must be the same length.

| | Static `int m[R][C]` | Array of pointers `int **` | One block `int *` |
|---|---|---|---|
| Size chosen at | Compile time | Run time | Run time |
| Access syntax | `m[i][j]` | `m[i][j]` | `m[i * cols + j]` |
| Memory | Contiguous | Rows scattered | Contiguous |
| `malloc` / `free` calls | 0 | `rows + 1` | 1 |
| Jagged rows | No | **Yes** | No |
| Function parameter | `int m[][C]` | `int **m` | `int *m` (+ `cols`) |

## Matrix Operations

With any of these layouts, the classic matrix operations are a couple of nested loops.

**Add** (`A` and `B` both `R x C`): `C[i][j] = A[i][j] + B[i][j]` for every `i`, `j`.

**Transpose** (`A` is `R x C`, result is `C x R`): rows become columns, so `T[j][i] = A[i][j]`.

**Multiply** (`A` is `n x m`, `B` is `m x p`, result is `n x p`): entry `(i, j)` of the product is the dot product of **row `i` of `A`** and **column `j` of `B`**:

```
     A (2x3)            B (3x2)           C = A x B (2x2)

  [ 1  2  3 ]         [  7   8 ]          [  58   64 ]
  [ 4  5  6 ]    x    [  9  10 ]    =     [ 139  154 ]
                      [ 11  12 ]

  C[0][0] = (row 0 of A) . (column 0 of B) = 1*7 + 2*9 + 3*11 = 58
```

```c
for (int i = 0; i < n; i++)
    for (int j = 0; j < p; j++) {
        int sum = 0;
        for (int k = 0; k < m; k++)
            sum += A[i][k] * B[k][j];
        C[i][j] = sum;
    }
```

The inner dimensions have to match: `A`'s column count (`m`) must equal `B`'s row count. A `2x3` times a `2x3` is undefined, so your program should refuse it.

<details>
<summary>Compiling without <code>make</code></summary>

`make` just runs these commands for you. To practice compiling by hand, run them yourself from this challenge's directory, then start the program directly (for example `./matmul`):

```bash
# Programs that `make check` tests
gcc -std=c11 -Wall -Wextra -g -o matmul matmul.c
gcc -std=c11 -Wall -Wextra -g -o pascal pascal.c

# Other programs in this challenge
gcc -std=c11 -Wall -Wextra -g -o layout layout.c
```

</details>

## Exercises

Exercises 1-3 are auto-checked. `make check matmul` and `make check pascal` test one program each (`tests/matmul/` and `tests/pascal/`); `make check` runs both and prints `__SUCCESS__` once all of them pass.

1. **Multiply** (`matmul.c`, checked by `make check matmul`). `matmul` reads two matrices from stdin (format at the top of the file) into single-block arrays; `read_matrix` is already written, so read it first. Implement `multiply` using `i * cols + j` indexing. Watch which `cols` goes with which matrix: `a` has `m` columns, `b` and `c` have `p`.

2. **Print** (`matmul.c`, checked). Implement `print_matrix`: one row per line, values separated by single spaces. Then `make run matmul` multiplies the matrices in `sample.txt` and should print `58 64` and `139 154`. Try `./matmul < tests/matmul/mismatch.in` too: the error goes to stderr and the exit code is 1 (`echo $?`).

3. **Pascal's triangle** (`pascal.c`, checked by `make check pascal`). Implement `build_triangle(n)` as a jagged `int **` (row `i` has `i + 1` ints) and `free_triangle`. If any row's `malloc` fails, free what you've already built before returning `NULL`. Try `echo 6 | make run pascal`.

4. **Predict** (`layout.c`, not checked). Without running anything: in `int grid[5][7];` (4-byte ints), what's the byte offset of `grid[3][2]`? Of `grid[4][6]`? What's `sizeof(grid[2])`? Check your answers by changing `layout.c`.

5. **Transpose** (`layout.c`, not checked). Write `transpose(rows, src, dst)` as described in the TODO and print the 4x3 result. You should get `1 5 9` / `2 6 10` / `3 7 11` / `4 8 12`.

6. **Draw it** (no file). Draw the memory diagram for a jagged triangle with 4 rows, like the `int **` picture above. Count the `malloc` calls. Then write the code to free it, and explain what goes wrong if you `free(tri)` first.

7. **Experiment** (`matmul.c`, not checked). Add a `transpose` for the single-block layout (`t[j * rows + i] = m[i * cols + j]`). Use it to print the transpose of `B`, then check on the sample input that transpose(A x B) equals transpose(B) x transpose(A). Remove the extra output before running `make check` again.

8. **Bonus:** Rewrite `matmul.c` to use `int **` matrices instead of single blocks (you'll need `alloc_matrix(rows, cols)` and `free_matrix(m, rows)` helpers). `make check` should still pass. Which version was easier to write? Which one would you rather debug? Which would you guess is faster on a 1000x1000 matrix? (You'll find out in Section 5.)

## Checkpoint

You're ready to move on when you can:

- [ ] Draw `int m[2][3]` in memory and say where `m[1][0]` is
- [ ] Use the formula `start + (i * C + j) * sizeof(T)` to find any element
- [ ] Explain why `void f(int m[][])` doesn't compile and why `int m[2][3]` can't be passed as `int **`
- [ ] Allocate and free a jagged `int **` array in the right order
- [ ] Allocate a single-block matrix and access element `(i, j)` correctly
- [ ] Multiply two matrices and check that their dimensions are compatible

## Quick Reference

| Syntax | Description |
|--------|-------------|
| `int m[R][C];` | Static 2D array: `R` rows of `C` ints, row-major, contiguous |
| `&m[i][j]` | `start + (i * C + j) * sizeof(int)` |
| `void f(int m[][C], int rows)` | Pass a static 2D array (columns required) |
| `int **m = malloc(rows * sizeof *m);` | Array of row pointers |
| `m[i] = malloc(cols * sizeof *m[i]);` | One row (can be a different length per row: jagged) |
| `for (i...) free(m[i]); free(m);` | Free rows first, then the row-pointer array |
| `int *m = malloc(rows * cols * sizeof *m);` | Single-block matrix |
| `m[i * cols + j]` | Element `(i, j)` of a single-block matrix |
| `int (*)[C]` vs. `int **` | Pointer to a row of `C` ints vs. pointer to a pointer: not interchangeable |

---

**Previous:** [Dynamic Memory](../03-dynamic-memory/) | **Next:** [Command-Line Arguments](../05-command-line-arguments/)
