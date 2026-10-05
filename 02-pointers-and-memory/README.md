# Section 2: Pointers & Memory

This is the section that makes C *C*. 

Here you'll learn what a pointer *really is*, how  arrays and pointers are secretly the same machinery, how to ask for memory at run time (and give it back), how to build 2D structures out of pointers, and how your program receives its command-line arguments (which turns out to be just another array of pointers). 

Take your time here and *draw lots of pictures* -- nearly everything in the rest of the workshop (linked lists, the call stack, threads, etc.) is built on these ideas.

## What You'll Learn

- What memory addresses are, and how `&` and `*` let you work with them
- How to write functions that change your variables and return several results through pointers
- Pointer arithmetic (why `arr[i]` is really `*(arr + i)`)
- The difference between the stack and the heap -- and how to use `malloc`, `calloc`, `realloc`, and `free` correctly
- How to recognize memory leaks, dangling pointers, double frees, and use-after-free bugs
- Three ways to build a 2D array and how each one is laid out in memory
- How to write real command-line tools with `argc`, `argv`, `strtol`, `stderr`, and exit codes

## Challenges

| # | Challenge | Description |
|---|-----------|-------------|
| 1 | [Pointers & Addresses](./01-pointers/) | `&`, `*`, `NULL`, a `swap` that works, out-parameters, and dangling pointers |
| 2 | [Pointer Arithmetic & Arrays](./02-pointer-arithmetic/) | How `arr[i]` works, array decay, walking strings, `const`; write `strlen` and `strcpy` |
| 3 | [Dynamic Memory](./03-dynamic-memory/) | Stack vs. heap, `malloc`/`free`, the classic heap bugs, and a growable array |
| 4 | [Multidimensional Arrays](./04-multidimensional-arrays/) | Row-major layout, `int **` and jagged arrays, matrix multiply, Pascal's triangle |
| 5 | [Command-Line Arguments](./05-command-line-arguments/) | `argc`/`argv`, `strtol`, `stderr`, exit codes, flags; build `calc` and `myhead` |

## Ready?

```bash
cd 01-pointers
```
