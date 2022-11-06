#!/bin/sh
set -x
set -e

# move staged boost (from github action build-boost in build.yaml workflow)
# to well-known location
if [ -d .boost ] ; then
    echo ".boost==================================================="
    ls -l .boost
    echo ".boost/stage/x64/Debug/lib/cmake========================="
    ls -l .boost/stage/x64/Debug/lib/cmake
    echo ".boost/stage/x64/Debug/lib/cmake/Boost-*================="
    ls -l .boost/stage/x64/Debug/lib/cmake/Boost-*
    mv -nv .boost/stage/x64/Debug/lib/cmake lib/boost
    echo "lib/boost================================================"
    ls -l lib/boost
fi

mkdir -p tmp/cmake
cd tmp/cmake

cmake ../..
cmake --build .
ls -l src

#cpack
#ls -l
