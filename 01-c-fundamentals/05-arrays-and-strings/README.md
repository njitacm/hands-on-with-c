# Challenge 5: Arrays & Strings

Store many values in one variable, discover that a C string is just an array of `char`s with a zero at the end, and build real text-processing tools with `string.h` and `ctype.h`.

**Difficulty:** Beginner &nbsp;·&nbsp; **Time:** ~60 min &nbsp;·&nbsp; **Course tie-in:** CS350 Ch. 3 (arrays and their memory layout); sets up CS288 Wk 7-8 (pointers and arrays)

## Learning Objectives

- Declare, initialize, and loop over fixed-size arrays, and compute their length with `sizeof`
- Pass arrays to functions along with their length, and explain why functions can change them
- Explain why reading or writing past the end of an array is undefined behavior
- Describe how C stores a string, and why the `'\0'` terminator matters
- Use `strlen`, `strcpy`, `strncpy`, `strcat`, and `strcmp`, plus `ctype.h`'s character tests
- Read a whole line safely with `fgets` and strip its newline

## Arrays

An array is a fixed number of values of the **same type**, stored **side by side** in memory. You choose the size when you declare it, and it can never grow or shrink.

```c
int scores[5] = {90, 85, 77, 100, 62};
int zeros[10] = {0};            /* first is 0, the rest default to 0 */
double temps[] = {71.5, 68.0, 74.2};   /* size inferred: 3 */

size_t n = sizeof(scores) / sizeof(scores[0]);
printf("scores has %zu elements, %zu bytes\n", n, sizeof(scores));
printf("temps has %zu elements\n", sizeof(temps) / sizeof(temps[0]));

int sum = 0;
for (size_t i = 0; i < n; i++)
    sum += scores[i];
printf("sum = %d, zeros[7] = %d\n", sum, zeros[7]);

scores[0] = 95;     /* elements are assignable... */
/* scores = zeros;     ...but whole arrays are not: compile error */
printf("scores[0] is now %d\n", scores[0]);
```

```bash
$ ./arrays
scores has 5 elements, 20 bytes
temps has 3 elements
sum = 414, zeros[7] = 0
scores[0] is now 95
```

In memory, `scores` is 5 `int`s back to back, 4 bytes each:

```
index:     [0]    [1]    [2]    [3]    [4]
         ┌──────┬──────┬──────┬──────┬──────┐
scores:  │  95  │  85  │  77  │ 100  │  62  │   20 bytes, one after another
         └──────┴──────┴──────┴──────┴──────┘
byte:     +0     +4     +8     +12    +16
```

Indexes run from `0` to `length - 1`. `sizeof(scores) / sizeof(scores[0])` (total bytes divided by bytes per element) is the standard idiom for "how many elements," but it only works where the array was declared, as you're about to see. An array declared without an initializer, like `int a[5];` inside a function, holds garbage, just like an uninitialized `int`.

## Passing Arrays to Functions

```c
#include <stdio.h>

/* The array parameter doesn't carry its length, so pass it separately. */
double average(const int values[], int len)
{
    int sum = 0;
    for (int i = 0; i < len; i++)
        sum += values[i];
    return (double) sum / len;
}

void double_all(int values[], int len)
{
    for (int i = 0; i < len; i++)
        values[i] *= 2;
}

int main(void)
{
    int data[4] = {3, 1, 4, 1};

    printf("average = %.2f\n", average(data, 4));
    double_all(data, 4);
    printf("after double_all: %d %d %d %d\n", data[0], data[1], data[2], data[3]);
    return 0;
}
```

```bash
$ ./pass
average = 2.25
after double_all: 6 2 8 2
```

Wait, didn't [Challenge 4](../04-functions/) say C passes everything **by value**? It does, but an array isn't copied when you pass it. What gets passed (by value) is the **address of its first element**. So the function works on the caller's actual array, and `double_all` really changes `data`. Two consequences:

1. Inside the function, `sizeof(values)` is the size of an address (8 bytes), not the array. The function has **no way** to know the length, so you always pass it in.
2. Write `const` on array parameters you don't intend to modify, like `average` does. The compiler will then stop you from changing them by accident.

Why arrays behave this way is the heart of [Pointer Arithmetic & Arrays](../../02-pointers-and-memory/02-pointer-arithmetic/).

## No Bounds Checking

Python raises `IndexError`. Java throws `ArrayIndexOutOfBoundsException`. C does... nothing. It computes "start of array + index × element size" and reads or writes whatever memory is there. Going out of bounds is **undefined behavior**: the program might print garbage, crash, seem to work perfectly, or quietly corrupt another variable.

