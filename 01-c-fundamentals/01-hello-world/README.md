# Challenge 1: Hello, World!

Write your first C program, compile it, and peek at what the compiler actually does along the way.

## Learning Objectives

- Write, compile, and run a C program from the command line
- Understand the parts of a minimal C program: `#include`, `main`, `printf`, and `return`
- Name the four stages of compilation: preprocess, compile, assemble, link
- Read a compiler error message and use it to fix your code
- Use `make`, `make run`, and `make check` to build and test a challenge

## Why C?

C is over 50 years old and still everywhere: the Linux kernel, Python's interpreter, Git, SQLite, the firmware in your microwave, etc.

It sits _just_ above the hardware, so learning C helps you understand how a computer works fundamentally (memory, bytes & bits, the stack, etc.) -- oh and its used in CS288 and CS350.

## How C?

C is a **compiled** language, rather than running the `.c` file directly, a program called a **compiler** (e.g. `gcc`) translates the source code into a machine-code **executable** which is what is run.

```
hello.c  ──(gcc)──►  hello  ──(./hello)──►  "Hello, World!"
 source             executable              output
```

## Your First Program

Open the `hello.c` file in this directory with your editor of choice (`nano hello.c`, `vim hello.c`, VS Code, etc.).

Right now it's mostly empty, type in the following (type it, don't copy-paste, we want to build muscle memory here):

```c
#include <stdio.h>

int main(void)
{
    printf("Hello, World!\n");
    return 0;
}
```

Line by line:

