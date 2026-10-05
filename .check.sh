#!/usr/bin/env bash

# check.sh - tiny test runner used by every challenge's `make check`
#
# Usage:
#   check.sh [--partial] <program> <tests-dir> [<program2> <tests-dir2> ...]
#
# For every file  <tests-dir>/NAME.out  the program is run once:
#   - if <tests-dir>/NAME.in   exists, it is fed to the program on stdin
#   - if <tests-dir>/NAME.args exists, its contents are passed as arguments
# The program's stdout is compared against NAME.out. Whitespace at the end
# of lines and trailing blank lines are ignored.
#
# Prints __SUCCESS__ when every test passes. With --partial (used by
# `make check <program>`) only some of the challenge is being tested, so
# __SUCCESS__ is left out.

set -u

partial=0
if [ "${1:-}" = --partial ]; then
  partial=1
  shift
fi

if [ $# -lt 2 ] || [ $(($# % 2)) -ne 0 ]; then
  echo "usage: check.sh [--partial] <program> <tests-dir> [<program2> <tests-dir2> ...]" >&2
  exit 2
fi

#NOTE: use colors only when writing to a terminal.
if [ -t 1 ]; then
  GREEN=$'\e[32m'; RED=$'\e[31m'; BOLD=$'\e[1m'; RESET=$'\e[0m'
  cols="$(tput cols 2>/dev/null || echo 100)"
else
  GREEN=""; RED=""; BOLD=""; RESET=""
  cols=100
fi

normalize() {
  sed -e 's/[[:space:]]*$//' | sed -e :a -e '/^\n*$/{$d;N;ba' -e '}'
}

# show_diff <expected-file> <actual-file>
# Prints the two outputs side by side, line 1 next to line 1, and so on
# Rows that differ are marked with * (and colored red in a terminal)
# Tabs are expanded to spaces so the columns always line up
show_diff() {
  awk -v cols="$cols" -v red="$RED" -v reset="$RESET" -v maxrows=40 '
  FILENAME == ARGV[1] { e[++ne] = $0; next }
  { a[++na] = $0 }
  function row(mark, left, right, color, k, line) {
    for (k = 0; k == 0 || k < length(left) || k < length(right); k += w) {
      line = sprintf("    %s %-" w "s | %s", (k ? " " : mark),
      substr(left, k + 1, w), substr(right, k + 1, w))
      sub(/ +$/, "", line)
      print (color ? red line reset : line)
    }
  }
  END {
    w = length("expected output")
    for (i = 1; i <= ne; i++) if (length(e[i]) > w) w = length(e[i])
    for (i = 1; i <= na; i++) if (length(a[i]) > w) w = length(a[i])
    room = int((cols - 9) / 2)
    if (room < 20) room = 20
    if (w > room) w = room
    dashes = sprintf("%" w "s", ""); gsub(/ /, "-", dashes)
    row(" ", "expected output", "your output", 0)
    row(" ", dashes, dashes, 0)

    n = ne > na ? ne : na
    for (i = 1; i <= n && i <= maxrows; i++) {
      left  = i <= ne ? e[i] : "(no line)"
      right = i <= na ? a[i] : "(no line)"
      if (i <= ne && i <= na && e[i] == a[i])
        row(" ", left, right, 0)
      else
        row("*", left, right, 1)
    }
    if (n > maxrows)
      printf "      ... (%d more lines not shown)\n", n - maxrows
  }' <(expand "$1") <(expand "$2")
} # NOTE: can just be replaced with `diff --side-by-side` but has a prettier output

# `timeout` isn't installed by default on MacOS (run without a time limit)
if command -v timeout > /dev/null 2>&1; then
  limit=(timeout 10)
else
  limit=()
fi

pass=0
fail=0
want="$(mktemp)"
got="$(mktemp)"
trap 'rm -f "$want" "$got"' EXIT

while [ $# -gt 0 ]; do
  prog="$1"; tests="$2"; shift 2

  if [ ! -x "$prog" ]; then
    echo "check.sh: '$prog' does not exist or is not executable. Did it compile?" >&2
    exit 1
  fi

  label=""
  if [ $# -gt 0 ] || [ -n "${multi:-}" ]; then
    label="$(basename "$tests")"
    [ "$label" = tests ] && label="$(basename "$prog")"
    label="$label: "
  fi
  multi=1

  for expected in "$tests"/*.out; do
    [ -e "$expected" ] || { echo "check.sh: no tests found in $tests" >&2; exit 1; }
    name="$label$(basename "$expected" .out)"
    base="$tests/$(basename "$expected" .out)"
    input="$base.in"
    argsfile="$base.args"

    args=()
    if [ -f "$argsfile" ]; then
      read -r -a args < "$argsfile"
    fi

    if [ -f "$input" ]; then
      actual="$(${limit[@]+"${limit[@]}"} "$prog" ${args[@]+"${args[@]}"} < "$input" 2>/dev/null)"
    else
      actual="$(${limit[@]+"${limit[@]}"} "$prog" ${args[@]+"${args[@]}"} < /dev/null 2>/dev/null)"
    fi
    status=$?

    if [ $status -eq 124 ]; then
      echo "${RED}FAIL${RESET}  $name  (timed out after 10s -- infinite loop?)"
      fail=$((fail + 1))
      last_failed=0
      continue
    fi

    { cat "$expected"; echo; } | normalize > "$want"
    printf '%s\n' "$actual" | normalize > "$got"

    if cmp -s "$want" "$got"; then
      echo "${GREEN}PASS${RESET}  $name"
      pass=$((pass + 1))
      last_failed=0
    else
      echo "${RED}FAIL${RESET}  $name"
      show_diff "$want" "$got"
      echo
      fail=$((fail + 1))
      last_failed=1
    fi
  done
done

[ "${last_failed:-0}" -eq 1 ] || echo
if [ $fail -eq 0 ]; then
  echo "${BOLD}${GREEN}All $pass test(s) passed.${RESET}"
  if [ $partial -eq 1 ]; then
    echo "(Only some of this challenge's tests ran. Use 'make check' to run them for all exersizes.)"
  else
    echo "__SUCCESS__"
  fi
  exit 0
else
  echo "Rows marked * differ from the expected output."
  echo "${BOLD}${RED}$fail of $((pass + fail)) test(s) failed.${RESET}"
  exit 1
fi
