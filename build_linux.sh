#!/bin/sh
set -x
set -e
root="$(pwd)"

git submodule update --init --recursive

mkdir -p tmp/cmake
cd tmp/cmake

cmake "$root"
cmake --build .
ls -l src

#cpack
#ls -l
