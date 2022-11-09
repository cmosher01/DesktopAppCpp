#!/bin/sh

set -e

mkdir -p tmp/cmake
cd tmp/cmake
[ "$1" = "--clean" ] && rm -rf *

cmake ../..
cmake --build .

cpack
ls -l
