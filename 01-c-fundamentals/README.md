# Section 1: C Fundamentals

This section covers the core of, and working with, the C language: compiling a program, storing and printing data, making decisions, writing functions, and working with arrays and strings. 

If you've programmed in Python or Java, many of the ideas will be familiar but the syntax won't be. 

C makes you say exactly what type every value is, performs integer division when you might not expect it, copies arguments into functions, and lets you take a long walk right off the end of a short array (or something like that). By the end of this section you'll be ready for the topic that makes C *C*: pointers.

## What You'll Learn

- How `gcc` turns a `.c` file into a program and how to read compiler error messages
- C's basic types, `sizeof`, and formatted input and output with `printf` and `scanf`
- Integer division, implicit conversions, and casts
- `if`, `switch`, C's three loops, and the classic bugs that `-Wall -Wextra` catches
- Functions, prototypes, pass-by-value, scope, `static`, and recursion
- Splitting a program into a header and multiple `.c` files
- Fixed-size arrays, null-terminated strings, `string.h`, `ctype.h`, and reading lines with `fgets`
- What **undefined behavior** is and why C programmers worry about it

## Challenges

| # | Challenge | Description |
|---|-----------|-------------|
| 1 | [Hello, World!](./01-hello-world/) | Write, compile, and run your first program -- and see the four stages of compilation |
| 2 | [Variables, Types & printf](./02-variables-and-types/) | Data types, `sizeof`, format specifiers, integer division, casts, constants, and `scanf`. Write a bill-splitting receipt calculator |
| 3 | [Control Flow](./03-control-flow/) | Truthiness, `if`, `switch` and fallthrough, `while`/`for`/`do`-`while`, and nested loops. Write FizzBuzzBang, a diamond printer, and a Collatz explorer |
| 4 | [Functions & Scope](./04-functions/) | Prototypes, pass-by-value, local/global/`static` variables, recursion, and your first header file. Write a small math library |
| 5 | [Arrays & Strings](./05-arrays-and-strings/) | Arrays, bounds (or the lack thereof), `'\0'`-terminated strings, `string.h`, `ctype.h`, and `fgets`. Write a text analyzer, a palindrome checker, and a Caesar cipher |

## Ready?

```bash
cd 01-hello-world
```
