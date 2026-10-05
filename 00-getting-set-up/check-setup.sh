#!/usr/bin/env bash

if [ -t 1 ]; then
  GREEN=$'\e[32m'; YELLOW=$'\e[33m'; RED=$'\e[31m'; RESET=$'\e[0m'
else
  GREEN=""; YELLOW=""; RED=""; RESET=""
fi

missing_required=0

# check <command> <required|optional> <what it's for>
check() {
  if command -v "$1" > /dev/null 2>&1; then
    version="$("$1" --version 2>&1 | head -n 1)"
    printf "  ${GREEN}found${RESET}    %-10s %s\n" "$1" "$version"
  elif [ "$2" = required ]; then
    printf "  ${RED}MISSING${RESET}  %-10s needed for %s\n" "$1" "$3"
    missing_required=1
  else
    printf "  ${YELLOW}missing${RESET}  %-10s optional, used in %s\n" "$1" "$3"
  fi
}

echo "Required tools:"
check gcc      required "every challenge"
check make     required "every challenge"

echo
echo "Optional tools (you can install these later):"
check g++      optional "Section 6 (C++)"
check gdb      optional "Section 5 (Debugging with GDB)"
check valgrind optional "Section 5 (Finding Memory Bugs)"
check objdump  optional "Section 5 (From C to Assembly)"
check mpicc    optional "Section 6 (MPI)"

if [ $missing_required -ne 0 ]; then
  echo
  echo "${RED}Some required tools are missing.${RESET} See 00-getting-set-up/README.md."
  exit 1
fi

echo
echo "Test-compiling a C program..."
tmp="$(mktemp -d)"
trap 'rm -rf "$tmp"' EXIT

cat > "$tmp/test.c" <<'EOF'
#include <stdio.h>

int main(void)
{
    printf("C compiler works!\n");
    return 0;
}
EOF

if gcc -std=c11 -Wall -Wextra -o "$tmp/test" "$tmp/test.c" && [ "$("$tmp/test")" = "C compiler works!" ]; then
  echo "  ${GREEN}C compiler works!${RESET}"
else
  echo "  ${RED}Could not compile and run a test program.${RESET} See 00-getting-set-up/README.md."
  exit 1
fi

echo
echo "You're all set. Head to ../01-c-fundamentals/01-hello-world to begin."
echo "__SUCCESS__"
