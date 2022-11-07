#!/bin/sh
set -x
set -e

# move staged boost (from github action build-boost in build.yaml workflow)
# to well-known location
if [ -d .boost ] ; then
    echo "lib/boost==================================================="
    ls -l lib/boost
    echo "lib/boost/stage/x64/Debug/lib/cmake========================="
    ls -l lib/boost/stage/x64/Debug/lib/cmake
    echo "lib/boost/stage/x64/Debug/lib/cmake/Boost-*================="
    ls -l lib/boost/stage/x64/Debug/lib/cmake/Boost-*
    echo "========================================================="


    mv -nv lib/boost/stage/x64/Debug/lib/cmake/Boost-* lib/boost/stage/x64/Debug/lib/cmake/boost
    ls -l lib/boost/stage/x64/Debug/lib/cmake
    ls -l lib/boost/stage/x64/Debug/lib/cmake/boost

fi

mkdir -p tmp/cmake
cd tmp/cmake

cmake ../..
cmake --build .
ls -l src

#cpack
#ls -l
