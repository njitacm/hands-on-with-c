# Challenge 1: Pointers & Addresses

Learn what a pointer really is (just a number that happens to be an address) and use pointers to let functions change your variables and hand back more than one result.

**Difficulty:** Intermediate &nbsp;·&nbsp; **Time:** ~45 min &nbsp;·&nbsp; **Course tie-in:** CS288 Wk 7 (C pointer variables & memory addresses)

## Learning Objectives

- Picture memory as a long row of numbered boxes, and a variable as a name for some of those boxes
- Use `&` to get an address and `*` to follow one, and print addresses with `%p`
- Declare, initialize, and check pointers, including `NULL`
- Write functions that change the caller's variables through pointer parameters (`swap`, out-parameters)
- Explain why `scanf` needs `&`, and why returning the address of a local variable is a bug

> **Trying the snippets:** each example that shows a `$ ./name` run was saved as `name.c` and built with `gcc -std=c11 -Wall -Wextra -o name name.c`. Type them in and run them yourself; drawing the pictures as you go is the best way to make pointers click.

## Memory Is a Row of Numbered Boxes

Your program's memory is one enormous array of **bytes**. Every byte has a number, its **address**. When you declare a variable, the compiler sets aside some of those bytes and lets you use a *name* instead of the number.

```c
int a = 10;     /* an int is 4 bytes on our machines */
int b = 20;
```

```
 address        memory                 name
            ┌───────────────┐
 0x...c8    │      20       │  4 bytes   b
            ├───────────────┤
 0x...cc    │      10       │  4 bytes   a
            └───────────────┘
```

So a variable has **two** things you can ask about:

| Question | C syntax | Example answer |
|----------|----------|----------------|
| What's *in* the box? (its value) | `a` | `10` |
| *Where* is the box? (its address) | `&a` | `0x7fffea0521cc` |

Python and Java hide addresses from you. C hands them to you, which is what makes C both powerful and dangerous.

## `&` and `%p`: Seeing Addresses

The `&` operator ("address of") gives you a variable's address. `printf` prints addresses with `%p`, which expects a `void *` (a "generic pointer", more on that later), so we cast with `(void *)`.

`addresses.c` in this directory does exactly this. Build it and run it:

```bash
$ make run addresses
a  = 10, stored at 0x7fffea0521cc
b  = 20, stored at 0x7fffea0521c8
p  = 0x7fffea0521cc (p points to a)
*p = 10
p itself is stored at 0x7fffea0521c0
after *p = 99:  a = 99
after p = &b; *p = *p + 1:  a = 99, b = 21
sizeof(int) = 4, sizeof(int *) = 8, sizeof(char *) = 8
```

