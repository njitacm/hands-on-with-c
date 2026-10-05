# Challenge 3: Dynamic Memory

Ask for memory while your program is running with `malloc`, give it back with `free`, and build a growable array that can hold as much input as you throw at it.

**Difficulty:** Intermediate &nbsp;·&nbsp; **Time:** ~50 min &nbsp;·&nbsp; **Course tie-in:** CS288 Wk 8 (dynamic variables), CS350 Ch. 9 (dynamic memory allocation)

## Learning Objectives

- Describe the difference between stack memory and heap memory, and when to use each
- Allocate memory with `malloc`, `calloc`, and `realloc`, and release it with `free`
- Check every allocation for `NULL` and use the `sizeof *p` idiom
- Recognize the three classic heap bugs: leaks, double frees, and use-after-free
- Build a dynamic array that doubles its capacity as it grows

> **Trying the snippets:** each example that shows a `$ ./name` run is either a file in this directory (`make name`) or was saved as `name.c` and built with `gcc -std=c11 -Wall -Wextra -o name name.c`. Type them in and run them yourself.

## Why We Need the Heap

So far, every variable you've made has a size fixed when you *compile* and a lifetime tied to a block of code:

- `int nums[100];` is stuck at 100. Ask for 101 numbers and you overflow it; ask for 3 and you waste 97.
- A local variable dies when its function returns. ([Challenge 1](../01-pointers/) showed what happens if you keep a pointer to it.)

Real programs don't know in advance how big their input will be, and they often need data to outlive the function that created it. For that, C gives you the **heap**: a big pool of memory you can request from at run time, in any size, and that stays yours until you explicitly hand it back.

## Where Things Live

A running program's memory is split into regions. `where.c` prints an address from each one:

```bash
$ make run where
code    (main)           0x5be1829b08e4
literal ("hello")        0x5be1829b09d8
global  (global_counter) 0x5be1829d004c
heap    (*heap)          0x5be198150310
stack   (local)          0x7fffc6d74434
stack   (heap, the ptr)  0x7fffc6d74428
```

(Your numbers will differ, but the *order* should match.) Here's the picture, high addresses at the top:

```
 high addresses
 ┌──────────────────────────┐  0x7fff...
 │          stack           │  local variables, function parameters
 │            │             │  one "frame" per active function call;
 │            ▼ grows down  │  freed automatically when the function returns
 │                          │
 │      (unused space)      │
 │                          │
 │            ▲ grows up    │
 │            │             │
 │           heap           │  malloc / calloc / realloc
 │                          │  yours until YOU call free()
 ├──────────────────────────┤
 │  globals & static vars   │  live for the whole program
 ├──────────────────────────┤
 │  read-only data, code    │  string literals, your compiled functions
 └──────────────────────────┘  0x5...
 low addresses
```

Notice the last two lines of output. The *pointer* `heap` is a local variable, so it lives on the stack. The `int` it points to lives on the heap:

```
        STACK                              HEAP
  ┌──────────────────┐               ┌──────────┐
  │ heap  0x5be19... │ ────────────► │    7     │
  └──────────────────┘               └──────────┘
  dies when main returns             lives until free(heap)
```

| | Stack | Heap |
|---|-------|------|
| How you get it | Declare a local variable | Call `malloc` / `calloc` / `realloc` |
| Size | Fixed at compile time | Chosen at run time |
| Lifetime | Until the function returns | Until you call `free` |
| Cleanup | Automatic | **Your job** |
| Speed | Very fast | Slower (the allocator has bookkeeping to do) |
| Typical size limit | ~8 MB total on Linux | Most of your RAM |

CS350 Chapter 9 explains how `malloc` itself works: how the allocator carves up the heap, tracks free blocks, and asks the OS for more.

## `malloc` and `free`

`malloc(n)` (in `<stdlib.h>`) reserves `n` **bytes** on the heap and returns a pointer to the first one. `free(p)` gives them back.

```c
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int n;
    printf("How many squares? ");
    if (scanf("%d", &n) != 1 || n < 1)
        return 1;

    int *sq = malloc(n * sizeof *sq);   /* room for n ints, size chosen at run time */
    if (sq == NULL) {
        fprintf(stderr, "out of memory\n");
        return 1;
    }

    for (int i = 0; i < n; i++)
        sq[i] = i * i;                  /* use it exactly like an array */
    for (int i = 0; i < n; i++)
        printf("%d ", sq[i]);
    printf("\n");

    free(sq);                           /* give it back */
    return 0;
}
```

```bash
$ ./squares
How many squares? 6
0 1 4 9 16 25
```

Three habits to build right now:

1. **Ask for bytes, not elements.** `malloc(n)` gives `n` *bytes*. For `n` ints you need `n * sizeof(int)` bytes.
2. **Use the `sizeof *p` idiom.** Write `malloc(n * sizeof *sq)` rather than `malloc(n * sizeof(int))`. `*sq` is an `int`, so it's the same number, but if you later change `sq` to a `double *`, the size updates by itself.
3. **Always check for `NULL`.** `malloc` returns `NULL` when it can't find enough memory. Using that `NULL` crashes your program (at best).

