# Challenge 2: Pointer Arithmetic & Arrays

Find out how `arr[i]` really works by walking through arrays and strings with pointers, and write your own versions of `strlen` and `strcpy`.

**Difficulty:** Intermediate &nbsp;·&nbsp; **Time:** ~45 min &nbsp;·&nbsp; **Course tie-in:** CS288 Wk 7 (pointer variables & memory addresses), CS350 Ch. 3 (array allocation & access)

## Learning Objectives

- Predict the address `p + n` points to, for pointers of different types
- Explain why `arr[i]` and `*(arr + i)` are the same thing
- Recognize when an array **decays** to a pointer, and why `sizeof` "breaks" inside a function
- Walk through arrays and strings with pointers instead of indexes
- Subtract and compare pointers, and use `ptrdiff_t` / `%td`
- Use `const` to promise a function won't modify what a pointer points to

> **Trying the snippets:** each example that shows a `$ ./name` run is either a file in this directory (`make name`) or was saved as `name.c` and built with `gcc -std=c11 -Wall -Wextra -o name name.c`. Type them in and run them yourself.

## Arrays Are Contiguous

An array is a block of same-sized boxes, one right after another, with no gaps. For `int nums[4] = {10, 20, 30, 40};` (each `int` is 4 bytes):

```
 address:   0x...748    0x...74c    0x...750    0x...754
           ┌──────────┬──────────┬──────────┬──────────┐
 nums:     │    10    │    20    │    30    │    40    │
           └──────────┴──────────┴──────────┴──────────┘
 index:       [0]         [1]         [2]         [3]
```

Because there are no gaps, the address of any element is easy to compute:

```
&nums[i]  ==  (start of nums)  +  i * sizeof(int)
```

That one formula is how the CPU finds array elements. In CS350 Chapter 3 you'll see the compiler turn `nums[i]` into a single x86 instruction that computes exactly `start + 4*i`.

## Pointer Arithmetic Scales by the Type

If `p` is a pointer, then `p + 1` doesn't mean "the next byte." It means **the next element**: C multiplies by `sizeof(*p)` for you. `walk.c` shows this for three types side by side:

```bash
$ make run walk
        int *           char *          double *
p + 0   0x7fffc242f748  0x7fffc242f740  0x7fffc242f720
p + 1   0x7fffc242f74c  0x7fffc242f741  0x7fffc242f728
p + 2   0x7fffc242f750  0x7fffc242f742  0x7fffc242f730
p + 3   0x7fffc242f754  0x7fffc242f743  0x7fffc242f738

nums[2]     = 30
*(nums + 2) = 30
*(ip + 2)   = 30
ip[2]       = 30

end - ip    = 4 elements
```

(Your addresses will differ; look at the *differences* between rows.) Each step adds 4 bytes for `int *` (`...748`, `...74c`, `...750`; remember these are hex, so `8 + 4 = c`), 1 byte for `char *`, and 8 bytes for `double *`.

| Pointer type | `sizeof(*p)` | `p + 1` moves forward by |
|--------------|-------------|--------------------------|
| `char *` | 1 | 1 byte |
| `int *` | 4 | 4 bytes |
| `double *` | 8 | 8 bytes |
| `T *` | `sizeof(T)` | `sizeof(T)` bytes |

This is why pointer types matter: the type is how C knows how far to step.

## `arr[i]` Is Just `*(arr + i)`

Here's the secret: C doesn't really have an "array indexing" operation. The C standard *defines* `a[i]` as `*(a + i)`: "start at `a`, step forward `i` elements, follow the pointer." That's why all four lines above print 30.

Here `ip` points at element 0, and `ip + 2` points at element 2:

```
     ip           ip + 2
     │              │
     ▼              ▼
  ┌──────┬──────┬──────┬──────┐
  │  10  │  20  │  30  │  40  │   nums
  └──────┴──────┴──────┴──────┘
    [0]    [1]    [2]    [3]
```

