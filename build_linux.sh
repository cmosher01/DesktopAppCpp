#!/bin/sh
set -x
set -e

# move staged boost (from github action build-boost in build.yaml workflow)
# to well-known location
if [ -d .boost ] ; then
    mv -nv .boost/stage/x64/Debug/lib/cmake/Boost-* lib/boost
fi

mkdir -p tmp/cmake
cd tmp/cmake

cmake ../..
cmake --build .
ls -l src

#cpack
#ls -l
