# Welcome to Hands-On with C!

## What is Hands-On with C?

Hands-On with C is a beginner-friendly, hands-on workshop from the [NJIT ACM Student Chapter](https://github.com/njitacm). It takes you from your very first `printf` to pointers, memory, debugging, and even a short bridge into C++ at the end.

You can work through it on your own, at your own pace, or follow along at a live workshop session where a presenter walks you through each section and volunteers are walking around to answer questions. Every challenge is a short lesson followed by a set of hands-on exercises that you can check easily.

It intended to be a crash course on much of the C and systems material in the following two NJIT courses:

- **CS 288: Intensive Programming in Linux**: debugging C, binary data and bitwise operations, radix sort, pointers, dynamic multidimensional arrays, command-line arguments, structs and linked lists, file and directory operations, A* search, threads, and MPI
- **CS 350: Intro to Computer Systems**: data representation (integers, two's complement, floating point), C to assembly, the stack, buffer overflows, caches and locality, and dynamic memory allocation

> **Note:** This workshop is intended to help you prepare for and reinforce those courses however it isn't affiliated with any specific course/section. Always follow your instructor's materials and academic integrity policies.

## Why Learn C?

- **It's everywhere:** Linux, Windows and macOS kernels, Python, Git, databases, game engines, and embedded devices
- **It shows you the machine:** memory, pointers, bytes, and the stack are right in front of you rather than abstracted away
- **Other languages build on it:** C++, Java, C#, Go, Rust, and JavaScript all borrow its syntax and ideas
- **NJIT uses it:** CS288 and CS350 rely on C heavily, and so do many upper-level systems courses
- **It's a career skill:** systems programming, embedded systems, HPC, security, and game development all run on C and C++

## Workshop Structure

There are **6 sections** plus a setup guide.

### [Getting Set Up](./00-getting-set-up/)

Install a development environment (or connect to NJIT's Linux machines), clone this repo, and verify that everything works.

### [Section 1: C Fundamentals](./01-c-fundamentals/)

The core language: compiling, types, control flow, functions, arrays, and strings.

1. [Hello, World!](./01-c-fundamentals/01-hello-world/): your first program and the four stages of compilation
2. [Variables, Types & printf](./01-c-fundamentals/02-variables-and-types/): data types, `sizeof`, formatted I/O
3. [Control Flow](./01-c-fundamentals/03-control-flow/): `if`, `switch`, and loops
4. [Functions & Scope](./01-c-fundamentals/04-functions/): prototypes, pass-by-value, recursion
5. [Arrays & Strings](./01-c-fundamentals/05-arrays-and-strings/): fixed arrays, `char` arrays, and `string.h`

### [Section 2: Pointers & Memory](./02-pointers-and-memory/)

The topics that make C _C_: addresses, pointers, the heap, and `argv`.

1. [Pointers & Addresses](./02-pointers-and-memory/01-pointers/): `&`, `*`, and out-parameters
2. [Pointer Arithmetic & Arrays](./02-pointers-and-memory/02-pointer-arithmetic/): how `arr[i]` really works
3. [Dynamic Memory](./02-pointers-and-memory/03-dynamic-memory/): `malloc`, `free`, and growable arrays
4. [Multidimensional Arrays](./02-pointers-and-memory/04-multidimensional-arrays/): matrices and pointer-to-pointer
5. [Command-Line Arguments](./02-pointers-and-memory/05-command-line-arguments/): `argc`, `argv`, and real CLI tools

### [Section 3: Bits, Bytes & Data Representation](./03-data-representation/)

How computers actually store numbers.

1. [Binary, Hex & Integers](./03-data-representation/01-number-systems/): bases, two's complement, overflow
2. [Bitwise Operations](./03-data-representation/02-bitwise-operations/): masks, shifts, and flags
3. [Floating Point](./03-data-representation/03-floating-point/): IEEE 754, and why `0.1 + 0.2 != 0.3`
4. [Bytes in Memory](./03-data-representation/04-bytes-in-memory/): endianness and hexdumps
5. [Radix Sort](./03-data-representation/05-radix-sort/): sorting with digits and bits

### [Section 4: Structs, Data Structures & Files](./04-structs-and-data-structures/)

Organizing data and talking to the file system.

1. [Structs & typedef](./04-structs-and-data-structures/01-structs/): custom types, `qsort`, padding
2. [Linked Lists](./04-structs-and-data-structures/02-linked-lists/): self-referential structures
3. [Stacks & Queues](./04-structs-and-data-structures/03-stacks-and-queues/): bracket matching and RPN calculators
4. [File I/O](./04-structs-and-data-structures/04-file-io/): reading and writing text and binary files
5. [Working with Directories](./04-structs-and-data-structures/05-directories/): `opendir`, `stat`, and a mini `tree`

### [Section 5: Tools & Under the Hood](./05-tools-and-the-machine/)

Toolchains, debugging, and assembly Oh My! Learn to use powerful tools to really understand whats happening under the hood.

1. [Multi-File Programs & Make](./05-tools-and-the-machine/01-multi-file-and-make/): headers, linking, Makefiles
2. [Debugging with GDB](./05-tools-and-the-machine/02-debugging-with-gdb/): breakpoints, backtraces, watchpoints
3. [Finding Memory Bugs](./05-tools-and-the-machine/03-finding-memory-bugs/): Valgrind and AddressSanitizer
4. [From C to Assembly](./05-tools-and-the-machine/04-c-to-assembly/): reading x86-64
5. [The Call Stack & Buffer Overflows](./05-tools-and-the-machine/05-the-stack/): stack frames and staying safe
6. [Caches & Locality](./05-tools-and-the-machine/06-caches-and-locality/): why loop order matters

### [Section 6: Going Further](./06-going-further/)

Parallelism, C++, and a capstone project (these challenges can be done in any order).

1. [Multithreading with pthreads](./06-going-further/01-threads/): threads, races, and mutexes
2. [Parallel Computing with MPI](./06-going-further/02-mpi-basics/): message passing across processes
3. [From C to C++](./06-going-further/03-from-c-to-cpp/): `string`, `vector`, references
4. [C++ Classes & the STL](./06-going-further/04-cpp-classes-and-the-stl/): RAII, operators, containers
5. [Capstone: Maze Pathfinder](./06-going-further/05-capstone-pathfinder/): BFS and A* search, using everything you've learned

> **Note:** Each challenge is expected to take roughly 20 to 45 minutes. If working self paced, The whole workshop is about 15 to 20 hours of work, so spread it over a couple weeks.

---

## Getting Started

### Prerequisites

- Some programming experience in **any** language (for example, CS100 or CS113). You should know what variables, loops, and functions are.
- Basic comfort with the Linux command line (`cd`, `ls`, `cat`, editing a file) -- the first section of the [Hands-On with Linux](https://github.com/njitacm/hands-on-with-linux) covers these skills nicely.
- **No prior C experience required!**

### Setup Options

**Option 1: Your own machine**

- **Linux:** install `gcc`, `make`, `gdb`, and `valgrind` with your package manager
- **Windows:** use WSL2 (Ubuntu), then follow the Linux instructions
- **macOS:** install the Xcode Command Line Tools (`xcode-select --install`)

**Option 2: NJIT's Linux servers (AFS)**

- SSH into NJIT's AFS Linux machines with your UCID. They already have `gcc` and `make`.

Full step-by-step instructions are in **[Getting Set Up](./00-getting-set-up/)**.

### First Steps

1. **Clone this repository:**

   ```bash
   git clone https://github.com/njitacm/hands-on-with-c.git
   cd hands-on-with-c
   ```

2. **Check your setup:**

   ```bash
   ./00-getting-set-up/check-setup.sh
   ```

3. **Start Section 1:**
   ```bash
   cd 01-c-fundamentals/01-hello-world
   cat README.md
   ```

## How Every Challenge Works

Each challenge folder contains:

| File          | Purpose                                                                |
| ------------- | ---------------------------------------------------------------------- |
| `README.md`   | The lesson: concepts, examples, exercises, and a checkpoint            |
| `*.c` / `*.h` | Starter code with `TODO` comments for you to complete                  |
| `Makefile`    | Builds and tests your code for you                                     |
| `tests/NAME/` | The expected outputs that `make check` compares program `NAME` against |

Every challenge uses the same commands:

| Command                  | What it does                                                                  |
| ------------------------ | ----------------------------------------------------------------------------- |
| `make`                   | Compile every program in the challenge                                        |
| `make run`               | Run the challenge's program. If there are several, it lists them              |
| `make run <NAME>`        | Run program `<NAME>` (for example `make run pascal`)                          |
| `make run <NAME> [ARGS]` | Run `<NAME>` with arguments (for example `make run calc 3 + 4`)               |
| `make check`             | Test **every** program in the challenge (same as `make check all`)            |
| `make check <NAME>`      | Test only program `<NAME>`, which keeps the output short while you work on it |
| `make clean`             | Delete compiled files                                                         |

`make run` and `make check` compile anything that changed first, so you never need to run `make` by itself. You can also pipe input into a program: `echo 5 | make run pascal`.

> Arguments that start with `-` are read by `make` itself, not your program. For those, run the program directly: `./myhead -n 3`.

Each program's tests live in `tests/NAME/`. When **every** test (for all the exercises) in the challenge passes, `make check` prints:

```text
All 12 test(s) passed.
__SUCCESS__
```

Where "12" would however many tests there are for that given challenge.

## How to Use This Workshop

1. It is best to do the **Sections** and **Challenges** in order, generally each one assumes you've done the ones before it
2. `cd` into a challenge directory and read its `README.md`. _Type the example templates yourself instead of copy-pasting them_ -- you'll learn more from your own typos than from someone else's working code
3. Do the **Exercises** at the end of each README and keep checking them until all the tests pass
4. Use the Makefile in every challenge:
   - `make` compiles the challenge's programs
   - `make run <NAME>` compiles and runs program `<NAME>` (plain `make run` lists the choices when there are several)
   - `make check <NAME>` tests just the program you're working on; `make check` tests everything and prints `__SUCCESS__` when it all passes
   - `make clean` deletes the compiled files
5. _Pay attention to warnings_ -- every Makefile compiles with `-Wall -Wextra`, and a warning is usually a bug (with the exception of unfinished starter code warning about unused variables until you write it)
6. Stuck? Re-read the concept section, add some `printf`s to see what your program is really doing (poor man's debugging, you'll learn GDB later), and look at the failing test in `tests/NAME/` -- also refer to the [Troubleshooting](#troubleshooting) section below
7. Before moving on, go through the **Checkpoint** list at the end of the README, remember that sections 1 through 5 build on each other

## Tips for Success

- **Type, don't copy-paste:** Your fingers learn syntax faster than your eyes do
- **Compile early, compile often:** Write a few lines, compile, and run. Don't write 100 lines and then compile
- **Read the _first_ error message:** Fix it, recompile, and repeat
- **Don't ignore warnings:** `-Wall` warnings are bugs the compiler found for you. Fix them, even if they're not causing issues yet
- **Predict, then run:** Before you run something, guess how it will behave or what it will print. You learn the most from being wrong
- **Draw pictures:** Boxes and arrows on paper make pointers click. Writing paper notes and diagrams in general helps you learn more
- **Help other:.** Explaining a concept to a neighbor is the fastest way to learn it yourself (the Feynmann method) -- help others and yourself

## Additional Resources

Resources we think you should use:

- [cppreference.com](https://en.cppreference.com/): the reference for the C and C++ standard libraries
- [Compiler Explorer](https://godbolt.org/): see the assembly for any C code, live
- [Beej's Guide to C Programming](https://beej.us/guide/bgc/): free, friendly, and thorough

Resources you professors think you should use:

- _The C Programming Language_ (K&R), 2nd ed., by Kernighan and Ritchie (used in CS288 and CS350 -- and a genuinely great resource)
- [_Computer Systems: A Programmer's Perspective_](https://csapp.cs.cmu.edu/) (CS:APP), by Bryant and O'Hallaron (the CS350 textbook)
- [_Dive Into Systems_](https://diveintosystems.org/): a free online systems textbook (recommended in CS288 by Dale)

## Troubleshooting

**`gcc: command not found` or `make: command not found`**

- See [Getting Set Up](./00-getting-set-up/) to install the toolchain
- On Ubuntu or WSL, run `sudo apt install build-essential`

**`make check` says FAIL**

- Read the side-by-side diff: the left column is expected output, the right is yours
- Check spacing, capitalization, and missing newlines (`\n`). The tests compare output exactly.

**`Segmentation fault (core dumped)`**

- Your program touched memory it doesn't own, usually a bad pointer or an array index out of bounds
- [Debugging with GDB](./05-tools-and-the-machine/02-debugging-with-gdb/) and [Finding Memory Bugs](./05-tools-and-the-machine/03-finding-memory-bugs/) teach you how to find it fast. You can jump ahead to them at any time.

**Still stuck?**

- Re-read the relevant section of the README
- Run `man 3 printf` (or the name of any other C library function)
- Ask a neighbor, volunteer, or a presenter, or open an issue on this repo

---

## Contributing

Found a typo? Have a better exercise? Want to add a challenge?

1. Fork this repository
2. Create a new branch
3. Make your changes and run `./verify-solutions.sh`
4. Submit a pull request

## License

This workshop is released under the MIT License. See [LICENSE](./LICENSE) for details.

---

## Ready to Begin?

```bash
cd 00-getting-set-up
```

**Remember:** every systems programmer started out with a segfault they didn't understand. You've got this!
