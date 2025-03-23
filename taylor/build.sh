#!/usr/bin/env bash
set -eo pipefail
shopt -s nullglob
cd $(dirname $0)
export TERM=xterm-256color
flags="$(< compile_flags.txt) $CFLAGS $CPPFLAGS $LDFLAGS"
flags="$(printf %s "$flags" | tr -s '\n' ' ')"
printf 'Using flags %s\n' "$flags"
exec nice -n39 clang $flags src/*.c -o taylor
