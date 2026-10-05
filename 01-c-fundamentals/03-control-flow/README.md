# Challenge 3: Control Flow

Make your programs decide and repeat with `if`, `switch`, and C's three loops, and learn the handful of control-flow bugs that bite every C beginner.

**Difficulty:** Beginner &nbsp;·&nbsp; **Time:** ~45 min &nbsp;·&nbsp; **Course tie-in:** CS350 Ch. 3 (jumps, branches, loops, and `switch` at the machine level, previewed in [Section 5](../../05-tools-and-the-machine/04-c-to-assembly/))

## Learning Objectives

- Write conditions with comparison and logical operators, and explain how C decides what's "true"
- Use `bool` from `<stdbool.h>`
- Choose between `if`/`else if` and `switch`, and use (or avoid) `switch` fallthrough on purpose
- Write `while`, `for`, and `do`-`while` loops, and steer them with `break` and `continue`
- Build patterns with nested loops
- Recognize the `=` vs `==` bug and other mistakes that `-Wall -Wextra` can catch for you

## Truth in C: Zero Is False

You already know `if` and loops from Python or Java. The big C difference is what counts as "true." A condition in C is just a number. (C99 added a `_Bool` type, but conditions still work on plain numbers.) The rule is:

> **Zero is false. Every other value is true.**

Comparison (`==`, `!=`, `<`, `<=`, `>`, `>=`) and logical (`&&`, `||`, `!`) operators produce an `int`: `1` for true and `0` for false.

```c
#include <stdio.h>
#include <stdbool.h>

int main(void)
{
    int x = 5;
    printf("x > 3      -> %d\n", x > 3);
    printf("x == 4     -> %d\n", x == 4);
    printf("!x         -> %d\n", !x);
    printf("x && 0     -> %d\n", x && 0);
    printf("x || 0     -> %d\n", x || 0);

    if (x)
        printf("5 counts as true\n");
    if (-1)
        printf("-1 counts as true\n");
    if (0)
        printf("you will never see this\n");

    bool done = false;
    printf("done = %d, !done = %d\n", done, !done);
    return 0;
}
```

```bash
$ ./truth
x > 3      -> 1
x == 4     -> 0
!x         -> 0
x && 0     -> 0
x || 0     -> 1
5 counts as true
-1 counts as true
done = 0, !done = 1
```

`#include <stdbool.h>` gives you the type `bool` and the constants `true` (1) and `false` (0). Use `bool` whenever a variable means yes/no; it makes your intent obvious.

| Python | Java | C |
|--------|------|---|
| `and`, `or`, `not` | `&&`, `\|\|`, `!` | `&&`, `\|\|`, `!` |
| `True`, `False` | `true`, `false` | `true`, `false` (with `<stdbool.h>`), or just `1` and `0` |
| `0 <= x <= 100` works | doesn't compile | compiles, but is **wrong** (see Exercise 4) |

`&&` and `||` **short-circuit** just like in Python and Java: in `a && b`, if `a` is false, `b` is never evaluated.

## `if`, `else if`, `else`

```c
int score = 83;

if (score >= 90) {
    printf("A\n");
} else if (score >= 80) {
    printf("B\n");
} else {
    printf("Below B\n");
}

if (score >= 0 && score <= 100)
    printf("%d is a valid score\n", score);
```

```bash
$ ./grade
B
83 is a valid score
```

