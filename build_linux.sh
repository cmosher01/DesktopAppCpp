#!/bin/sh

set -x

# debug====================
xcode-select -p
echo "$PATH" | tr ':' '\0' | xargs -0 -n 1
brew info gcc
which gcc
which g++
which as
ls -l /usr/local/bin/gcc*
ls -l /usr/local/bin/g++*
xcode-select -p
# =========================

set -e

root="$(pwd)"

git submodule update --init --recursive

mkdir -p tmp/cmake
cd tmp/cmake



cmake "$root" --debug-trycompile
cmake --build .
cpack
