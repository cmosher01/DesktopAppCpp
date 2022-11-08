#!/bin/sh

if [ $# -ne 1 ] ; then
    echo "usage: $0 path/to/boost/root"
    exit 1
fi

BOOST_ROOT="$1"
cp="$(which cygpath)"
if [ -x "$cp" ] ; then
    BOOST_ROOT="$(cygpath -u "$BOOST_ROOT")"
    ls -l /mingw64
    ls -l /mingw64/lib
    exit 0
fi
echo "BOOST_ROOT=$BOOST_ROOT"

PREFIX="$(pwd)"
echo "PREFIX=$PREFIX"



cd "$BOOST_ROOT" || exit 1
cp -r boost "$PREFIX/include/"
cp -r stage/x64/Debug/lib/* "$PREFIX/lib/"
