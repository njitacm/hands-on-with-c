# Challenge 5: Command-Line Arguments

Turn your programs into real command-line tools that take arguments and flags, check their input carefully, and report errors the way Unix tools do.

**Difficulty:** Intermediate &nbsp;·&nbsp; **Time:** ~45 min &nbsp;·&nbsp; **Course tie-in:** CS288 Wk 9 (command line arguments)

## Learning Objectives

- Read command-line arguments through `argc` and `argv`, and draw `argv` as a `char **`
- Explain what the shell does to your arguments (splitting, quotes, `*`) before your program sees them
- Convert argument strings to numbers with `strtol`, with full error checking, and explain why `atoi` isn't enough
- Write error and usage messages to `stderr` and return a nonzero exit code on failure
- Parse simple flags such as `-v` and `-n 5`, and know that `getopt` exists

> **Trying the snippets:** each example that shows a `$ ./name` run is either a file in this directory (`make name`) or was saved as `name.c` and built with `gcc -std=c11 -Wall -Wextra -o name name.c`. Type them in and run them yourself.

## `argc` and `argv`

Every tool you've used in the terminal takes arguments: `gcc -Wall -o hello hello.c`, `ls -l`, `head -n 5 file.txt`. Your C programs can too. Declare `main` like this:

```c
int main(int argc, char *argv[])
```

| Parameter | Meaning |
|-----------|---------|
| `argc` | **arg**ument **c**ount: how many strings are in `argv`, *including the program name* |
| `argv` | **arg**ument **v**ector: an array of strings, one per argument |

`args.c` prints them all:

```bash
$ make args
$ ./args hello "two words" 42
argc = 4
argv[0] = "./args"
argv[1] = "hello"
argv[2] = "two words"
argv[3] = "42"
argv[4] = NULL
```

A few things to notice:

- **`argv[0]` is the program's name**, exactly as it was typed (`./args`). That's why `argc` is never 0 in practice: with no arguments, it's 1. It's also why error messages use `argv[0]`: they then show whatever name the user typed.
- **Every argument is a string**, even `42`. It's the two characters `'4'` and `'2'` plus a `'\0'`, not the number 42. Converting it is your job (more below).
- **`argv[argc]` is always `NULL`**, a marker for the end of the list, like `'\0'` at the end of a string.

### `argv` is a `char **`

`char *argv[]` is a parameter with array syntax, so (as you saw in [Challenge 2](../02-pointer-arithmetic/)) it's really a pointer: `char **argv`. You'll see both spellings, and they mean the same thing. Here's the picture for `./args hello "two words" 42`. It's the same array-of-pointers shape as the jagged arrays in [Challenge 4](../04-multidimensional-arrays/), with `char` instead of `int`:

```
  argv (char **)      array of char *                 the strings
 ┌───────┐           ┌──────────┐
 │   ●───┼─────────► │ argv[0] ●┼────────► │ . │ / │ a │ r │ g │ s │\0 │
 └───────┘           ├──────────┤
                     │ argv[1] ●┼────────► │ h │ e │ l │ l │ o │\0 │
                     ├──────────┤
                     │ argv[2] ●┼────────► │ t │ w │ o │   │ w │ o │ r │ d │ s │\0 │
                     ├──────────┤
                     │ argv[3] ●┼────────► │ 4 │ 2 │\0 │
                     ├──────────┤
                     │ argv[4]  │  NULL
                     └──────────┘
```

So `argv[2]` is a `char *` (a whole string), and `argv[2][0]` is a `char` (`'t'`). You can walk the list with a pointer, stopping at the `NULL`, just like walking a string to its `'\0'`:

```c
for (char **p = argv; *p != NULL; p++)
    printf("%s\n", *p);
```

## The Shell Gets There First

Your program never sees the command line you typed. The **shell** (bash, zsh) splits it into words, processes it, and *then* hands your program the resulting list of strings. Three consequences:

| You type | `argv` gets | Why |
|----------|-------------|-----|
| `./args two words` | `"two"`, `"words"` | Words are split on spaces |
| `./args "two words"` | `"two words"` | Quotes keep spaces together; the quotes themselves are removed |
| `./args 6 * 7` | `"6"`, `"calc.c"`, `"Makefile"`, `"notes.txt"`, `"7"` | `*` is a **wildcard**: the shell replaces it with every filename in the directory |
| `./args 6 '*' 7` | `"6"`, `"*"`, `"7"` | Quoting turns the wildcard off |