```c
int a[4] = {10, 20, 30, 40};
int i = 4;              /* one past the last valid index (0..3) */

printf("a[%d] = %d\n", i, a[i]);    /* undefined behavior! */
```

```bash
$ gcc -std=c11 -Wall -Wextra -g -o peek peek.c
$ ./peek
a[4] = 845358584
```

No warning, no error, just a number that was never in the array. (Yours will differ.) Tools can help. **AddressSanitizer** adds checks to every memory access when you compile with `-fsanitize=address`:

```bash
$ gcc -std=c11 -Wall -Wextra -g -fsanitize=address -o peek peek.c
$ ./peek
==42597==ERROR: AddressSanitizer: stack-buffer-overflow on address 0x6060240d9030 ...
READ of size 4 at 0x6060240d9030 thread T0
    #0 0x6e4b42350f2c in main /.../peek.c:8
...
    [32, 48) 'a' (line 5) <== Memory access at offset 48 overflows this variable
```

It even tells you the line and the variable. You'll use it (and Valgrind) seriously in [Finding Memory Bugs](../../05-tools-and-the-machine/03-finding-memory-bugs/). Out-of-bounds **writes** are worse than reads: they're how buffer overflow attacks work, which is CS350 Chapter 3 material and the subject of [The Call Stack & Buffer Overflows](../../05-tools-and-the-machine/05-the-stack/).

## Strings Are `char` Arrays

C has no string type. A **string** is an array of `char`s that ends with the **null character** `'\0'` (a byte whose value is 0). Every string function finds the end of a string by walking forward until it hits that `'\0'`.

```c
char name[] = "NJIT";               /* the compiler adds the '\0' */

printf("sizeof = %zu, strlen = %zu\n", sizeof(name), strlen(name));
for (int i = 0; i < 4; i++)
    printf("name[%d] = '%c' (%d)\n", i, name[i], name[i]);
printf("name[4] = %d, the terminator\n", name[4]);

name[0] = 'n';                      /* strings in arrays are editable */
printf("%s\n", name);

name[2] = '\0';                     /* cut it short */
printf("%s\n", name);
```

```bash
$ ./strings
sizeof = 5, strlen = 4
name[0] = 'N' (78)
name[1] = 'J' (74)
name[2] = 'I' (73)
name[3] = 'T' (84)
name[4] = 0, the terminator
nJIT
nJ
```

```
         [0]   [1]   [2]   [3]   [4]
name:  │ 'N' │ 'J' │ 'I' │ 'T' │ '\0' │    sizeof(name) == 5, strlen(name) == 4
```

**Always leave room for the `'\0'`.** A buffer that holds a 10-character name must be at least 11 `char`s long. A "string" without its terminator isn't a string, and functions like `printf("%s")` and `strlen` will run right off the end of it.

## `string.h`: Working with Strings

Since strings are arrays, `=` can't copy them and `==` can't compare them. Use the functions in `<string.h>`:

```c
char first[20] = "Hands";
char full[40];

strcpy(full, first);                /* full = first   (no '=' for arrays!) */
strcat(full, "-On with C");         /* full += "..."                       */
printf("full = \"%s\" (%zu chars)\n", full, strlen(full));

printf("%d\n", strcmp("apple", "banana") < 0);  /* apple sorts first */
printf("%d\n", strcmp("cs288", "cs288") == 0);  /* equal             */
printf("%d\n", strcmp("Zebra", "apple") < 0);   /* 'Z' (90) < 'a' (97) */

char small[6];
strncpy(small, "Highlanders", sizeof(small) - 1);
small[sizeof(small) - 1] = '\0';    /* strncpy may NOT add the '\0' */
printf("small = \"%s\"\n", small);
```

```bash
$ ./strfuncs
full = "Hands-On with C" (15 chars)
1
1
1
small = "Highl"
```

| Function | Does | Watch out |
|----------|------|-----------|
| `strlen(s)` | Number of characters before the `'\0'` | Returns `size_t`; walks the whole string every call |
| `strcpy(dst, src)` | Copy `src` (with its `'\0'`) into `dst` | `dst` must be big enough, or it overflows |
| `strncpy(dst, src, n)` | Copy at most `n` characters | Does **not** add `'\0'` if `src` is too long; add one yourself |
| `strcat(dst, src)` | Append `src` to the end of `dst` | `dst` needs room for both plus the `'\0'` |
| `strcmp(a, b)` | `0` if equal, negative if `a` sorts first, positive if `b` does | Compares character codes, so uppercase sorts before lowercase |

Never compare strings with `==`. It compares *where* the two arrays are in memory, not what's in them:

```c
char a[] = "cs350";
char b[] = "cs350";

printf("a == b       -> %s\n", a == b ? "same" : "different");
printf("strcmp(a, b) -> %s\n", strcmp(a, b) == 0 ? "same" : "different");
```