`malloc`'s return type is `void *`, a "pointer to anything." C converts it to `int *` automatically, so you don't need a cast. (C++ does require one; that's one of the differences you'll see in [Section 6](../../06-going-further/03-from-c-to-cpp/).)

### `calloc`: allocate and zero

`malloc` doesn't clear the memory it gives you; it contains whatever garbage was there before. `calloc(count, size)` allocates `count * size` bytes **and sets them all to zero**:

```c
int *c = calloc(5, sizeof *c);      /* 5 ints, all set to 0 */
```

```bash
$ ./zeros
0 0 0 0 0
```

## `realloc`: Growing a Block

`realloc(p, new_size)` resizes a block you got from `malloc`/`calloc`. It keeps your data, and it may have to **move** the block to a new address to find enough room. Here's a block doubling in size six times:

```c
size_t capacity = 1;
int *a = malloc(capacity * sizeof *a);
...
for (int round = 0; round < 6; round++) {
    capacity *= 2;
    int *bigger = realloc(a, capacity * sizeof *a);
    if (bigger == NULL) {
        free(a);
        return 1;
    }
    printf("capacity %2zu: block at %p%s\n", capacity, (void *)bigger,
           bigger == a ? "" : "  (moved!)");
    a = bigger;
}
free(a);
```

```bash
$ ./grow
capacity  2: block at 0x68edc924c310
capacity  4: block at 0x68edc924c310
capacity  8: block at 0x68edc924e340  (moved!)
capacity 16: block at 0x68edc924e340
capacity 32: block at 0x68edc924e340
capacity 64: block at 0x68edc924e340
```

Two important consequences:

- **After `realloc`, the old pointer may be dead.** Always use the pointer `realloc` returns. Any other pointers into the old block are now dangling.
- **Don't write `a = realloc(a, ...)`.** If `realloc` fails, it returns `NULL` but leaves the old block alone. Assigning straight to `a` throws away your only pointer to that block, and it leaks. Use a temporary (`bigger`) as above.

## The Dynamic Array (a "Vector")

Put those pieces together and you get the most useful data structure in C: an array that grows as needed. You track three things:

```
 nums ──► ┌────┬────┬────┬────┐      count    = 4   (slots in use)
          │ 7  │ 3  │ 9  │ 1  │      capacity = 4   (slots allocated)
          └────┴────┴────┴────┘

 append 4: the array is full (count == capacity), so double it first

 nums ──► ┌────┬────┬────┬────┬────┬────┬────┬────┐  count = 5
          │ 7  │ 3  │ 9  │ 1  │ 4  │    │    │    │  capacity = 8
          └────┴────┴────┴────┴────┴────┴────┴────┘
```

```c
if (count == capacity) {
    size_t new_capacity = capacity * 2;
    int *bigger = realloc(nums, new_capacity * sizeof *bigger);
    if (bigger == NULL) { /* handle it */ }
    nums = bigger;
    capacity = new_capacity;
}
nums[count++] = value;
```

Why *double* instead of adding one slot at a time? Each `realloc` may copy the whole array. Growing by one slot means copying on every append, which is slow for big inputs (quadratic time). Doubling means copies are rare, so appending is fast on average. C++'s `std::vector` and Python's `list` use the same trick.

## The Rules of the Heap (and the Bugs You Get for Breaking Them)

The C runtime trusts you completely. It won't stop you from breaking these rules; your program will just misbehave, sometimes much later and far away from the real bug.

| Rule | Break it and you get... |
|------|--------------------------|
| Every `malloc` gets exactly **one** `free` | **Memory leak** (zero frees) or **double free** (two) |
| Never use memory after you `free` it | **Use-after-free**: reading garbage, or corrupting memory someone else now owns |
| Only `free` what `malloc`/`calloc`/`realloc` gave you | Crash: `free` on a stack array or on `p + 1` corrupts the heap |
| Check for `NULL` before using an allocation | Segfault when memory runs out |
| Stay inside the block's bounds | **Heap buffer overflow**: silently corrupts the allocator's bookkeeping |

A few notes:

- **Leaks** don't crash anything; the memory just stays reserved until the program exits. For a short program that's harmless. For a server that runs for months, leaking a little per request eventually eats all your RAM.
- **`free(NULL)` is allowed** and does nothing. That's handy.
- A good habit after `free(p);` is `p = NULL;`. A NULL pointer can't dangle, and a double `free(NULL)` is harmless.

Here's what a double free looks like when glibc catches it (from `bugs.c`, which you'll fix in Exercise 5):

```bash
$ ./bugs
round 1: last square is 16
round 2: last square is 16
round 3: last square is 16
data[3] is 445576339
free(): double free detected in tcache 2
Aborted (core dumped)
```

