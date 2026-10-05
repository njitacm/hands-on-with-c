#!/usr/bin/env bash
#
# verify-solutions.sh - maintainer script.
#
# For every challenge that has a solution/ directory, copy the challenge to a
# temporary directory, drop the solution files on top of the starter files,
# and run `make check`. Use this before every workshop to make sure nothing
# has rotted.
#
# Usage (from the repository root):
#   ./verify-solutions.sh            # every challenge
#   ./verify-solutions.sh 02-pointers-and-memory   # one section

set -u
root="$(cd "$(dirname "$0")" && pwd)"
filter="${1:-}"

work="$(mktemp -d)"
trap 'rm -rf "$work"' EXIT

ok=0; bad=0; failed=()

for sol in "$root"/[0-9][0-9]-*/[0-9][0-9]-*/solution; do
    [ -d "$sol" ] || continue
    chal="$(dirname "$sol")"
    rel="${chal#"$root"/}"
    case "$rel" in "$filter"*) ;; *) continue ;; esac

    # Only challenges with tested programs are verified automatically.
    grep -q '^TESTED *=' "$chal/Makefile" 2>/dev/null || { echo "SKIP  $rel (no tested programs)"; continue; }

    # MPI challenges need OpenMPI; skip them on machines without it.
    if grep -q '^CC *= *mpicc' "$chal/Makefile" && ! command -v mpicc > /dev/null 2>&1; then
        echo "SKIP  $rel (mpicc not installed)"; continue
    fi

    dest="$work/$rel"
    mkdir -p "$dest"
    cp -r "$chal"/. "$dest"/
    cp -r "$sol"/. "$dest"/
    ln -sfn "$root/.check.sh" "$work/.check.sh"
    ln -sfn "$root/.rules.mk" "$work/.rules.mk"

    make -s -C "$dest" clean > /dev/null 2>&1
    if make -s -C "$dest" check > "$dest/.log" 2>&1 && grep -q '__SUCCESS__' "$dest/.log"; then
        echo "OK    $rel"; ok=$((ok + 1))
    else
        echo "FAIL  $rel"; bad=$((bad + 1)); failed+=("$rel")
        sed 's/^/      /' "$dest/.log" | tail -20
    fi
done

echo
echo "$ok passed, $bad failed"
[ $bad -eq 0 ]
