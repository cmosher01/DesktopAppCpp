#!/bin/sh

# debug====================
echo "---------------------xcode-select -p"
xcode-select -p
echo "---------------------PATH"
echo "$PATH" | tr ':' '\0' | xargs -0 -n 1
echo "---------------------brew info gcc"
brew info gcc
echo "---------------------which"
which gcc
which g++
which as
echo "---------------------ls -l /usr/local/bin/gcc*"
ls -l /usr/local/bin/gcc*
echo "---------------------ls -l /usr/local/bin/g++*"
ls -l /usr/local/bin/g++*
# =========================

set -e

root="$(pwd)"

#git submodule update --init --recursive

mkdir -p tmp/cmake
cd tmp/cmake



cmake "$root" --debug-trycompile # -D CMAKE_C_COMPILER=gcc-12 -D CMAKE_CXX_COMPILER=g++-12
#cmake --build .
#cpack