```bash
$ gcc -std=c11 -Wall -Wextra -o eq eq.c
eq.c:9:38: warning: comparison between two arrays [-Warray-compare]
$ ./eq
a == b       -> different
strcmp(a, b) -> same
```

(GCC 12 and newer warn about this. Older compilers say nothing, so don't count on the warning.)

## Reading a Line with `fgets`

`scanf("%s", buf)` reads only one word, and nothing stops it from overflowing `buf`. To read a whole line safely, use `fgets`:

```c
char line[100];

printf("Your name: ");
if (fgets(line, sizeof(line), stdin) == NULL)
    return 1;

printf("Before: [%s]\n", line);
line[strcspn(line, "\n")] = '\0';   /* chop off the newline, if any */
printf("After:  [%s]\n", line);

for (int i = 0; line[i] != '\0'; i++)
    line[i] = toupper((unsigned char) line[i]);
printf("Shout:  [%s]\n", line);
```

```bash
$ ./readline
Your name: Ada Lovelace
Before: [Ada Lovelace
]
After:  [Ada Lovelace]
Shout:  [ADA LOVELACE]
```

- `fgets(buf, size, stdin)` reads up to `size - 1` characters, stops after a newline, and always adds the `'\0'`. It returns `NULL` at end of input, so `while (fgets(...) != NULL)` reads every line until the input runs out. (At the keyboard, press `Ctrl+D` to signal end of input.)
- It **keeps the `'\n'`**, as the `Before:` line shows. `strcspn(line, "\n")` returns the index of the first newline (or the string's length if there isn't one), so writing a `'\0'` there removes it either way.
- If you mix `scanf` and `fgets`, remember that `scanf("%d", ...)` leaves the rest of the line, including its `'\n'`, unread. The next `fgets` will happily read that empty line. `caesar.c` shows the fix.

## `ctype.h`: Classifying Characters

```c
const char *sample = "Room 2506, GITC!";
int letters = 0, digits = 0, spaces = 0, other = 0;

for (int i = 0; sample[i] != '\0'; i++) {
    unsigned char c = sample[i];
    if (isalpha(c))
        letters++;
    else if (isdigit(c))
        digits++;
    else if (isspace(c))
        spaces++;
    else
        other++;
}
printf("letters=%d digits=%d spaces=%d other=%d\n", letters, digits, spaces, other);
printf("tolower('Q') = %c, isupper('q') = %d\n", tolower('Q'), isupper('q') != 0);
```

```bash
$ ./ctypes
letters=8 digits=4 spaces=2 other=2
tolower('Q') = q, isupper('q') = 0
```

| Function | True for |
|----------|----------|
| `isalpha(c)` | Letters |
| `isdigit(c)` | `'0'` to `'9'` |
| `isalnum(c)` | Letters or digits |
| `isspace(c)` | Space, tab, newline, ... |
| `isupper(c)` / `islower(c)` | Upper / lowercase letters |
| `toupper(c)` / `tolower(c)` | Return the converted character (non-letters come back unchanged) |

The `is...` functions return "nonzero" for true, not necessarily `1`. And pass them an `unsigned char` value: a plain `char` can be negative for non-ASCII bytes, and passing a negative value (other than `EOF`) is undefined behavior. (Don't worry about `const char *` in the snippet yet; it's a pointer to a string, coming up in Section 2.)

<details>
<summary>Compiling without <code>make</code></summary>

`make` just runs these commands for you. To practice compiling by hand, run them yourself from this challenge's directory, then start the program directly (for example `./textstats`):

```bash
# Programs that `make check` tests
gcc -std=c11 -Wall -Wextra -g -o textstats textstats.c
gcc -std=c11 -Wall -Wextra -g -o palindrome palindrome.c
gcc -std=c11 -Wall -Wextra -g -o caesar caesar.c

# Other programs in this challenge
gcc -std=c11 -Wall -Wextra -g -o bounds bounds.c
gcc -std=c11 -Wall -Wextra -g -fsanitize=address -o bounds-asan bounds.c
```

</details>

## Exercises

This challenge has three auto-checked programs: `textstats`, `palindrome`, and `caesar`. Test the one you're working on with `make check <NAME>` (for example `make check textstats`). Plain `make check` tests all three (each test name starts with its program's name) and prints `__SUCCESS__` once all of them pass. Until you write your code, the compiler warns about unused variables and parameters; that's expected.

