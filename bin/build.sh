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

cmake --install-prefix "$prefix" ../..
cmake --build .

cpack
ls -l
