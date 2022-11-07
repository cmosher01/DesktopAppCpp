#!/bin/sh

mkdir -p tmp/cmake
cd tmp/cmake || exit 1

cmake ../.. || exit 1
cmake --build .
ret=$?

cat src/foobar.vcxproj

exit $ret
#cpack
#ls -l
