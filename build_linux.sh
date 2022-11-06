#!/bin/sh

set -x

set -e

root="$(pwd)"

git submodule update --init --recursive

mkdir -p tmp/cmake
cd tmp/cmake



cmake --help
cmake "$root" --debug-trycompile
cmake --build .
cpack
