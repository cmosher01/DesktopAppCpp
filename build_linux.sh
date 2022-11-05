#!/bin/sh

mkdir -p tmp/cmake
cd tmp/cmake
cmake ../..
cmake --build .
cd -
