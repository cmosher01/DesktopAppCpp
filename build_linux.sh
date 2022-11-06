#!/bin/sh

set -x
git submodule update --init --recursive --remote
mkdir -p tmp/cmake
cd tmp/cmake || exit 1
cmake ../.. || exit 1
cmake --build .
