# Challenge 2: Variables, Types & printf

Learn how C stores numbers & characters and how to read & print them precisely with `scanf` and `printf`.

**Difficulty:** Beginner
**Time:** ~40 min

## Learning Objectives

- Declare variables of C's basic types and how choose the right type
- Use `sizeof` to find out how many bytes of memory a given type occupies
- Print values with the right `printf` format specifier (e.g. widths and decimal places)
- Predict the result of integer division, `%`, implicit conversions, and casts
- Define constants and macros with `const` and `#define`, respectively
- Read numbers from the keyboard with `scanf` and detect uninitialized variables

## Variables Have Types, and Types Have Sizes

In Python you write `x = 5` and the language figures out the rest. In C, every variable has a **type** that you declare up front, and that type never changes:

```c
int count = 10;        /* a whole number                        */
double price = 4.99;   /* a number with a fractional part       */
char grade = 'A';      /* a single character (in single quotes) */
```

The type tells the compiler how many bytes of memory to set aside and how to interpret those bytes. The `sizeof` operator tells you how many bytes a type (or variable) uses:

```c
#include <stdio.h>

int main(void)
{
    printf("char:   %zu byte\n", sizeof(char));
    printf("short:  %zu bytes\n", sizeof(short));
    printf("int:    %zu bytes\n", sizeof(int));
    printf("long:   %zu bytes\n", sizeof(long));
    printf("float:  %zu bytes\n", sizeof(float));
    printf("double: %zu bytes\n", sizeof(double));
    return 0;
}
```

Running this program gives you an output that looks like:

```bash
$ ./sizes
char:   1 byte
short:  2 bytes
int:    4 bytes
long:   8 bytes
float:  4 bytes
double: 8 bytes
```

So, what are these different types used for?

| Type     | Typical size (x86-64 Linux) | Holds                                   | Example       |
| -------- | --------------------------- | --------------------------------------- | ------------- |
| `char`   | 1 byte                      | One character, or a tiny integer        | `'A'`, `'\n'` |
| `short`  | 2 bytes                     | Small integers (about ±32 thousand)     | `1200`        |
| `int`    | 4 bytes                     | Everyday integers (about ±2.1 billion)  | `-42`         |
| `long`   | 8 bytes                     | Big integers                            | `8100000000L` |
| `float`  | 4 bytes                     | Decimal numbers, ~7 significant digits  | `3.14f`       |
| `double` | 8 bytes                     | Decimal numbers, ~15 significant digits | `3.14159`     |

The C standard only guarantees _minimum_ sizes. On 64-bit Windows, for example, `long` is 4 bytes, not 8. That's why `sizeof` exists: never hard-code a size you can ask the compiler for. Each integer type also has an `unsigned` version (`unsigned int`, ...) that gives up negative numbers to reach twice as high.

> **Tip:** Use `int` for integers and `double` for decimals unless you have a reason not to. `float` loses precision surprisingly fast.

