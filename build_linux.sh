#!/bin/sh

set -x
root="$(pwd)"

git submodule update --init --recursive || exit 1

mkdir -p tmp/cmake
cd tmp/cmake || exit 1



cmake "$root" || exit 1
cmake --build .
cpack

ls -l