1. **Text statistics.** Complete `textstats.c`. It reads lines with `fgets` and counts lines, characters, letters, digits, words, and the longest line, then finds the most common letter using an array of 26 counters. The exact rules are in the file's comment. Covered by `make check textstats` (7 tests in `tests/textstats/`, including an empty file and a file with no final newline).
   ```bash
   $ make textstats; ./textstats < tests/textstats/njit.in
   Lines: 4
   Characters: 88
   Letters: 61
   Digits: 8
   Words: 18
   Longest line: 35
   Most common letter: e (9)
   ```
   `< file` feeds a file to your program's standard input, so you don't have to type it. `make run textstats` does this for you with `tests/textstats/njit.in`. To pass it your own text, pipe it in (`echo "Hello, World" | ./textstats`) or run `./textstats < yourfile.txt`.

2. **Palindromes.** In `palindrome.c`, write `reverse` (reverse a string **in place** by swapping from both ends) and `is_palindrome` (ignore case and anything that isn't a letter or digit). `main` is already written. Covered by `make check palindrome` (3 tests in `tests/palindrome/`).
   ```bash
   $ make palindrome; echo "A man, a plan, a canal: Panama!" | ./palindrome
   "A man, a plan, a canal: Panama!" reversed is "!amanaP :lanac a ,nalp a ,nam A" -> palindrome
   ```

3. **Caesar cipher.** In `caesar.c`, write `caesar`, which shifts every letter by a fixed amount, wrapping around the alphabet and keeping its case. Covered by `make check caesar` (6 tests in `tests/caesar/`). When it works, decode this with a shift of 13 (known as ROT13; doing it twice gets you back where you started):
   ```bash
   $ printf '13\nPbatenghyngvbaf, lbh penpxrq vg!\n' | make run caesar
   ```

4. **Predict the output.** What does each line print? Run it in a scratch file to check.
   ```c
   char s[10] = "hello";
   printf("%zu %zu\n", sizeof(s), strlen(s));
   s[1] = '\0';
   printf("%s %zu\n", s, strlen(s));
   printf("%c\n", s[2]);
   printf("%d\n", strcmp("cat", "car") > 0);
   printf("%d\n", 'b' - 'a' + 'A');
   ```

5. **Why throw away the rest of the line?** In `caesar.c`, comment out the `while ((c = getchar()) ...` loop (and the `int c;` above it), rebuild, and run `printf '3\nHello\n' | ./caesar | cat -A`. (`cat -A` shows each line's end as `$`.) What's the extra line, and where did it come from? Put the loop back.

6. **Off by one.** `bounds.c` has a classic off-by-one bug. Run `make run bounds`: does the output look right? Now run `make run bounds-asan` and read the report. Which line, which variable, and how many bytes past the end? Fix the loop, using the `sizeof` idiom for the length. Not covered by `make check`.

7. **Bonus:** `fgets` stops at `MAX_LINE - 1` characters. What does `textstats` report for a line longer than 255 characters? Try it with `python3 -c 'print("x" * 300)' | ./textstats`. Explain the result, then fix it: if the buffer doesn't end with a `'\n'` (and you're not at end of input), the line isn't finished yet, so don't count it as a new line.

## Checkpoint

You're ready to move on when you can:

- [ ] Declare and initialize an array, and compute its length with `sizeof`
- [ ] Pass an array to a function, and explain why the length must be passed too
- [ ] Explain what happens when you index past the end of an array (and how to catch it)
- [ ] Draw how `"NJIT"` is stored in memory, terminator included
- [ ] Copy, append, and compare strings with `string.h`, and say why `==` doesn't work
- [ ] Read lines with `fgets` until end of input and strip the newline

## Quick Reference

| Thing | Description |
|-------|-------------|
| `int a[5] = {1, 2};` | Array of 5; unlisted elements become 0 |
| `sizeof(a) / sizeof(a[0])` | Number of elements (only where `a` was declared) |
| `void f(int a[], int len)` | Arrays are passed as their starting address; pass the length too |
| `char s[] = "hi";` | 3 bytes: `'h'`, `'i'`, `'\0'` |
| `strlen`, `strcpy`, `strncpy`, `strcat`, `strcmp` | Length, copy, bounded copy, append, compare (`<string.h>`) |
| `fgets(buf, sizeof(buf), stdin)` | Read a line (keeps the `'\n'`); `NULL` at end of input |
| `buf[strcspn(buf, "\n")] = '\0';` | Strip the trailing newline |
| `isalpha isdigit isalnum isspace toupper tolower` | Character tests and conversions (`<ctype.h>`) |
| `-fsanitize=address` | Compile with AddressSanitizer to catch out-of-bounds accesses |
| `./prog < file` | Feed a file to the program's standard input |

---

**Previous:** [Functions & Scope](../04-functions/) | **Next:** [Pointers & Addresses](../../02-pointers-and-memory/01-pointers/)