**Your addresses will be different**, and they will probably change every time you run the program. Linux deliberately loads programs at random spots for security (look up *ASLR* if you're curious). What stays the same is the *pattern*: `a` and `b` are 4 bytes apart because an `int` is 4 bytes. The `0x` means the number is in hexadecimal; you'll get comfortable with hex in [Section 3](../../03-data-representation/01-number-systems/).

## Pointers: Variables That Hold Addresses

A **pointer** is just a variable whose value is an address. You declare one by putting `*` before the name:

```c
#include <stdio.h>

int main(void)
{
    int n = 42;
    int *p = &n;        /* p is a "pointer to int"; it holds n's address */

    printf("n  = %d\n", n);
    printf("&n = %p\n", (void *)&n);
    printf("p  = %p\n", (void *)p);
    printf("*p = %d\n", *p);

    *p = 7;             /* write 7 into the box p points at */
    printf("n is now %d\n", n);
    return 0;
}
```

```bash
$ ./decl
n  = 42
&n = 0x7fffc72e8a84
p  = 0x7fffc72e8a84
*p = 42
n is now 7
```

Here's the picture. A pointer is a box too; it just holds an address instead of a regular number. We usually draw that address as an arrow:

```
        p                          n
  ┌────────────────┐         ┌──────────┐
  │ 0x7fffc72e8a84 │ ──────► │    42    │   address 0x7fffc72e8a84
  └────────────────┘         └──────────┘
   int *  (8 bytes)           int (4 bytes)
```

The `*` operator **dereferences** a pointer: "follow the arrow." `*p` *is* `n`, so you can read it (`*p` gives 42) or write it (`*p = 7` changes `n`).

### The two meanings of `*`

This trips up everybody at first:

| Where you see it | Meaning | Example |
|------------------|---------|---------|
| In a **declaration** | "this variable is a pointer" | `int *p;` |
| In an **expression** | "follow the pointer" (dereference) | `*p = 7;` `x = *p + 1;` |
| Between two values | plain old multiplication | `a * b` |

And `&` and `*` undo each other: `*&n` is just `n`.

### Pointer types matter

`int *` points to an `int`, `double *` to a `double`, `char *` to a `char`. The type tells C how many bytes to read when you dereference, and how to interpret them. All pointers are the same *size* on a given machine (8 bytes on 64-bit x86, which you saw in the `sizeof` line above), because an address is an address.

> **Declaration gotcha:** `int *p, q;` makes `p` a pointer but `q` a plain `int`. The `*` sticks to the *name*, not the type. Declare one pointer per line and you'll never get bitten.

## `NULL`: Pointing at Nothing

An uninitialized pointer holds garbage, so it points to some random place. Using it is a bug. When a pointer has nothing to point at yet, set it to `NULL` (defined in `<stdio.h>`, `<stdlib.h>`, and others), a special value that means "no address," and check for it:

```c
#include <stdio.h>

int main(void)
{
    int *p = NULL;
    if (p == NULL)
        printf("p doesn't point anywhere yet\n");
    printf("about to dereference NULL...\n");
    printf("%d\n", *p);
    return 0;
}
```

```bash
$ ./nullp
p doesn't point anywhere yet
about to dereference NULL...
Segmentation fault (core dumped)
```

A **segmentation fault** ("segfault") means your program touched memory it isn't allowed to touch, so the operating system killed it. (The exact wording comes from your shell and may differ.) A segfault on NULL is actually the *lucky* case: it fails loudly, right where the bug is. Dereferencing a garbage pointer might silently corrupt some other variable instead.

Officially, dereferencing NULL is **undefined behavior (UB)**: the C standard says nothing at all about what happens. The program might crash, print nonsense, or appear to work. You'll meet UB a lot in this section; the rule is simply *don't do it*.

## Fixing `swap()`

In [Functions & Scope](../../01-c-fundamentals/04-functions/) you learned that C passes arguments **by value**: a function gets *copies*. That's why a swap function written with plain `int`s can't work. With pointers, it can:

```c
#include <stdio.h>

void swap_values(int a, int b)      /* gets COPIES of x and y */
{
    int tmp = a;
    a = b;
    b = tmp;
}

void swap(int *a, int *b)           /* gets the ADDRESSES of x and y */
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int main(void)
{
    int x = 1, y = 2;
    swap_values(x, y);
    printf("after swap_values: x=%d y=%d\n", x, y);
    swap(&x, &y);
    printf("after swap:        x=%d y=%d\n", x, y);
    return 0;
}
```

```bash
$ ./swaps
after swap_values: x=1 y=2
after swap:        x=2 y=1
```

Look at what each function can see. `swap_values` gets its own boxes and swaps *those*; `main`'s `x` and `y` never change:

```
 main's frame            swap_values's frame
 ┌─────┬─────┐           ┌─────┬─────┐
 │ x 1 │ y 2 │  copied   │ a 2 │ b 1 │   swapped... then thrown away
 └─────┴─────┘  ───────► └─────┴─────┘   when the function returns
```

`swap` gets *arrows* to `main`'s boxes, and `*a` / `*b` reach back through them:

```
 main's frame               swap's frame
 ┌─────────┐                ┌──────────────┐
 │ x   1   │ ◄───────────── │ a  (= &x)    │
 ├─────────┤                ├──────────────┤
 │ y   2   │ ◄───────────── │ b  (= &y)    │
 └─────────┘                ├──────────────┤
                            │ tmp          │
                            └──────────────┘
   *a = *b;  writes into x.     *b = tmp;  writes into y.
```

C is *still* pass-by-value here. `swap` gets copies of two **addresses**. A copy of an address still leads to the same box, and that's the whole trick.

## Out-Parameters: How `scanf` Works

A C function can `return` only one value. When it needs to produce more, the caller passes in *addresses* of variables, and the function writes its results through them. These are called **out-parameters**.

You've already been using one:

```c
scanf("%d", &n);
```

`scanf` has to store the number it reads into *your* variable, so it needs to know *where* `n` is. That's what `&n` gives it. Forget the `&` and the compiler warns you:

```bash
$ gcc -std=c11 -Wall -Wextra -o scanfbug scanfbug.c
scanfbug.c:7:13: warning: format ‘%d’ expects argument of type ‘int *’, but argument 2 has type ‘int’ [-Wformat=]
    7 |     scanf("%d", n);
      |            ~^   ~
      |             |   |
      |             |   int
      |             int *
```

If you run it anyway, `scanf` treats whatever garbage is in `n` as an address and writes there, and the program crashes with a segfault (or worse, doesn't). **Never ignore this warning.** (Arrays are the exception you already know: `scanf("%s", name)` has no `&` because an array name already turns into a pointer. Challenge 2 explains why.)

### Returning multiple values

Here's the pattern you'll use in this challenge's exercises. A function that finds both the smallest and largest value of an array:

```c
void min_max(int arr[], int n, int *min, int *max);

int lo, hi;
min_max(values, 5, &lo, &hi);   /* afterwards, lo and hi hold the answers */
```

A very common C idiom combines the two: **return a success/failure code**, and hand back the actual results through out-parameters. `scanf` itself does this; it returns how many items it read.

```c
int div_mod(int a, int b, int *quot, int *rem);   /* returns 0 if b == 0 */

if (div_mod(17, 5, &q, &r))
    printf("%d remainder %d\n", q, r);
else
    printf("can't divide by zero\n");
```

## Dangling Pointers: Don't Return the Address of a Local

Every time a function is called, its local variables get fresh boxes in a region of memory called the **stack**. When the function returns, those boxes are released and will be reused by the next function call. (You'll see the stack up close in [Section 5](../../05-tools-and-the-machine/05-the-stack/).)

So this is a bug:

```c
char *make_greeting(const char *name)
{
    char buf[64];
    snprintf(buf, sizeof buf, "Hello, %s!", name);
    return buf;     /* BUG: buf dies when this function returns */
}
```

```
  while make_greeting runs          after it returns
  ┌────────────────────┐            ┌────────────────────┐
  │ buf "Hello, ..."   │ ◄── ok     │ (released, will be │ ◄── msg still points here:
  └────────────────────┘            │  reused)           │     a DANGLING pointer
                                    └────────────────────┘
```

The returned pointer is **dangling**: it points to memory that no longer belongs to anything. Using it is undefined behavior. GCC is kind enough to warn you, and it even replaces the returned address with NULL so the bug crashes loudly instead of printing garbage:

```bash
$ make dangling
gcc -std=c11 -Wall -Wextra -g -o dangling dangling.c
dangling.c: In function ‘make_greeting’:
dangling.c:16:12: warning: function returns address of local variable [-Wreturn-local-addr]
   16 |     return buf;     /* BUG: buf dies when this function returns */
      |            ^~~
$ ./dangling
Segmentation fault (core dumped)
```

Other compilers (or a slightly different program) might print the right text, print garbage, or crash later somewhere unrelated. That's what makes UB so nasty. Two safe fixes: let the **caller** own the buffer and pass it in (an out-parameter, Exercise 5), or allocate memory that outlives the function with `malloc` ([Challenge 3](../03-dynamic-memory/)).

The rule: **a pointer is only valid while the thing it points to is still alive.**

<details>
<summary>Compiling without <code>make</code></summary>

`make` just runs these commands for you. To practice compiling by hand, run them yourself from this challenge's directory, then start the program directly (for example `./pointers`):

```bash
# Programs that `make check` tests
gcc -std=c11 -Wall -Wextra -g -o pointers pointers.c

# Other programs in this challenge
gcc -std=c11 -Wall -Wextra -g -o addresses addresses.c
gcc -std=c11 -Wall -Wextra -g -o predict predict.c
gcc -std=c11 -Wall -Wextra -g -o dangling dangling.c    # doesn't compile cleanly yet: that's the exercise
```

</details>

## Exercises

All of Exercises 1-4 are in `pointers.c`. The bottom half of that file is a small test driver that reads commands like `swap 3 5` from stdin and calls your functions; you don't need to change it. You can try it by hand:

```bash
$ make run
swap 3 5
swap: x=3 y=5
```

The first `swap 3 5` is what you typed; the second line is the program's answer (not swapped yet, because `swap` is still empty). Press **Ctrl-D** to end the input and quit.

1. **`swap`** (`pointers.c`, checked by `make check`). Implement `swap(int *a, int *b)`. Then run `make check`. The `swap` test should pass (the others won't yet).

2. **`min_max`** (`pointers.c`, checked). Implement `min_max(arr, n, &min, &max)`. One test includes only negative numbers. If you start `*min` and `*max` at `0`, it will catch you. What should they start at instead?

3. **`div_mod`** (`pointers.c`, checked). Return `0` without touching `*quot` / `*rem` when `b` is `0`; otherwise store both results and return `1`. Notice what C gives for `-7 / 2` and `-7 % 2` in the test output. (C division truncates toward zero.)

4. **`split_time`** (`pointers.c`, checked). Turn a number of seconds into hours, minutes, and seconds through three out-parameters. When all four functions are done, `make check` prints `__SUCCESS__`.

5. **Fix the dangling pointer** (`dangling.c`, not checked). Change `make_greeting` to `void make_greeting(const char *name, char *out, int out_size)` so the caller provides the buffer, and update `main` to match. `make dangling` should build with no warnings and `make run dangling` should print `Hello, Highlander!`.

6. **Draw it** (`addresses.c`, not checked). Run `make run addresses` and, on paper, draw boxes for `a`, `b`, and `p` labeled with *your* addresses. Draw `p`'s arrow before and after `p = &b`. Which direction do the addresses go as you declare more variables? Is `p` stored next to `a` and `b`?

7. **Predict the output** (`predict.c`, not checked). Read `predict.c` and write down what each of the four `printf` lines will print *before* you run it. Draw boxes and arrows as you go. Then `make run predict` and compare. For any puzzle you got wrong, find the exact line where your picture went off.

8. **Bonus:** A pointer is a variable, so it has an address too. Add an `int **pp = &p;` to `addresses.c` (a *pointer to a pointer*) and print `pp`, `*pp`, and `**pp`. Draw the three boxes and two arrows. Then use `**pp = 0;` and check which variable changed. You'll need `**` for real in [Challenge 4](../04-multidimensional-arrays/) and [Challenge 5](../05-command-line-arguments/).

## Checkpoint

You're ready to move on when you can:

- [ ] Explain the difference between a variable's value and its address
- [ ] Read `int *p = &x;` and `*p = 5;` out loud correctly, and say what each `*` means
- [ ] Draw a box-and-arrow diagram for a few lines of pointer code
- [ ] Write a function that returns several results through out-parameters
- [ ] Explain why `scanf` needs `&` and why `swap(int a, int b)` can't work
- [ ] Say why returning the address of a local variable is undefined behavior

## Quick Reference

| Syntax | Description |
|--------|-------------|
| `int *p;` | Declare `p` as a pointer to `int` |
| `p = &x;` | Store the address of `x` in `p` ("`p` points to `x`") |
| `*p` | The thing `p` points to (dereference); readable and writable |
| `int *p = NULL;` | A pointer that deliberately points nowhere |
| `if (p != NULL)` / `if (p)` | Check a pointer before using it |
| `printf("%p", (void *)p);` | Print an address |
| `sizeof(int *)` | Size of a pointer: 8 bytes on 64-bit systems |
| `void f(int *out)` / `f(&x);` | Out-parameter: `f` writes into the caller's `x` via `*out = ...` |
| `int **pp = &p;` | Pointer to a pointer |
| Segmentation fault | The OS killed your program for touching memory it doesn't own |

---

**Previous:** [Arrays & Strings](../../01-c-fundamentals/05-arrays-and-strings/) | **Next:** [Pointer Arithmetic & Arrays](../02-pointer-arithmetic/)