| Line                         | Meaning                                                                                                                |
| ---------------------------- | ---------------------------------------------------------------------------------------------------------------------- |
| `#include <stdio.h>`         | import the **st**andar**d** **i**nput/**o**utput library, which is where the `printf` function is defined              |
| `int main(void)`             | Every C program starts by running the `main` function -- it takes no arguments (`void`) and returns an integer (`int`) |
| `{ ... }`                    | Curly braces group statements into a block, here, the body of the `main` function                                      |
| `printf("Hello, World!\n");` | Print text to standard out (the terminal) -- `\n` is a **newline**. Every statement ends in a `;`                      |
| `return 0;`                  | From main, return an exit code back to the shell (`0` means "success").                                                |

### Compile it

```bash
$ gcc -Wall -o hello hello.c
```

| Piece      | Meaning                                                                     |
| ---------- | --------------------------------------------------------------------------- |
| `gcc`      | The GNU C Compiler                                                          |
| `-Wall`    | Turn on (almost) **all** **w**arnings -- they're free bug reports           |
| `-o hello` | Name the **o**utput file `hello` (otherwise it's called `a.out` by default) |
| `hello.c`  | The source file to compile                                                  |

No output means it was successful. In C, silence is golden.

### Run it

```bash
$ ./hello
Hello, World!
```

The `./` means "the program named `hello` in _this_ directory." Without it, the shell only looks in your `PATH` variable for a program called `hello`.

### Check the exit code

```bash
$ echo $?
0
```

The shell variable `$?` holds the exit code of the last command you ran in your shell. Try changing `return 0;` to `return 42;`, recompile, run, and check `$?` again.

## Using `make`

Typing `gcc` flags gets old fast. Every challenge in this workshop comes with a `Makefile` that already has the commands for you:

| Command             | What it does                                                                              |
| ------------------- | ----------------------------------------------------------------------------------------- |
| `make`              | Compile the program(s) in this challenge                                                  |
| `make run`          | Compile (if needed) and run. If a challenge has several programs, it lists them           |
| `make run <NAME>`   | Compile (if needed) and run program `<NAME>`, for example `make run hello`                |
| `make check`        | Compile and run the automatic tests for every program. Prints `__SUCCESS__` when all pass |
| `make check <NAME>` | Test only program `<NAME>`, for example `make check hello`                                |
| `make clean`        | Delete compiled files                                                                     |

```bash
$ make
gcc -std=c11 -Wall -Wextra -g -o hello hello.c
$ make run hello
Hello, World!
Welcome to Hands-On with C at NJIT.
$ make check
PASS  hello

All 1 test(s) passed.
__SUCCESS__
```

You'll write your own Makefiles in [Section 5](../../05-tools-and-the-machine/01-multi-file-and-make/). For now, you just get to use them.

## Under the Hood: The Four Stages

`gcc` is actually running four separate tools in a row. You can stop it after each one to see what's happening.

```
            preprocess        compile          assemble          link
hello.c  ─────────────►  hello.i  ───────►  hello.s  ───────►  hello.o  ───────►  hello
 (C)        (cpp)       (expanded C)  (cc1)  (assembly)  (as)  (machine code) (ld) (executable)
```

### 1. Preprocess (`-E`)

The preprocessor handles every line starting with `#`. In your program, the `#include <stdio.h>` (and all other include statements) is replaces by the entire contents of that file.

```bash
$ gcc -E hello.c -o hello.i
$ wc -l hello.c hello.i
```

Your simple 7-line program just became hundreds of lines long! If you look at the very end of the `hello.i` file (with `tail hello.i`), you can see that your code is still there at the bottom.

There are other types of so-called "preprocessor directives" (lines starting with `#`), but the most common ones are `#include`, `#define`, and `#if`.

| Directive       | What it does                                                                         |
| --------------- | ------------------------------------------------------------------------------------ |
| `#include`      | Replaces that line with the contents of the referenced file                          |
| `#define`       | _defines_ a macro where every instance of it gets replaced by a value                |
| `#if` & `#else` | Conditionally compiles code depending on whether or not a constant statement is true |

You'll see examples of these and write them yourself later in the workshop.

### 2. Compile (`-S`)

After preprocessing, the compiler turns the program into **assembly**: a language comprised of human-readable CPU instructions.

```bash
$ gcc -S hello.c -o hello.s
$ cat hello.s
```

Look for `main:` and a `call` to `puts` or `printf`. (`gcc` may swap your `printf` call for the simpler `puts` function). Later you will read assembly for real (in [Section 5](../../05-tools-and-the-machine/04-c-to-assembly/)) but for now just recognize that it is a different form of your same C program.

### 3. Assemble (`-c`)

The assembler turns assembly into binary **machine code**, stored in an **object file**.

```bash
$ gcc -c hello.c -o hello.o
$ file hello.o
hello.o: ELF 64-bit LSB relocatable, x86-64, ...
```

While it may be machine code, you can't run you object file just yet, it still has a hole where `printf` should be.

### 4. Link

The linker fills in the "holes" by connecting your object file to the C standard library.

```bash
$ gcc hello.o -o hello
$ ./hello
```

This prevents duplication of these standard functions in every program.

## Reading Compiler Errors

Everyone writes code that doesn't compile, the skill is reading the errors the compiler gives you. Open `broken.c` -- it has **three** mistakes. Try to compile it:

```bash
$ gcc -Wall -o broken broken.c
broken.c:5:5: error: implicit declaration of function 'prinft'; did you mean 'printf'? ...
```

An error message has the format:

```
file:line:column: error: what went wrong
```

> **Tip:** Fix the first error first, then recompile. One mistake often causes a cascade of confusing errors below it, often making it easiest to try to address one error at a time.

<details>
<summary>Compiling without <code>make</code></summary>

`make` just runs these commands for you. To practice compiling by hand, run them yourself from this challenge's directory, then start the program directly (e.g. `./hello`):

```bash
gcc -std=c11 -Wall -Wextra -g -o hello hello.c

gcc -std=c11 -Wall -Wextra -g -o broken broken.c
```

</details>

## Exercises

1. Complete `hello.c` so that `./hello` prints **exactly** these two lines, then
   run `make check`:

   ```
   Hello, World!
   Welcome to Hands-On with C at NJIT.
   ```

2. Fix all three bugs in `broken.c` until `make broken` builds with **no errors and no warnings**. Then run `./broken`.

3. Remove the `\n` from the end of your second `printf` and run `./hello`. What happens to your shell prompt? Why? Put it back afterwards.

4. Delete `#include <stdio.h>` from `hello.c` and compile. Read the warning or error. What is the compiler trying to tell you? Put it back.

5. Run each of the four stages by hand (`-E`, `-S`, `-c`, then link). Use `ls -l` to compare the sizes of `hello.c`, `hello.i`, `hello.s`, `hello.o`, and `hello`. Which is biggest? Why do you think that is?

6. **Bonus:** Change `return 0;` to `return 300;`. Recompile, run, and check `echo $?`. The answer isn't 300 — what is it, and why? (Hint: exit codes are stored in a single byte.)

## Checkpoint

You're ready to move on when you can:

- [ ] Compile and run a C program without looking at the instructions
- [ ] Explain what `-Wall` and `-o` do
- [ ] Name the four stages of compilation and the file each one produces
- [ ] Find the file, line, and cause of a compiler error

## Quick Reference

| Command                                           | Description                                |
| ------------------------------------------------- | ------------------------------------------ |
| `gcc -Wall -o prog prog.c`                        | Compile `prog.c` into an executable `prog` |
| `./prog`                                          | Run the program in the current directory   |
| `echo $?`                                         | Show the exit code of the last command     |
| `gcc -E file.c`                                   | Stop after preprocessing                   |
| `gcc -S file.c`                                   | Stop after compiling (produces `file.s`)   |
| `gcc -c file.c`                                   | Stop after assembling (produces `file.o`)  |
| `make` / `make run` / `make check` / `make clean` | Build / run / test / clean up              |
| `make run <NAME>` / `make check <NAME>`           | Run / test just the program `<NAME>`       |

---

**Previous:** [Getting Set Up](../../00-getting-set-up/) | **Next:**
[Variables, Types & printf](../02-variables-and-types/)
