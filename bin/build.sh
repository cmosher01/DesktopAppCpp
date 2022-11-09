#!/bin/sh

set -e

uname -o

mkdir -p tmp/cmake
cd tmp/cmake
[ "$1" = "--clean" ] && rm -rf *

prefix="/usr/local"
[ "$(uname -o)" = "Msys" ] && prefix="C:/Program Files/"

cmake --install-prefix "$prefix" ../..
cmake --build .

cpack
ls -l