That third row is real output from a directory containing `calc.c`, `Makefile`, and `notes.txt`:

```bash
$ ./args 6 * 7
argc = 6
argv[0] = "./args"
argv[1] = "6"
argv[2] = "calc.c"
argv[3] = "Makefile"
argv[4] = "notes.txt"
argv[5] = "7"
argv[6] = NULL
```

That's why the calculator in this challenge uses `x` for multiplication. You learned about wildcards, quoting, and word splitting in the Bash part of CS288; this is the other side of it.

## Converting Arguments to Numbers

Since every argument is a string, a number like `"42"` has to be converted. There are two common choices in `<stdlib.h>`:

```c
int  atoi(const char *s);                          /* simple, but can't report errors */
long strtol(const char *s, char **end, int base);  /* reports where it stopped */
```

Here's what they do with some good and bad input (`convert.c` runs both on each argument):

```bash
$ ./convert 42 -17 abc 12abc "" 99999999999999999999
42                     atoi: 42          strtol: 42                   OK
-17                    atoi: -17         strtol: -17                  OK
abc                    atoi: 0           strtol: 0                    no digits at all
12abc                  atoi: 12          strtol: 12                   leftover text "abc"
                       atoi: 0           strtol: 0                    no digits at all
99999999999999999999   atoi: -1          strtol: 9223372036854775807  out of range
```

`atoi` returns `0` for `"abc"`. Is that an error, or did the user type `0`? You can't tell. It also quietly accepts `"12abc"`, and on overflow its behavior is *undefined* (here it gave `-1`). **Use `atoi` only when you don't care about bad input**, which in a real tool is never.

`strtol` reports everything you need through two side channels:

- **`end` (an out-parameter, a `char **`):** `strtol` stores a pointer to the first character it *didn't* use. If that's the start of the string, there were no digits. If it isn't the `'\0'`, there was junk after the number.
- **`errno` (from `<errno.h>`):** set to `ERANGE` if the number doesn't fit in a `long`. `strtol` only *sets* `errno` on error and never clears it, so you set it to 0 first.

```
   s ──► │ 1 │ 2 │ a │ b │ c │\0 │
                   ▲
                  end        *end == 'a', not '\0'  →  junk after the number
```

The complete, careful version is a pattern worth memorizing:

```c
char *end;
errno = 0;
long value = strtol(s, &end, 10);     /* 10 = decimal */

if (end == s)          { /* no digits at all: "", "abc" */ }
else if (*end != '\0') { /* junk after the number: "12abc" */ }
else if (errno == ERANGE) { /* too big or too small for a long */ }
else                   { /* value is good */ }
```

Notice `&end`: `strtol` needs to *change* your `end` pointer, so you pass its address. That makes it a pointer to a pointer, a `char **`. It's the out-parameter idea from [Challenge 1](../01-pointers/), one level up.

## Errors: `stderr` and Exit Codes

A well-behaved command-line tool does two things when something goes wrong.

**1. It prints the error to `stderr`, not `stdout`.** Every program has two output streams. `stdout` is for *results*; `stderr` is for *messages to the human*. When someone redirects your output to a file or pipes it to another program, only `stdout` goes along, so errors still show up on the screen and never pollute the data:

```c
fprintf(stderr, "%s: division by zero\n", argv[0]);
```

**2. It returns a nonzero exit code.** `0` means success; anything else means failure. Scripts (and `make`) check this to decide whether to keep going.

Here's the finished calculator from this challenge in action:

```bash
$ ./calc 3 + 4
7
$ ./calc 7 / 0
./calc: division by zero
$ echo $?
1
$ ./calc 7 / 0 2>/dev/null
$ echo $?
1
$ ./calc 6 x 7 > result.txt
$ cat result.txt
42
$ ./calc 6 / 0 > result.txt
./calc: division by zero
$ cat result.txt
```

`2>/dev/null` throws away `stderr`, so the error message disappears but the exit code still says "failure." And when `stdout` is redirected to a file, the error message still reaches the screen while the file stays clean.