A fun (but useless) consequence: since `a + i == i + a`, the expression `2[nums]` is also 30. Don't ever write that in real code.

## Array Decay

You just did `int *ip = nums;` without an `&`. That works because in almost every expression, **an array's name automatically converts ("decays") to a pointer to its first element**. `nums` becomes `&nums[0]`.

This is why:

- `scanf("%s", name)` needs no `&` (`name` already decays to a `char *`)
- a function declared `void f(int arr[])` really receives an `int *`; the two declarations mean *exactly* the same thing for a parameter
- arrays are effectively "passed by reference": the function gets the address, so it can change the caller's elements

An array and a pointer are still **not** the same thing. An array *is* the boxes; a pointer *holds the address* of a box. You can do `ip = ip + 1`, but you can't do `nums = nums + 1` (an array name can't be reassigned). And the decay doesn't happen inside `sizeof` or with `&`.

### `sizeof` an array vs. a pointer

Inside the function that declared it, `sizeof` on an array gives the size of the whole array. Pass that array to a function and it's just a pointer. `sizes.c` shows the classic bug:

```c
void print_all(int arr[])
{
    /* BUG: inside this function, arr is NOT an array */
    int n = sizeof(arr) / sizeof(arr[0]);
    ...
```

```bash
$ make sizes
gcc -std=c11 -Wall -Wextra -g -o sizes sizes.c
sizes.c: In function ‘print_all’:
sizes.c:13:19: warning: ‘sizeof’ on array function parameter ‘arr’ will return size of ‘int *’ [-Wsizeof-array-argument]
   13 |     int n = sizeof(arr) / sizeof(arr[0]);
      |                   ^
sizes.c:10:20: note: declared here
   10 | void print_all(int arr[])
      |                ~~~~^~~~~
$ ./sizes
sizeof(data)    = 32
sizeof(data[0]) = 4
sizeof(p)       = 8
main counts 8 elements
print_all thinks there are 2 elements: 1 2
```

In `main`, `data` is a real 8-element array: 32 bytes. In `print_all`, `arr` is a pointer: 8 bytes, so `8 / 4 = 2`. **A pointer doesn't know how many elements it points to.** That's why nearly every C function that takes an array also takes its length (`size_t n`), or relies on a marker at the end, like the `'\0'` at the end of a string.

## Walking a String with a Pointer

A C string is a `char` array that ends with `'\0'`. Instead of indexing with `s[i]`, you can move a pointer along it until it hits the terminator:

```c
#include <stdio.h>

int main(void)
{
    const char *msg = "NJIT";
    for (const char *p = msg; *p != '\0'; p++)
        printf("p = %p   *p = '%c'   offset %td\n", (void *)p, *p, p - msg);
    return 0;
}
```

```bash
$ ./strwalk
p = 0x558ecea908b8   *p = 'N'   offset 0
p = 0x558ecea908b9   *p = 'J'   offset 1
p = 0x558ecea908ba   *p = 'I'   offset 2
p = 0x558ecea908bb   *p = 'T'   offset 3
```

```
   msg                     p stops here, because *p == '\0'
    │                         │
    ▼                         ▼
 ┌─────┬─────┬─────┬─────┬──────┐
 │ 'N' │ 'J' │ 'I' │ 'T' │ '\0' │
 └─────┴─────┴─────┴─────┴──────┘
    ▲     ▲     ▲     ▲
   1st   2nd   3rd   4th   trip through the loop body: p == msg + 0, 1, 2, 3
```

Notice that this address (`0x55...`) looks very different from the `0x7ff...` stack addresses earlier. String literals like `"NJIT"` aren't on the stack; they're stored with the program's code in **read-only** memory. More on that in the `const` section below.

### `*p++`

You'll see `*p++` constantly in C code. Postfix `++` binds tighter than `*`, so it means `*(p++)`: "use the value `p` points to, then move `p` to the next element."

