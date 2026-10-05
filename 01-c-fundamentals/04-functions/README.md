# Challenge 4: Functions & Scope

Break programs into functions, learn exactly how C passes arguments and where variables live, and write your first recursive functions.

**Difficulty:** Beginner &nbsp;·&nbsp; **Time:** ~50 min &nbsp;·&nbsp; **Course tie-in:** CS350 Ch. 3 (procedures, the run-time stack, and recursion)

## Learning Objectives

- Declare, define, and call functions, and explain what a prototype is for
- Explain pass-by-value, and why a naive `swap` function can't work
- Tell local, global, and `static` local variables apart, and predict their lifetimes
- Write recursive functions with a base case, and picture the call stack they build
- Split a program into a header (`.h`) and two `.c` files and build it

## Anatomy of a Function

```c
return_type name(type param1, type param2)
{
    /* body */
    return value;
}
```

Every parameter has a type, and so does the return value. A function that returns nothing has return type `void`, and a function that takes nothing has `(void)` as its parameter list:

```c
void print_banner(void)
{
    printf("=== NJIT ACM ===\n");
}
```

C has no overloading (two functions can't share a name), no default arguments, and no nested functions. Functions live at the top level of a file.

## Declare Before You Use

The compiler reads your file **top to bottom, once**. When it sees a call, it must already know the function's name, parameter types, and return type. If the definition comes later, put a **prototype** (a declaration: the first line plus a `;`) above the call:

```c
#include <stdio.h>

double average(int a, int b);   /* prototype: "this function exists" */

int main(void)
{
    printf("%.1f\n", average(3, 4));
    return 0;
}

double average(int a, int b)    /* definition: the actual code */
{
    return (a + b) / 2.0;
}
```

```bash
$ ./average
3.5
```

Delete the prototype and modern GCC refuses to compile:

```bash
$ gcc -std=c11 -Wall -Wextra -o noproto noproto.c
noproto.c: In function 'main':
noproto.c:5:20: error: implicit declaration of function 'triple' [-Wimplicit-function-declaration]
    5 |     printf("%d\n", triple(5));
      |                    ^~~~~~
```

GCC 14 and newer make this an error. Older versions (like the ones on some lab machines) only **warn**, and then guess that the function returns `int`, which silently breaks things if it doesn't. Treat this warning as an error no matter which compiler you have.

That's what `#include <stdio.h>` is doing, by the way: `stdio.h` is a file full of prototypes, including `printf`'s.

## Pass-by-Value

When you call a function, C **copies** each argument's value into the function's parameter. The function works on its own copies. Here's the proof, from `swap.c` in this directory:

```c
void swap(int a, int b)
{
    int tmp = a;
    a = b;
    b = tmp;
    printf("  inside swap: a = %d, b = %d\n", a, b);
}

int main(void)
{
    int x = 1, y = 2;

    printf("before swap:   x = %d, y = %d\n", x, y);
    swap(x, y);
    printf("after swap:    x = %d, y = %d\n", x, y);
    return 0;
}
```

```bash
$ ./swap
before swap:   x = 1, y = 2
  inside swap: a = 2, b = 1
after swap:    x = 1, y = 2
```

```
main's variables        swap's variables (copies)
  x [ 1 ]  ──copy──►      a [ 1 ] → [ 2 ]
  y [ 2 ]  ──copy──►      b [ 2 ] → [ 1 ]
  (never touched)         (thrown away when swap returns)
```

Java programmers: this is exactly how Java treats `int`s. The difference is that C has **no** reference types to save you. To let a function change the caller's variable, you pass the variable's **address** instead. That's what the `&` in `scanf("%d", &x)` has been doing all along, and it's the subject of [Pointers & Addresses](../../02-pointers-and-memory/01-pointers/).

## Scope and Lifetime

**Scope** is *where* in the code a name is visible. **Lifetime** is *when* the variable exists in memory.

| Kind | Declared | Scope | Lifetime |
|------|----------|-------|----------|
| Local | Inside a function or block `{ }` | That block only | Created each time the block runs; destroyed when it ends |
| Parameter | In the function's `( )` | The function body | Same as a local |
| Global | Outside every function | The rest of the file (and other files, with `extern`) | The whole program |
| `static` local | Inside a function, with `static` | That block only | The whole program, initialized **once** |

```c
#include <stdio.h>

int total = 0;              /* global: visible to every function below */

void visit(void)
{
    int local = 0;          /* fresh copy on every call */
    static int calls = 0;   /* created once, keeps its value between calls */

    local++;
    calls++;
    total += 10;
    printf("local = %d, calls = %d, total = %d\n", local, calls, total);
}

int main(void)
{
    visit();
    visit();
    visit();
    return 0;
}
```

```bash
$ ./counter
local = 1, calls = 1, total = 10
local = 1, calls = 2, total = 20
local = 1, calls = 3, total = 30
```

A `static` local is like a private global: it remembers its value, but only `visit` can see it. Plain globals are convenient but make programs hard to reason about, because any function might change them. Prefer parameters and return values.

## Recursion

A **recursive** function calls itself on a smaller version of the problem. Every recursive function needs:

1. A **base case** that answers directly, without recursing.
2. A **recursive case** that makes progress toward the base case.

```c
long factorial(int n)
{
    if (n <= 1)
        return 1;                    /* base case */
    return n * factorial(n - 1);     /* recursive case */
}
```

Each call gets its **own** `n`, because each call gets its own **stack frame**, a chunk of memory on the **call stack** that holds its parameters, locals, and where to return to. Calling pushes a frame; returning pops it:

```
factorial(4) calls factorial(3) calls ... factorial(1):

  ┌────────────────────┐
  │ factorial  n = 1   │  ◄── top: base case, returns 1
  ├────────────────────┤
  │ factorial  n = 2   │      waiting to compute 2 * (result)
  ├────────────────────┤
  │ factorial  n = 3   │      waiting to compute 3 * (result)
  ├────────────────────┤
  │ factorial  n = 4   │      waiting to compute 4 * (result)
  ├────────────────────┤
  │ main               │
  └────────────────────┘
```

Then the frames pop off one at a time: 1, then 2 × 1 = 2, then 3 × 2 = 6, then 4 × 6 = 24. `recursion.c` in this directory prints this as a trace:

```bash
$ make run recursion
factorial(5)
  factorial(4)
    factorial(3)
      factorial(2)
        factorial(1)
        -> 1 (base case)
      -> 2
    -> 6
  -> 24
-> 120
5! = 120
...
```

How the CPU actually builds these frames (`call`, `ret`, `push`, `pop`, the `%rsp` register) is CS350 Chapter 3, and you'll see it yourself in [The Call Stack & Buffer Overflows](../../05-tools-and-the-machine/05-the-stack/). Forget the base case and the stack grows until the program crashes with a **stack overflow** (a "Segmentation fault" on Linux).

### Recursion isn't always a good idea

The textbook Fibonacci function is elegant and terribly slow, because it recomputes the same values over and over:

```c
long fib(int n)
{
    if (n < 2)
        return n;
    return fib(n - 1) + fib(n - 2);
}
```

You'll measure exactly how slow in Exercise 5.

## Splitting Code Across Files

Real programs aren't one giant `.c` file. The usual pattern is:

- **`mymath.h`** (the header): prototypes, the "menu" of what's available
- **`mymath.c`**: the definitions (the actual code), with `#include "mymath.h"` at the top
- **`main.c`**: uses the functions, with `#include "mymath.h"` at the top

`#include "..."` with quotes looks in the current directory first; `#include <...>` with angle brackets looks only in the system's directories. You compile both `.c` files together, and the linker (stage 4 from [Challenge 1](../01-hello-world/)) connects the call in `main.c` to the code in `mymath.c`:

```bash
$ gcc -std=c11 -Wall -Wextra -o mathtool main.c mymath.c
```

The Makefile in this challenge does that for you. Separate compilation, `.o` files, `extern`, and writing your own Makefile are all covered in [Multi-File Programs & Make](../../05-tools-and-the-machine/01-multi-file-and-make/).

<details>
<summary>Compiling without <code>make</code></summary>

`make` just runs these commands for you. To practice compiling by hand, run them yourself from this challenge's directory, then start the program directly (for example `./mathtool`):

```bash
# Programs that `make check` tests
gcc -std=c11 -Wall -Wextra -g -o mathtool main.c mymath.c

# Other programs in this challenge
gcc -std=c11 -Wall -Wextra -g -o swap swap.c
gcc -std=c11 -Wall -Wextra -g -o scope scope.c
gcc -std=c11 -Wall -Wextra -g -o recursion recursion.c
```

</details>

## Exercises

The main program for this challenge is `mathtool`, built from `main.c` (a ready-made driver; don't edit it), `mymath.h` (the prototypes, with a comment describing each function), and `mymath.c` (yours to finish). `main.c` reads one-letter commands, calls your function, and prints the result:

```bash
$ printf 'p 97\ng 12 18\ne 2 10\ns 12345\nr 98765\n' | make run mathtool
is_prime(97) = true
gcd(12, 18) = 6
power(2, 10) = 1024
sum_digits(12345) = 15
digital_root(98765) = 8
```

That's the output once you're done. Right now every function returns a placeholder, and `-Wextra` warns about "unused parameters" until you write the bodies. `make check` runs 5 test files, one per function plus a mixed one; look in `tests/mathtool/` to see exactly what each tests.

1. **`is_prime` and `gcd`.** In `mymath.c`, implement `is_prime` (anything below 2 is not prime) and `gcd` using Euclid's algorithm. The `TODO` comments give the strategy. Check with `make check`: the `primes` and `gcd` tests should pass.

2. **`power`, `sum_digits`, and `digital_root`.** Implement `power` with a loop, `sum_digits` **recursively** (no loops allowed!), and `digital_root` by calling your `sum_digits`. Now all 5 tests should pass and you'll see `__SUCCESS__`.

3. **Predict the scope.** Read `scope.c` and write down the 7 lines you expect it to print. Then `make run scope`. Explain every line you got wrong. Not covered by `make check`.

4. **The swap that doesn't.** Run `make run swap`. In two or three sentences, explain why `x` and `y` didn't change. Can you fix it by changing only `swap`'s body? (You can't. You can rescue it by making `swap` *return* something, but only one value. The real fix is in Section 2; the solution file has a sneak preview.)

5. **Measure recursion.** In `recursion.c`, add a call counter to `fib` (a global, or think about why a `static` local is awkward here) and print the number of calls for `fib(10)`, `fib(20)`, and `fib(30)`. Roughly how many times more calls does each extra 10 cost? Then write an iterative `fib_loop` with a `for` loop and two variables and compare.

6. **Break it on purpose.** In a scratch file, write a `factorial` with **no** base case (just `return n * factorial(n - 1);`) and call it from `main`. Newer GCCs warn `infinite recursion detected`; older ones may not. Run it anyway, then run `echo $?`. You should see `Segmentation fault` and exit code 139, which is 128 + 11, where 11 is the signal number for a segmentation fault. Explain the crash in terms of stack frames. (Hint: the stack is only a few megabytes, typically 8 MB on Linux; check yours with `ulimit -s`, which prints kilobytes.)

7. **Bonus:** Add a new command `c LO HI` to the calculator that prints how many primes there are between `LO` and `HI` inclusive. Declare `int count_primes(int lo, int hi);` in `mymath.h`, define it in `mymath.c` using your `is_prime`, and add a `case 'c':` to `main.c`. How long does `echo "c 1 10000000" | ./mathtool` take? Use `time` to find out, then try to make `is_prime` faster (skip even divisors after 2).

## Checkpoint

You're ready to move on when you can:

- [ ] Write a function's prototype and definition and explain why the prototype is needed
- [ ] Explain why `swap(x, y)` can't change `x` and `y`
- [ ] Say where local, global, and `static` local variables live and how long they last
- [ ] Write a recursive function with a correct base case, and draw its call stack
- [ ] Compile a program made of two `.c` files and a header

## Quick Reference

| Thing | Description |
|-------|-------------|
| `int f(int a, double b);` | Prototype (declaration): name, types, no body |
| `int f(int a, double b) { ... }` | Definition |
| `void f(void)` | Returns nothing, takes nothing |
| Pass-by-value | Parameters are copies of the arguments |
| `static int n = 0;` (in a function) | Keeps its value between calls; initialized once |
| Global variable | Declared outside all functions; visible everywhere below it |
| Base case / recursive case | The two parts of every recursive function |
| `#include "file.h"` | Include your own header (searches the current directory first) |
| `#ifndef X / #define X / #endif` | Include guard: makes a header safe to include twice |
| `gcc -o prog main.c other.c` | Compile and link several `.c` files into one program |

---

**Previous:** [Control Flow](../03-control-flow/) | **Next:** [Arrays & Strings](../05-arrays-and-strings/)
