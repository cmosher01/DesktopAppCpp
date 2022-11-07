#!/bin/sh
#set -e

echo "====----------------------PATH----------------------===="
echo "$PATH" | tr ':' '\0' | xargs -0 -n 1
echo "====------------------------------------------------===="


echo "/usr/lib==================================================="
ls -l /usr/lib
echo "/usr/lib/cmake==================================================="
ls -l /usr/lib/cmake
echo "/usr/local/lib==================================================="
ls -l /usr/local/lib
echo "/usr/local/lib/cmake==================================================="
ls -l /usr/local/lib/cmake
echo "/usr/lib/x86_64-linux-gnu==================================================="
ls -l /usr/lib/x86_64-linux-gnu
echo "/usr/lib/x86_64-linux-gnu/cmake==================================================="
ls -l /usr/lib/x86_64-linux-gnu/cmake



# move staged boost (from github action build-boost in build.yaml workflow)
# to well-known location
if [ -d lib/boost ] ; then
    echo "lib/boost==================================================="
    ls -l lib/boost
    echo "lib/boost/stage/x64/Debug========================="
    ls -l lib/boost/stage/x64/Debug
    echo "lib/boost/stage/x64/Debug/lib========================="
    ls -l lib/boost/stage/x64/Debug/lib
    echo "lib/boost/stage/x64/Debug/lib/cmake========================="
    ls -l lib/boost/stage/x64/Debug/lib/cmake
    echo "========================================================="

    # mkdir -p /usr/lib/cmake
    # mv -v lib/boost/stage/x64/Debug/lib/cmake/* /usr/lib/cmake/
    # echo "/usr/lib/cmake==================================================="
    # ls -l /usr/lib/cmake
    # echo "================================================================="
fi

mkdir -p tmp/cmake
cd tmp/cmake

cmake ../..
cmake --build .
ls -l src


exit 0



#cpack
#ls -l
