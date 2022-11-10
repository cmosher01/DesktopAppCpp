#!/bin/sh

set -e

uname -sr

mkdir -p tmp/cmake
cd tmp/cmake
[ "$1" = "--clean" ] && rm -rf *

case "$(uname -sr)" in
    MINGW*|MSYS*) prefix="C:/Program Files/" ;;
    *) prefix="/usr/local" ;;
esac

echo "::group::cmake"
cmake --install-prefix "$prefix" ../..
echo "::endgroup::"

echo "::group::cmake --build"
cmake --build .
echo "::endgroup::"

echo "::group::cpack"
cpack --trace-expand
echo "::endgroup::"

echo "::group::ls"
ls -l
echo "::endgroup::"
