#!/bin/sh

set -x
mkdir -p tmp/cmake
cd tmp/cmake || exit 1
cmake ../.. || exit 1
cmake --build .
