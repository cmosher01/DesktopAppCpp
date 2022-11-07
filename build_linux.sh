#!/bin/sh

# move staged boost (from github action build-boost in build.yaml workflow)
# to well-known location
if [ -d lib/boost ] ; then
    mv lib/boost/boost include/
    cp -rv lib/boost/stage/x64/Debug/lib/* lib/
fi

mkdir -p tmp/cmake
cd tmp/cmake || exit 1

cmake ../.. || exit 1
cmake --build . || exit 1

#cpack
#ls -l
