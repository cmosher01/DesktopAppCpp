#!/bin/sh

set -e

mkdir -p tmp/cmake
cd tmp/cmake
[ "$1" = "--clean" ] && rm -rf -- *

echo "::group::cmake"
cmake ../..
echo "::endgroup::"

echo "::group::cmake --build"
cmake --build .
echo "::endgroup::"

echo "::group::cpack"
cpack
echo "::endgroup::"

echo "::group::directory"
tree
echo "::endgroup::"
