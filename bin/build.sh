#!/bin/sh

set -e

if [ -e "$1/CMakeCache.txt" ] ; then
    builddir="$1"
else
    mkdir -p tmp
    builddir=$(mktemp -d tmp/tmp.XXXXXXXXXX)
fi
cd $builddir

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