| Expression | Means | Changes |
|------------|-------|---------|
| `*p++` | read `*p`, then advance `p` | the pointer |
| `(*p)++` | add 1 to the thing `p` points to | the pointed-to value |
| `*++p` | advance `p`, then read `*p` | the pointer |

When in doubt, write two separate statements (`x = *p; p++;`). Clear beats clever.

## Subtracting and Comparing Pointers

Two pointers into the **same array** can be subtracted. The answer is the number of *elements* between them (not bytes), and its type is `ptrdiff_t` (from `<stddef.h>`), printed with `%td`. `walk.c` did this at the end: `end - ip` was 4. You can also compare them with `<`, `<=`, `==`, and so on, which makes loops like this possible:

```c
int *end = nums + 4;                   /* one past the last element */
for (int *p = nums; p < end; p++)
    printf("%d\n", *p);
```

The rules (break them and it's undefined behavior):

- You may point anywhere *inside* an array, or **one past the end** (like `end` above). You may not *dereference* the one-past-the-end pointer.
- Pointing before the start (`nums - 1`) or further past the end is UB, even if you never dereference it.
- Subtracting or `<`-comparing pointers into *different* arrays is UB. (`==` and `!=` are always fine.)

`my_strlen` in Exercise 1 is a perfect use for subtraction: move `p` to the `'\0'`, and `p - s` is the length.

## `const`: Promising Not to Write

When a function only needs to *read* through a pointer, declare the parameter as a pointer to `const`:

```c
size_t my_strlen(const char *s);                 /* won't modify the string */
char  *my_strcpy(char *dst, const char *src);    /* writes dst, only reads src */
```

`const char *s` means "`s` points to `char`s that I promise not to change through `s`." It's documentation the compiler enforces. If you break the promise, you get an error:

```c
size_t count_spaces(const char *s)
{
    size_t count = 0;
    for (; *s != '\0'; s++) {
        if (*s == ' ') {
            count++;
            *s = '_';
        }
    }
    return count;
}
```

```bash
$ gcc -std=c11 -Wall -Wextra -c constbug.c
constbug.c: In function ‘count_spaces’:
constbug.c:9:16: error: assignment of read-only location ‘*s’
    9 |             *s = '_';
      |                ^
```

Notice that `s++` was allowed: the *characters* are `const`, not the pointer itself. Read declarations right to left:

| Declaration | Read it as | Can change `*p`? | Can change `p`? |
|-------------|------------|-----------------|-----------------|
| `char *p` | pointer to char | yes | yes |
| `const char *p` | pointer to const char | **no** | yes |
| `char * const p` | const pointer to char | yes | **no** |
| `const char * const p` | const pointer to const char | **no** | **no** |

### String literals are read-only

This compiles without a single warning in C, but it's undefined behavior:

```c
char *s = "hello";     /* points INTO a string literal */
s[0] = 'J';            /* undefined behavior */
```

```bash
$ ./lit
Segmentation fault (core dumped)
```

String literals live in read-only memory, so on Linux this crashes. Make it a habit: point at literals with `const char *`, and the compiler will catch the mistake for you. If you need a modifiable copy, use an array: `char s[] = "hello";` copies the literal into your own boxes.

<details>
<summary>Compiling without <code>make</code></summary>

`make` just runs these commands for you. To practice compiling by hand, run them yourself from this challenge's directory, then start the program directly (for example `./ptrs`):

```bash
# Programs that `make check` tests
gcc -std=c11 -Wall -Wextra -g -o ptrs ptrs.c

# Other programs in this challenge
gcc -std=c11 -Wall -Wextra -g -o walk walk.c
gcc -std=c11 -Wall -Wextra -g -o sizes sizes.c
```

</details>

## Exercises

Exercises 1-4 are in `ptrs.c`. The bottom of the file is a test driver that reads commands such as `strlen hello`, `reverse 1 2 3`, and `find 7 in 3 7 9`; you don't need to change it. **The rule for these four: use pointers (`*p`, `p++`, `p < end`), not `s[i]`, and don't call the real `strlen`/`strcpy`.** `make check` can't tell how you wrote them, so that part is on your honor.

1. **`my_strlen`** (`ptrs.c`, checked). Walk a pointer to the `'\0'` and return the difference. Run `make check`; the `strlen` test should pass.

2. **`my_strcpy`** (`ptrs.c`, checked). Copy every character *including* the `'\0'`, and return the original `dst` (that's what the real `strcpy` does, so calls can be chained). The driver fills the destination with `X`s first, so if you forget the terminator you'll see `XXXX...` in the output.

3. **`reverse`** (`ptrs.c`, checked). Reverse an `int` array in place with two pointers, `lo` at the start and `hi` at the end, swapping and moving them toward each other while `lo < hi`. One test reverses an empty array (`n == 0`). What would `arr + n - 1` be then, and why is that a problem?

4. **`find`** (`ptrs.c`, checked). Return a pointer to the first element equal to `target`, or `NULL`. Look at how the driver turns your pointer back into an index (`hit - vals`). When all four pass, `make check` prints `__SUCCESS__`.

5. **Experiment** (`walk.c`, not checked). Add a fourth column for `short *` (and a `short` array). Before running, predict how far apart its addresses will be. Then change `walk.c`'s last `printf` to print `(char *)end - (char *)ip` instead. What number do you get, and why is it different from `end - ip`?

6. **Fix the bug** (`sizes.c`, not checked). Predict all five output lines, run it, then fix `print_all` so it prints all 8 numbers by adding a length parameter. `make sizes` should give no warnings.

7. **Break the promise** (`ptrs.c`, not checked). Inside your `my_strlen`, temporarily add `*s = 'X';` and compile. Read the error, then remove the line. Now look at `reverse` and `find`: could either of their array parameters be `const`? Why or why not?

8. **Bonus:** Add a `char *my_strcat(char *dst, const char *src)` to `ptrs.c` that appends `src` to the end of `dst` and returns `dst`. Write it in two lines using your `my_strlen` and `my_strcpy` (hint: `dst + my_strlen(dst)` is a pointer to `dst`'s `'\0'`). Test it from `main` in a small program of your own. Then explain to a friend what `while ((*d++ = *s++) != '\0') ;` does, step by step.

## Checkpoint

You're ready to move on when you can:

- [ ] Say exactly how many bytes `p + 3` moves for an `int *`, a `char *`, and a `double *`
- [ ] Rewrite any `a[i]` as `*(a + i)` and explain why they're equal
- [ ] Explain why `sizeof(arr)` gives 8 inside a function that receives an array
- [ ] Loop over a string or array with a pointer, using `'\0'` or an `end` pointer to stop
- [ ] Read `const char *p` and `char * const p` out loud correctly
- [ ] Explain why `char *s = "hi"; s[0] = 'H';` is a bug

## Quick Reference

| Syntax | Description |
|--------|-------------|
| `p + n`, `p - n` | Move `n` elements forward/back (`n * sizeof(*p)` bytes) |
| `a[i]` | Defined as `*(a + i)` |
| `int *p = arr;` | Array decays to `&arr[0]` |
| `p++`, `p--` | Step to the next / previous element |
| `*p++` | Use `*p`, then advance `p` |
| `q - p` | Elements between two pointers into the same array (`ptrdiff_t`, print with `%td`) |
| `p < q`, `p == q` | Compare pointers (`<` only within the same array) |
| `arr + n` | One past the end: valid to compute and compare, never to dereference |
| `sizeof(arr) / sizeof(arr[0])` | Element count; only works where `arr` is a real array, not a parameter |
| `const char *s` | Can't modify the chars through `s` |
| `char * const p` | Can't change where `p` points |

---

**Previous:** [Pointers & Addresses](../01-pointers/) | **Next:** [Dynamic Memory](../03-dynamic-memory/)
