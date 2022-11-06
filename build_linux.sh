#!/bin/sh

set -x
git submodule update --init --recursive
ls -l lib/boost/stage/x64/Release/lib
ls -l lib/boost/stage/x64/Release/lib/*
mkdir -p tmp/cmake
cd tmp/cmake || exit 1
cmake ../.. || exit 1
cmake --build .