| Stream | C name | Shell redirect | Use it for |
|--------|--------|----------------|------------|
| Standard output | `stdout` (`printf`) | `>` file, `\|` pipe | Results |
| Standard error | `stderr` (`fprintf(stderr, ...)`) | `2>` file | Errors, warnings, usage |

> **About `make check`:** the test runner only compares `stdout`. So when a test passes bad input, the expected output is *empty*: any error message has to go to `stderr`. Check your exit codes yourself with `echo $?`.

### Usage messages

When the arguments don't make sense, tell the user how to call your program. The convention is a one-line `usage:` message on `stderr`, with optional parts in `[brackets]`:

```bash
$ ./calc 3 +
usage: ./calc NUMBER OP NUMBER   (OP is one of + - x / %)
```

**Always check `argc` before you touch `argv[i]`.** In the starter version of `calc.c`, `./calc 3 +` reads `argv[3]`, which is the `NULL` at the end of the list, and passes it to `atoi`, which dereferences it. Segfault.

## Parsing Flags

Flags (also called options) are arguments that start with `-` and change how a program behaves. Parsing them is a loop over `argv` with `strcmp`:

```c
for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-v") == 0) {
        verbose = 1;
    } else if (strcmp(argv[i], "-n") == 0) {
        if (i + 1 >= argc) { /* error: -n was the last argument */ }
        i++;                          /* the count is the NEXT argument */
        /* ... convert argv[i] with strtol ... */
    } else {
        /* error: unknown option */
    }
}
```

The interesting one is `-n 5`: the flag *takes a value*, which is the next element of `argv`. Check that the next element exists, then use `i++` to step past it so the loop doesn't treat `5` as a flag. Here's the `myhead` tool you'll build in Exercise 4:

```bash
$ seq 1 100 | ./myhead -n 3
1
2
3
$ seq 1 100 | ./myhead -v -n 2
==> standard input <==
1
2
$ seq 1 100 | ./myhead -n abc
./myhead: invalid number of lines: 'abc'
```

### `getopt`

Option parsing gets fiddly fast (`-n5`, `-vn 3`, `--`, ...), so POSIX systems like Linux and macOS provide `getopt` in `<unistd.h>`. It's not part of standard C, so with `-std=c11` you have to ask for it with a `#define` before any `#include`:

```c
#define _POSIX_C_SOURCE 200809L     /* getopt is POSIX, not standard C */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int verbose = 0;
    const char *count = "10";
    int opt;

    while ((opt = getopt(argc, argv, "n:v")) != -1) {   /* "n:" = -n takes a value */
        switch (opt) {
        case 'n':
            count = optarg;                            /* the value after -n */
            break;
        case 'v':
            verbose = 1;
            break;
        default:                                       /* getopt already printed an error */
            fprintf(stderr, "usage: %s [-n N] [-v]\n", argv[0]);
            return 1;
        }
    }
    printf("count=%s verbose=%d\n", count, verbose);
    return 0;
}
```

```bash
$ ./opts -v -n 5
count=5 verbose=1
$ ./opts -n5
count=5 verbose=0
$ ./opts -vn 3
count=3 verbose=1
$ ./opts -x
./opts: invalid option -- 'x'
usage: ./opts [-n N] [-v]
```

For this challenge, write the loop by hand: it's good pointer practice, and it's what CS288 expects you to understand. Reach for `getopt` in your own tools.

<details>
<summary>Compiling without <code>make</code></summary>

`make` just runs these commands for you. To practice compiling by hand, run them yourself from this challenge's directory, then start the program directly (for example `./calc`):

```bash
# Programs that `make check` tests
gcc -std=c11 -Wall -Wextra -g -o calc calc.c
gcc -std=c11 -Wall -Wextra -g -o myhead myhead.c

# Other programs in this challenge
gcc -std=c11 -Wall -Wextra -g -o args args.c
```

</details>

## Exercises

This challenge has two auto-checked programs. `make check calc` and `make check myhead` test one program each, and `make check` runs both (`tests/calc/` and `tests/myhead/`) and prints `__SUCCESS__` once all of them pass; each test's arguments are in its `.args` file (for example, `tests/calc/add.args` contains `3 + 4`). Remember that only `stdout` is compared, so for bad input the expected output is empty.

