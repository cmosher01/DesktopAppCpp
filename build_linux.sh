#!/bin/sh

echo "PATH+"
echo "$PATH" | tr ':' '\0' | xargs -0 -n 1

mkdir -p tmp/cmake
cd tmp/cmake || exit 1

cmake ../.. || exit 1
cmake --build .
ret=$?


#cpack
#ls -l


exit $ret