Note the garbage `445576339`: that's the use-after-free reading a block that the allocator has already reused for its own bookkeeping. You were lucky that glibc noticed the double free. Many heap bugs produce no error at all, at least not right away. In [Section 5: Finding Memory Bugs](../../05-tools-and-the-machine/03-finding-memory-bugs/) you'll use **Valgrind** and **AddressSanitizer**, tools that catch leaks, double frees, and use-after-free automatically and point at the exact line.

<details>
<summary>Compiling without <code>make</code></summary>

`make` just runs these commands for you. To practice compiling by hand, run them yourself from this challenge's directory, then start the program directly (for example `./stats`):

```bash
# Programs that `make check` tests
gcc -std=c11 -Wall -Wextra -g -o stats stats.c
gcc -std=c11 -Wall -Wextra -g -o tac tac.c

# Other programs in this challenge
gcc -std=c11 -Wall -Wextra -g -o where where.c
gcc -std=c11 -Wall -Wextra -g -o bugs bugs.c
```

</details>

## Exercises

This challenge has two auto-checked programs. `make check stats` and `make check tac` test one program each (`tests/stats/` and `tests/tac/`), which keeps the output short while you work. `make check` runs both test sets and prints `__SUCCESS__` once all of them pass.

1. **Grow the array** (`stats.c`, checked by `make check stats`). Make `stats` read any number of ints into a dynamic array: `malloc` an initial capacity of 4, and double it with `realloc` whenever `count == capacity`. Use a temporary pointer for `realloc`, and check every allocation for `NULL`. Try it with `echo 7 3 9 1 4 7 | make run stats`.

2. **Print the stats** (`stats.c`, checked). Print `sum`, `min`, `max`, `mean` (`%.2f`), and the numbers in reverse, in exactly the format shown at the top of `stats.c`. Keep the sum in a `long long` (one test sums three copies of `INT_MAX`). Careful with the reverse loop: `size_t` can't go negative, so `for (size_t i = count - 1; i >= 0; i--)` loops forever. When all of its tests pass, move on to `tac`.

3. **`my_strdup`** (`tac.c`, checked by `make check tac`). Write `my_strdup(s)`, which returns a new heap copy of the string `s`. How many bytes do you need for a 5-character string?

4. **Fix `tac`** (`tac.c`, checked). Run the starter version first: `printf 'one\ntwo\nthree\n' | make run tac` prints `three` three times. Draw the `lines` array and figure out why every entry shows the same text. Then store `my_strdup(buf)` instead of `buf`, and `free` every line at the end.

5. **Fix the memory bugs** (`bugs.c`, not checked). `bugs.c` has four memory bugs. Find each one, write down which rule from the table it breaks, and fix it. The fixed program should print three rounds, `data[3] is 9`, and `done`, with no warnings from `make bugs`.

6. **Explore** (`where.c`, not checked). Run `make run where` a few times. Which addresses change between runs? Add a second `malloc` and a second local variable and print their addresses. Do the heap addresses go up and the stack addresses go down, like the diagram says?

7. **Predict** (no file). For `int *p = malloc(10);`, how many `int`s fit, on a machine where `sizeof(int)` is 4? What's wrong with `char *s = malloc(strlen(t));` followed by `strcpy(s, t);`?

8. **Bonus:** `tac.c` can only hold `MAX_LINES` lines because `lines` is a fixed-size array of pointers. Replace it with a dynamic array of pointers that doubles like the one in `stats.c`. Its type is `char **lines` (a pointer to the first of many `char *`s), and each slot is `sizeof *lines` bytes. Make sure `make check` still passes. You'll see much more of `**` in the next challenge.

## Checkpoint

You're ready to move on when you can:

- [ ] Draw the stack, heap, globals, and code regions, and say what lives in each
- [ ] Allocate an array of `n` items with `malloc(n * sizeof *p)` and check the result
- [ ] Explain why `p = realloc(p, size)` is risky, and write the safe version
- [ ] Describe a leak, a double free, and a use-after-free, and spot each in code
- [ ] Explain why a growable array doubles its capacity instead of adding one slot

## Quick Reference

| Function / idiom | Description |
|------------------|-------------|
| `#include <stdlib.h>` | Where `malloc`, `calloc`, `realloc`, and `free` live |
| `T *p = malloc(n * sizeof *p);` | Room for `n` items of type `T`; contents are garbage |
| `T *p = calloc(n, sizeof *p);` | Room for `n` items, all bytes set to zero |
| `T *tmp = realloc(p, n * sizeof *p);` | Resize to `n` items; may move the block; `NULL` on failure (old block untouched) |
| `free(p); p = NULL;` | Release the block, then make sure `p` can't dangle |
| `if (p == NULL)` | Check every allocation |
| `free(NULL)` | Allowed; does nothing |
| `count` / `capacity` | Slots used vs. slots allocated in a dynamic array; double capacity when they're equal |
| Leak / double free / use-after-free | Zero frees / two frees / touching memory after its free |

---

**Previous:** [Pointer Arithmetic & Arrays](../02-pointer-arithmetic/) | **Next:** [Multidimensional Arrays](../04-multidimensional-arrays/)