1. **Check `argc`** (`calc.c`, checked by `make check calc`). First, build the starter code with `make calc`, then run `./calc 3 +` and `./calc`. Explain the crash using the `argv` diagram. Then add the `argc` check so wrong argument counts print the usage message to `stderr` and return 1.

2. **`strtol`** (`calc.c`, checked). Replace `atoi` in `parse_long` with `strtol` and check all three failure cases (no digits, leftover text, `ERANGE`). Tests include `abc`, `12abc`, and a 20-digit number.

3. **More operators** (`calc.c`, checked). Add `-`, `x` (and a quoted `'*'`), `/`, and `%` with a `switch`. Division or remainder by zero, a multi-character operator, or an unknown operator is an error. Then try `./calc 6 * 7` (no quotes) and explain the message you get.

4. **`myhead`** (`myhead.c`, checked by `make check myhead`). Write the option loop for `-v` and `-n N`, in any order. Reject a missing count, a count that isn't a number, a negative count, and any unknown option, each with a message on `stderr` and exit code 1. Compare your tool with the real one: `seq 1 20 | head -n 3` vs. `seq 1 20 | ./myhead -n 3`.

5. **Explore** (`args.c`, not checked). Run `./args` with: no arguments; `"a b" c`; `'$HOME'` and `"$HOME"`; `*.c`; and `-n 5 -- -v`. For each, predict `argc` and every `argv[i]` first. Which ones surprised you, and which part of the shell was responsible?

6. **Walk `argv`** (`args.c`, not checked). Rewrite the loop in `args.c` to use a `char **p` that starts at `argv` and stops at the `NULL`, with no `argc` and no index. Then print only the *first character* of each argument. (What's the type of `*p`? Of `**p`?)

7. **Exit codes in the shell** (no file). Try `./calc 2 + 2 && echo worked` and `./calc 2 / 0 && echo worked`. Then `./calc 2 / 0 || echo failed`. How do `&&` and `||` use your exit code?

8. **Bonus:** Make `calc` evaluate a whole chain left to right, like `./calc 1 + 2 x 3` (giving `9`, not `7`). Then make it detect overflow, for example `./calc 9223372036854775807 + 1`, instead of silently wrapping around (signed overflow is undefined behavior). Hint: check the operands against `LONG_MAX` / `LONG_MIN` from `<limits.h>` *before* you do the arithmetic. Every test except `too-many` should still pass. That one (`1 + 2 + 3`) expects an error, so once chains work, change `tests/calc/too-many.out` to `6`.

## Checkpoint

You're ready to move on when you can:

- [ ] Say what `argc` and `argv[0]` are for `./prog a b`
- [ ] Draw `argv` as a `char **` pointing to an array of `char *` that ends in `NULL`
- [ ] Explain why `./calc 6 * 7` doesn't do what you might expect
- [ ] Convert a string to a number with `strtol` and detect all three kinds of bad input
- [ ] Send errors to `stderr`, return a nonzero exit code, and print a usage message
- [ ] Parse flags such as `-v` and `-n 5` in any order

## Quick Reference

| Syntax | Description |
|--------|-------------|
| `int main(int argc, char *argv[])` | Receive command-line arguments (`char **argv` is the same) |
| `argv[0]` | The program name, as typed |
| `argv[1]` ... `argv[argc - 1]` | The arguments, all strings |
| `argv[argc]` | Always `NULL` |
| `strtol(s, &end, 10)` | String to `long`; `end` marks where it stopped |
| `errno = 0;` ... `errno == ERANGE` | Detect out-of-range numbers (`<errno.h>`) |
| `atoi(s)` | String to `int` with no error reporting; avoid for user input |
| `fprintf(stderr, ...)` | Print an error or usage message |
| `return 1;` (from `main`) | Exit with failure; `echo $?` shows it |
| `strcmp(argv[i], "-v") == 0` | Check for a flag |
| `getopt(argc, argv, "n:v")` | POSIX option parser (`<unistd.h>`, needs `_POSIX_C_SOURCE`) |

---

**Previous:** [Multidimensional Arrays](../04-multidimensional-arrays/) | **Next:** [Binary, Hex & Integers](../../03-data-representation/01-number-systems/)
