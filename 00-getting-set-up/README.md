# Getting Set Up

Before you write any C, you need a **compiler** (which turns your code into an executable program), **make** (which runs the compiler for you), and a **clone** (copy) of this repository.

**Time:** ~15 min

Already have `gcc` and `make`? Jump straight to [Clone the Repository](#clone-the-repository).

## Learning Objectives

- Install a C toolchain on your own machine, *or* connect to NJIT's Linux servers
- Clone this repository with `git`
- Verify your setup with `check-setup.sh`
- Pick a text editor you're comfortable with

## What You Need

| Tool | What it does | Needed for |
|------|--------------|------------|
| `gcc` | The GNU C compiler | Everything |
| `make` | Runs build commands from a `Makefile` | Everything |
| `git` | Downloads (clones) this repository | Setup |
| `g++` | The GNU C++ compiler | Section 6 (C++) |
| `gdb` | The GNU debugger | Section 5 |
| `valgrind` | A memory-error detector | Section 5 |
| `mpicc` / `mpirun` | OpenMPI compiler wrapper and launcher | Section 6 (MPI challenge only) |

Only `gcc`, `make`, and `git` are required to start -- you can install the rest when you need them.

## Option 1: Your Own Machine

### Linux (Ubuntu / Debian)

```bash
$ sudo apt update
$ sudo apt install build-essential gdb valgrind git
```

`build-essential` installs `gcc`, `g++`, `make`, and the C standard library headers in one go.

<details>
<summary>Fedora / RHEL and Arch</summary>

```bash
# Fedora / RHEL
$ sudo dnf install gcc gcc-c++ make gdb valgrind git

# Arch
$ sudo pacman -S base-devel gdb valgrind git
```
</details>

### Windows: Use WSL2

Windows doesn't ship a Unix-style C toolchain. The simplest solution is to install the **Windows Subsystem for Linux**, which provides a full linux environment from within Windows.

1. Open **PowerShell as Administrator** and run:
   ```powershell
   wsl --install
   ```
2. Restart if/when it asks you to (often not required), then open **Ubuntu** from the Start menu and create a username and password.
3. Inside Ubuntu, follow the Linux (Ubuntu) instructions above.

> **Tip:** Keep your work inside the Linux file system (`~/`), not in `/mnt/c/...`. It's much faster, and file permissions behave correctly there.

<details>
<summary>Installing a WSL environment/distribution other than Ubuntu</summary>

While Ubuntu is the default, you can download almost any linux distro to use through WSL. Many of the most popular options are already packaged and available for you, to see whats available run:

```powershell
wsl --list --online
```

And then install your desired distro with: 

```powershell
wsl --install --distribution <distribution_name>
```

We recommend Fedora and Ubuntu especially, but anything should work for this workshop. 

It is also possible to setup linux distros not listed through WSL. For example, you can download the Rocky Linux WSL Image and run the following to install it:

```powershell
wsl --import RockyLinux C:\WSL\Rocky rocky-linux-10.tar
```
</details>

### macOS

```bash
$ xcode-select --install
```

This installs Apple's command line tools, including `make`, `git`, and a C compiler.

A few things to know on macOS:

- `gcc` on a Mac is really **Clang** in disguise (run `gcc --version` and you'll see). That's fine for almost every challenge.
- **`gdb` and `valgrind` don't work well on modern Macs.** Use `lldb` (installed with the command line tools) instead of `gdb`, and AddressSanitizer (`-fsanitize=address`) instead of `valgrind`. The Section 5 challenges include a `gdb` to `lldb` cheat sheet.
- If you'd rather have the exact/intended Linux experience, use Option 2 below.

## Option 2: NJIT's Linux Servers (AFS)

Every NJIT student has an account on NJIT's AFS Linux machines, which already have `gcc`, `make`, and `git` instaled. You connect with **SSH** using your UCID and password:

```bash
$ ssh <UCID>@afslogin0.njit.edu
```

Replace `<UCID>` with your own UCID (for example, `abc123`). On Windows you can run this in PowerShell, Windows Terminal, or WSL. On macOS and Linux, use the Terminal app.

> **Note:** NJIT IST occasionally changes hostnames and access rules (for example, requiring the VPN when you're off campus). Similarly, if you are on campus but have a non-NJIT VPN connected, it will often fail to connect as well. If the command above doesn't work, search **"AFS"** on Highlander Nexus (NJIT's IT help portal) for the current instructions or ask one of the volunteers for help.

AFS machines may have an older `gcc` than your laptop (gcc 11 last time we checked) -- that's fine: every challenge is written to work with GCC 8 and newer.

## Choosing an Editor

Use whatever you like and are comfortable with, but we recommend practicing with something in the terminal. Here are some good options:

| Editor | Where | Notes |
|--------|-------|-------|
| `nano` | Terminal | Easiest to learn. `Ctrl+O` saves, `Ctrl+X` exits |
| `vim` | Terminal | Powerful but has a learning curve. Run `vimtutor` to learn |
| VS Code | Desktop | Install the **C/C++** extension. Use the **Remote - SSH** for AFS or **WSL** extensions if you're on Windows |

The [Text Editors challenge](https://github.com/njitacm/hands-on-with-linux/tree/main/02-file-operations/02-text-editors) in our Hands-On With Linux Workshop covers `nano` and `vim`.

## Clone the Repository

```bash
$ git clone https://github.com/njitacm/hands-on-with-c.git
$ cd hands-on-with-c
$ ls
00-getting-set-up  02-pointers-and-memory  04-structs-and-data-structures  06-going-further  ...
```

**Cloning** downloads the whole workshop, including the starter code you'll edit. If the workshop gets updated later, you can pull the changes in with `git pull`.

## Check Your Setup

Run the setup checker script from the root of the repository -- you should see something that looks like:

```bash
$ ./00-getting-set-up/check-setup.sh
Required tools:
  found    gcc        gcc (GCC) 15.3.0
  found    make       GNU Make 4.4.1

Optional tools (you can install these later):
  found    g++        g++ (GCC) 15.3.0
  missing  gdb        optional, used in Section 5 (Debugging with GDB)
  missing  valgrind   optional, used in Section 5 (Finding Memory Bugs)
  found    objdump    GNU objdump (GNU Binutils) 2.46
  missing  mpicc      optional, used in Section 6 (MPI)

Test-compiling a C program...
  C compiler works!

You're all set. Head to 01-c-fundamentals/01-hello-world to begin.
__SUCCESS__
```

Your version numbers will be different. That's fine. If you see `__SUCCESS__`, you're ready to go.

## Exercises

1. Install the toolchain (Option 1) or SSH into AFS (Option 2).
2. Clone this repository and `cd` into it.
3. Run `./00-getting-set-up/check-setup.sh` and get `__SUCCESS__`.
4. Run `gcc --version` and `make --version`. Which versions do you have?
5. Open `01-c-fundamentals/01-hello-world/hello.c` in your editor, add a blank line, save, and quit. If you can do that, your editor is ready.

## Checkpoint

You're ready to move on when:

- [ ] `check-setup.sh` prints `__SUCCESS__`
- [ ] You can open, edit, and save a file in your editor
- [ ] You know where this repository lives on your machine (run `pwd` inside it)

---

**Next:** [Section 1: C Fundamentals](../01-c-fundamentals/)