How those bytes actually encode a number (binary, two's complement, IEEE 754 floating point) is all of [Section 3](../../03-data-representation/) later in this workshop.

### Characters are small integers

A `char` is just a 1-byte number. The character `'A'` is stored as 65, its **ASCII** code. That means you can do arithmetic on characters:

```c
char c = 'A';
printf("%c is stored as %d\n", c, c);
c = c + 1;
printf("next letter: %c\n", c);
printf("'a' - 'A' = %d\n", 'a' - 'A');
```

```bash
$ ./chars
A is stored as 65
next letter: B
'a' - 'A' = 32
```

> **Fun Fact:** An interesting side effect of upper and lower case ASCII being offset by 32 is that XORing a chatacter with 32 (or, more clearly, `c ^= (1 << 5)`) allows you to switch its case without having to check its case before hand. More on bitwise opperations in [Section 3](../../03-data-representation/).

Single quotes make a `char` (`'A'`). Double quotes make a **string** (`"A"`), which is a different thing entirely. More on strings in [Challenge 5](../05-arrays-and-strings/).

## Printing with `printf`

`printf` takes a **format string** with placeholders called **format specifiers**, then one argument for each placeholder:

```c
int count = -42;
unsigned int big = 4000000000u;
long population = 8100000000L;
double pi = 3.14159265358979;
char grade = 'A';

printf("[%d]\n", count);
printf("[%u]\n", big);
printf("[%ld]\n", population);
printf("[%f]\n", pi);
printf("[%.2f]\n", pi);
printf("[%8.3f]\n", pi);
printf("[%c]\n", grade);
printf("[%d]\n", grade);
printf("[%s]\n", "Newark");
printf("[%x]\n", 255);
printf("[%5d] [%-5d] [%05d]\n", 42, 42, 42);
printf("[%zu]\n", sizeof(double));
printf("[100%%]\n");
```

```bash
$ ./fmt
[-42]
[4000000000]
[8100000000]
[3.141593]
[3.14]
[   3.142]
[A]
[65]
[Newark]
[ff]
[   42] [42   ] [00042]
[8]
[100%]
```

(The square brackets are just there so you can see the spaces.)

| Specifier | Prints                                       | Example output |
| --------- | -------------------------------------------- | -------------- |
| `%d`      | `int` in decimal                             | `-42`          |
| `%u`      | `unsigned int`                               | `4000000000`   |
| `%ld`     | `long`                                       | `8100000000`   |
| `%f`      | `double` (or `float`), 6 decimals by default | `3.141593`     |
| `%.2f`    | `double` with 2 decimals (rounded)           | `3.14`         |
| `%c`      | `char` as a character                        | `A`            |
| `%s`      | a string                                     | `Newark`       |
| `%x`      | `int` in hexadecimal                         | `ff`           |
| `%zu`     | a `size_t`, the type `sizeof` gives you      | `8`            |
| `%%`      | a literal `%` sign                           | `%`            |

You can put a **width** between the `%` and the letter: `%5d` pads to 5 characters on the left, `%-5d` pads on the right, and `%05d` pads with zeros. `%8.3f` means "8 characters wide, 3 after the decimal point." Widths are how you line up columns.

### Mismatches are bugs

`printf` trusts you completely. If the specifier doesn't match the argument, you get garbage, and that's whats called "**undefined behavior**": the C standard doesn't say what happens, so anything can. Luckily `-Wall` checks format strings:

```c
double gpa = 3.5;
printf("GPA: %d\n", gpa);
```

```bash
$ gcc -std=c11 -Wall -o mism mism.c
mism.c:6:19: warning: format '%d' expects argument of type 'int', but argument 2 has type 'double' [-Wformat=]
$ ./mism
GPA: -258012360
```

Your garbage number will be almost certainly different.

## Arithmetic: Integer Division and `%`

When **both** operands are integers, `/` does **integer division**: it throws away the fractional part (it truncates toward zero). `%` gives the remainder.

```c
printf("7 / 2   = %d\n", 7 / 2);
printf("7 %% 2   = %d\n", 7 % 2);
printf("-7 / 2  = %d\n", -7 / 2);
printf("-7 %% 2  = %d\n", -7 % 2);
printf("7.0 / 2 = %f\n", 7.0 / 2);
```

```bash
$ ./div
7 / 2   = 3
7 % 2   = 1
-7 / 2  = -3
-7 % 2  = -1
7.0 / 2 = 3.500000
```

Python programmers, watch out: in Python `7 // 2` is integer division and `7 / 2` is `3.5`. In C, `7 / 2` is `3`. And `-7 / 2` is `-3` in C but `-4` in Python.

### Conversions and casts

If one operand is a `double`, the other is **implicitly converted** to `double` first, so `7.0 / 2` is `3.5`. But the conversion happens per operation, and it happens _after_ the right-hand side is computed. That leads to this classic bug:

```c
int total = 7, n = 2;
double avg1 = total / n;            /* integer division happens FIRST */
double avg2 = (double) total / n;   /* cast one operand to double     */
printf("avg1 = %.2f, avg2 = %.2f\n", avg1, avg2);

int truncated = (int) 3.99;
char letter = 'a' + 2;
printf("(int) 3.99 = %d, 'a' + 2 = %c\n", truncated, letter);
```

```bash
$ ./div
...
avg1 = 3.00, avg2 = 3.50
(int) 3.99 = 3, 'a' + 2 = c
```

`(double) total` is a **cast**: an explicit "convert this value to that type" instead of a **conversion**. Another classic but is forgetting that casting a `double` to an `int` "chops off" the decimal rather than rounding it.

## Constants: `const` and `#define`

Magic numbers scattered through code are hard to read and easy to mess up. Luckily, C has two ways to name a constant:

```c
#include <stdio.h>

#define TAX_RATE 0.06625    /* (NJ sales tax) no '=' and no ';' */

int main(void)
{
    const int SECONDS_PER_HOUR = 3600;
    double price = 20.00;

    printf("Tax on $%.2f is $%.2f\n", price, price * TAX_RATE);
    printf("An hour is %d seconds\n", SECONDS_PER_HOUR);
    /* SECONDS_PER_HOUR = 60;   <-- error: assignment of read-only variable */
    return 0;
}
```

```bash
$ ./consts
Tax on $20.00 is $1.33
An hour is 3600 seconds
```

- `#define TAX_RATE 0.06625` is a **preprocessor** instruction (remember stage 1 from [Challenge 1](../01-hello-world/)?). Before compiling, every `TAX_RATE` in the file is replaced with the text `0.06625`. It has no type and uses no memory.
- `const int SECONDS_PER_HOUR = 3600;` is a real variable with a type that the compiler won't let you change. If you uncomment the last line, you get `error: assignment of read-only variable 'SECONDS_PER_HOUR'`.

There are benefits to using both -- when using `const` you give the compiler a typed, scoped, debuggable object which it can reason about. However, const-qualified values are actually _not_ compile-time constants, which means they can't be used as array sizes, switch case labels, or values needed during preprocessing (such as for `#if` directives).

By convention, constants are written in `ALL_CAPS`.

## Reading Input with `scanf`

`scanf` is `printf` in reverse: it reads text from standard input (the keyboard, or a file or pipe) and converts it using format specifiers.

```c
#include <stdio.h>

int main(void)
{
    int age;
    double gpa;

    printf("Age and GPA: ");
    if (scanf("%d %lf", &age, &gpa) != 2) {
        printf("That wasn't a number!\n");
        return 1;
    }
    printf("In 4 years you'll be %d. GPA: %.1f\n", age + 4, gpa);
    return 0;
}
```

```bash
$ ./ask
Age and GPA: 19 3.75
In 4 years you'll be 23. GPA: 3.8
$ echo "nineteen" | ./ask
Age and GPA: That wasn't a number!
```

Three things to notice:

1. **The `&`:** `scanf` needs to know _where_ to store each value, so you pass the variable's **address** with `&`. Why that's necessary is the whole story of pointers, and you'll see it in [Section 2](../../02-pointers-and-memory/01-pointers/). For now: `scanf` wants `&` in front of each variable identifier.
2. **`%lf` for `double`:** `printf` uses `%f` for both `float` and `double`, but `scanf` needs `%lf` ("long float") for a `double`.
3. **Check the return value:** `scanf` returns how many values it successfully read. If it's not the number you asked for, the input was bad. This can be a good way to catch an error early.

The `echo "..." | ./ask` trick sends text to your program's input as if you'd typed it. `make check` uses the same idea to feed test input to your programs. You can, of course, just run your program and type it in normally, however your shell's history means that running the same command repeatedly while working on a program is much easier.

## Uninitialized Variables

In Python, using a variable before assigning it is an error. In C, a local variable you haven't assigned holds **whatever bytes were already in that memory**. Reading it is undefined behavior:

```c
int total;            /* never given a value! */
for (int i = 1; i <= 3; i++)
    total += i;
printf("total = %d\n", total);
```

```bash
$ gcc -std=c11 -Wall -Wextra -g -o uninit uninit.c
$ ./uninit
total = 26208
$ gcc -std=c11 -Wall -Wextra -O2 -o uninit uninit.c
uninit.c:7:15: warning: 'total' is used uninitialized [-Wuninitialized]
$ ./uninit
total = 6
```

The first build gave garbage and **no warning**; the optimized build (`-O2`) noticed the problem and then happened to print the "right" answer anyway. Your numbers may differ, which is exactly the point: the behavior is unpredictable. This is another instance of **undefined behavior**, luckily, the fix is simple: **always initialize** (e.g. `int total = 0;`).

<details>
<summary>Compiling without <code>make</code></summary>

`make` just runs these commands for you. To practice compiling by hand, run them yourself from this challenge's directory, then execute the program directly (for example `./receipt`):

```bash
# Programs that `make check` tests
gcc -std=c11 -Wall -Wextra -g -o receipt receipt.c

# Other programs/exercises in this challenge
gcc -std=c11 -Wall -Wextra -g -o types types.c
gcc -std=c11 -Wall -Wextra -g -o predict predict.c
gcc -std=c11 -Wall -Wextra -g -o buggy buggy.c    #
```

> **Note:** `buggy.c` doesn't compile cleanly yet -- that's intentional

</details>

## Exercises

1. **Sizes and limits:** Open `types.c` and finish both `TODO`s: add `sizeof` rows for `short`, `long`, `long long`, `float`, and `double`, and print `INT_MIN`, `SHRT_MAX`, `LONG_MAX`, and `UINT_MAX` from `<limits.h>`. Build and run it with `make run types`. Not covered by `make check` (sizes depend on the platform and therefore aren't deterministic) -- compare with a neighbor on a different OS if you can.

2. **Split the bill:** Complete `receipt.c` so it reads a subtotal, a tip percentage, and a number of people, then prints a receipt. The exact output format is in the comment at the top of the file. Until you use your variables, the compiler will warn that they are unused.
   ```bash
   $ echo "84.50 18 4" | make run receipt
   Subtotal:   $   84.50
   Tax:        $    5.60
   Tip (18%):  $   15.21
   Total:      $  105.31
   Per person (4): $26.32
   Leftover cents: 3
   $ make check receipt
   ```
   `make check receipt` runs 5 tests (look in `tests/receipt/` to see their inputs). `receipt` is the only program in this challenge with tests, so plain `make check` does the same thing and prints `__SUCCESS__` when they all pass.

<details>
<summary>Hints / Common traps</summary>
Common traps: `tip_percent / 100` is integer division, and `cents / 100` is too.
</details>

3. **Predict the output:** Open `predict.c` and write down what you think each of the 12 lines prints _before_ running it. Then run it with `make run predict`. Pay special attention to lines 4 vs. 5 and 11 vs. 12. Line 10 might surprise you (shouldn't 2.675 round _up_?) -- it will make sense after you learn about how C handles [Floating Points](../../03-data-representation/03-floating-point/).

4. **Fix the bugs:** `buggy.c` is supposed to average three exam scores, but it has **five** bugs. Run `make buggy` and read the warnings: `-Wall` finds four of them. The fifth produces a wrong answer with no warning at all. When it's fixed, it should build with zero warnings and print:

   ```bash
   $ echo "90 85 88" | make run buggy
   Enter three exam scores: Sum: 263
   Average: 87.67
   ```

5. **Bad input:** Run `./receipt` and type `abc` instead of numbers. What happens, and why? Add a check on `scanf`'s return value that prints `Expected: subtotal tip_percent people` and returns `1` if the input is bad. Run `make check` again to make sure you didn't break anything.

6. **Experiment: unsigned surprises.** Add these lines to the end of `types.c` and run it. Explain each result in one sentence.

   ```c
   unsigned int u = 0;
   u = u - 1;
   printf("%u\n", u);
   printf("%d\n", -1 < 1u);
   ```

7. **Bonus:** Change `TAX_RATE` and the `Tax:` line so that `receipt` also prints the tax rate, like `Tax (6.625%):`. Which format specifier prints `6.625` with no trailing zeros (try `%g`.)? Then put the format back so `make check` still passes.

## Checkpoint

You're ready to move on when you can:

- [ ] Name C's basic types and say roughly how big each one is
- [ ] Pick the right `printf` specifier for `int`, `long`, `double`, `char`, a string, and a `size_t`
- [ ] Explain why `7 / 2` is `3` and how to get `3.5` instead
- [ ] Explain the difference between `#define` and `const`
- [ ] Read numbers with `scanf` (and know you need `&` and `%lf`)
- [ ] Explain why you should always initialize your variables

## Quick Reference

| Thing                          | Description                                                                     |
| ------------------------------ | ------------------------------------------------------------------------------- |
| `int x = 0;`                   | Declare and initialize a variable                                               |
| `sizeof(type)`                 | Size in bytes, as a `size_t` (print with `%zu`)                                 |
| `%d %u %ld %f %c %s %x %zu %%` | `int`, `unsigned`, `long`, `double`, `char`, string, hex, `size_t`, literal `%` |
| `%8.2f` / `%-5d` / `%05d`      | Width 8 with 2 decimals / left-justify / pad with zeros                         |
| `7 / 2`, `7 % 2`               | Integer division (`3`) and remainder (`1`)                                      |
| `(double) x`                   | Cast `x` to `double`                                                            |
| `#define NAME value`           | Text substitution by the preprocessor                                           |
| `const int N = 10;`            | A variable that can't be changed                                                |
| `scanf("%d %lf", &i, &d)`      | Read an `int` and a `double`; returns the number of items read                  |
| `<limits.h>`                   | `INT_MAX`, `INT_MIN`, `LONG_MAX`, `UINT_MAX`, ...                               |

---

**Previous:** [Hello, World!](../01-hello-world/) | **Next:** [Control Flow](../03-control-flow/)
