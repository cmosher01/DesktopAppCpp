#!/bin/sh

set -e

mkdir -p tmp/cmake
cd tmp/cmake
[ "$1" = "--clean" ] && rm -rf -- *

case "$(uname -sr)" in
    MINGW*|MSYS*) prefix="C:/Program Files/" ;;
    *) prefix="/opt" ;;
esac

echo "::group::cmake"
cmake --install-prefix "$prefix" ../..
echo "::endgroup::"

echo "::group::cmake --build"
cmake --build .
echo "::endgroup::"

echo "::group::cpack"
cpack
echo "::endgroup::"

echo "::group::ls"
ls -l
echo "::endgroup::"