The parentheses around the condition are required. The braces are optional when the body is a single statement, as in the last `if`, but be careful: only that **one** statement is controlled by the `if`. Many style guides (and Apple's infamous 2014 "goto fail" SSL bug) say: when in doubt, use braces.

## The Classic Bug: `=` vs `==`

`=` assigns. `==` compares. And because an assignment is also an expression whose value is the value assigned, C will happily compile this:

```c
int tries = 3;
if (tries = 0)
    printf("Out of tries!\n");
else
    printf("You have %d tries left\n", tries);
```

```bash
$ gcc -std=c11 -o assign assign.c
$ ./assign
You have 0 tries left
```

`tries = 0` set `tries` to 0, and the value of that expression is 0, which is false. Two bugs in one line! Now compile with warnings:

```bash
$ gcc -std=c11 -Wall -o assign assign.c
assign.c: In function 'main':
assign.c:6:9: warning: suggest parentheses around assignment used as truth value [-Wparentheses]
    6 |     if (tries = 0)
      |         ^~~~~
```

This is why every Makefile in this workshop uses `-Wall -Wextra`. Warnings are bugs the compiler found for free.

## `switch`

When you're comparing **one integer value** (an `int`, a `char`, ...) against several constants, `switch` is cleaner than a chain of `else if`s:

```c
for (int month = 1; month <= 12; month++) {
    int days;
    switch (month) {
    case 2:
        days = 28;
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        days = 30;          /* four cases share this code */
        break;
    default:
        days = 31;
        break;
    }
    printf("%d:%d ", month, days);
}
printf("\n");
```

```bash
$ ./days
1:31 2:28 3:31 4:30 5:31 6:30 7:31 8:31 9:30 10:31 11:30 12:31
```

`switch` jumps to the matching `case` label and then runs **everything below it** until it hits a `break` (or the end of the `switch`). That behavior is called **fallthrough**. Stacking labels like `case 4: case 6: ...` uses it on purpose. Forgetting a `break` uses it by accident:

```c
int choice = 2;
switch (choice) {
case 1:
    printf("one\n");
case 2:
    printf("two\n");
case 3:
    printf("three\n");
default:
    printf("something else\n");
}
```

```bash
$ ./fall
two
three
something else
```

`-Wextra` warns about this with `this statement may fall through [-Wimplicit-fallthrough=]`. Note that `switch` cases must be constant integers: you can't `switch` on a string or a `double` in C.

> **Under the hood:** a `switch` with many cases is often compiled into a **jump table**, an array of addresses the CPU indexes into. That's CS350 Chapter 3.

## Loops: `while`, `for`, `do`-`while`

```c
/* while: check first, then run */
int n = 1;
while (n < 100)
    n *= 3;
printf("while:    first power of 3 >= 100 is %d\n", n);

/* for: init; condition; update */
printf("for:     ");
for (int i = 10; i > 0; i -= 3)
    printf(" %d", i);
printf("\n");

/* do-while: run first, then check -- always runs at least once */
int k = 100;
do {
    printf("do-while: k = %d\n", k);
    k++;
} while (k < 5);
```

```bash
$ ./loops
while:    first power of 3 >= 100 is 243
for:      10 7 4 1
do-while: k = 100
```

| Loop | Use it when... |
|------|----------------|
| `for (init; cond; update)` | You know how many times to loop, or you're counting |
| `while (cond)` | You loop until something happens, and it might be zero times |
| `do { ... } while (cond);` | The body must run at least once (e.g. "ask until the input is valid") |

C's `for` is not Python's `for x in ...`. It's really a `while` loop with the setup and the update written on one line. Declaring the counter inside it (`for (int i = 0; ...)`) keeps `i` local to the loop; that needs C99 or later, which is why our Makefiles say `-std=c11`. Note the `;` after the `do`-`while`'s condition: it's required.

### `break` and `continue`

```c
for (int i = 1; i <= 10; i++) {
    if (i % 2 == 0)
        continue;       /* skip the rest of this iteration */
    if (i > 7)
        break;          /* leave the loop entirely */
    printf("%d ", i);
}
printf("\n");
```

```bash
$ ./breakcont
1 3 5 7
```

`break` exits the **innermost** loop (or `switch`) only. In a `for` loop, `continue` still runs the update (`i++`) before checking the condition again.

### Nested loops

A loop inside a loop runs the inner loop completely for every pass of the outer one. This is how you work with grids, tables, and patterns:

```c
for (int row = 1; row <= 4; row++) {
    for (int col = 1; col <= 6; col++)
        printf("%4d", row * col);
    printf("\n");
}
```

```bash
$ ./table
   1   2   3   4   5   6
   2   4   6   8  10  12
   3   6   9  12  15  18
   4   8  12  16  20  24
```

The trick for pattern problems: for each row, work out **how many** of each thing to print as a formula of the row number, then write one inner loop per thing.

<details>
<summary>Compiling without <code>make</code></summary>

`make` just runs these commands for you. To practice compiling by hand, run them yourself from this challenge's directory, then start the program directly (for example `./fizzbuzz`):

```bash
# Programs that `make check` tests
gcc -std=c11 -Wall -Wextra -g -o fizzbuzz fizzbuzz.c
gcc -std=c11 -Wall -Wextra -g -o diamond diamond.c
gcc -std=c11 -Wall -Wextra -g -o collatz collatz.c

# Other programs in this challenge
gcc -std=c11 -Wall -Wextra -g -o oops oops.c
```

</details>

## Exercises

This challenge has three auto-checked programs. While you work on one, test just that program with `make check NAME` (for example `make check fizzbuzz`). Plain `make check` tests all three (each test name starts with its program's name, such as `fizzbuzz: to-15`), so you can watch the PASS count grow as you finish each one. `__SUCCESS__` appears once all three pass. Until you write your code, the compiler warns that `n` is unused; that's expected.

1. **FizzBuzzBang.** Complete `fizzbuzz.c`. For each number from 1 to n, print `Fizz` for multiples of 3, `Buzz` for multiples of 5, `Bang` for multiples of 7, all of the matching words for multiples of several (`21` is `FizzBang`, `105` is `FizzBuzzBang`), and the number itself otherwise. The full rules, including bad input, are in the file's comment. Covered by `make check fizzbuzz` (6 tests in `tests/fizzbuzz/`).
   ```bash
   $ echo 15 | make run fizzbuzz | tail -3
   13
   Bang
   FizzBuzz
   ```

2. **Diamond.** Complete `diamond.c` so it reads a size and prints a diamond of `*`s with nested loops. Get the top half working first. Covered by `make check diamond` (4 tests in `tests/diamond/`).
   ```bash
   $ echo 3 | make run diamond
     *
    ***
   *****
    ***
     *
   ```

3. **Collatz.** Complete `collatz.c`: print the Collatz sequence starting from n (halve even numbers, turn odd ones into 3n + 1, stop at 1), then the number of steps and the highest value reached. Covered by `make check collatz` (4 tests in `tests/collatz/`).
   ```bash
   $ echo 6 | make run collatz
   6 -> 3 -> 10 -> 5 -> 16 -> 8 -> 4 -> 2 -> 1
   Steps: 8
   Peak: 16
   ```
   Then try `echo 27 | make run collatz`. Nobody has ever proved that this loop ends for every starting number. It's a famous open problem!

4. **Fix the bugs.** `oops.c` has four classic control-flow bugs. Run `make oops`, read every warning, and fix the code until it builds with **zero warnings** and matches the expected output in the file's comment. Not covered by `make check`. For each bug, write one sentence explaining what the buggy code actually did. (Hint: `echo 85 | ./oops` currently claims a perfect score.)

5. **Predict the output.** Without running it, what does this print? Then type it into a scratch file and check.
   ```c
   int i = 0;
   while (i < 10) {
       i += 3;
       if (i == 6)
           continue;
       printf("%d ", i);
   }
   printf("\n");
   for (int j = 5; j < 5; j++)
       printf("for %d\n", j);
   int k = 5;
   do {
       printf("do %d\n", k);
   } while (k < 5);
   ```

6. **Validate with `do`-`while`.** Modify your `diamond.c` so that, instead of quitting on a size below 1, it keeps asking `Size (1 or more): ` until it gets one. A `do`-`while` loop is the natural fit. (This will break `make check`, because the tests expect the original behavior, so do it in a copy: `cp diamond.c diamond2.c` and `gcc -std=c11 -Wall -Wextra -o diamond2 diamond2.c`.) What happens if you type `abc`? Why? (Press `Ctrl+C` to stop a runaway program.)

7. **Bonus:** Add a hollow mode to a copy of the diamond: print only the outline, with spaces inside. Then try a checkerboard: read a size n and print an n-by-n grid where `#` and `.` alternate in both directions. (Hint: look at `(row + col) % 2`.)

## Checkpoint

You're ready to move on when you can:

- [ ] Explain what C considers true and false, and what `x > 3` evaluates to
- [ ] Spot the `=` vs `==` bug, and the compiler warning that points to it
- [ ] Write a `switch`, and explain what happens when a `break` is missing
- [ ] Pick the right loop (`for`, `while`, `do`-`while`) for a job
- [ ] Use `break` and `continue`, and say which loop `break` exits
- [ ] Print a 2D pattern with nested loops

## Quick Reference

| Thing | Description |
|-------|-------------|
| `== != < <= > >=` | Comparisons; produce `1` (true) or `0` (false) |
| `&& \|\| !` | Logical AND, OR, NOT (short-circuiting) |
| `if (c) {...} else if (d) {...} else {...}` | Branching |
| `#include <stdbool.h>` | Gives you `bool`, `true`, `false` |
| `switch (x) { case 1: ... break; default: ... }` | Multi-way branch on an integer; falls through without `break` |
| `while (c) {...}` | Check first; may run zero times |
| `for (int i = 0; i < n; i++) {...}` | Counting loop |
| `do {...} while (c);` | Runs at least once |
| `break` / `continue` | Leave the innermost loop / skip to the next iteration |
| `-Wall -Wextra` | Catches `=` in conditions, missing `break`, `a <= b <= c`, stray `;` |

---

**Previous:** [Variables, Types & printf](../02-variables-and-types/) | **Next:** [Functions & Scope](../04-functions/)
