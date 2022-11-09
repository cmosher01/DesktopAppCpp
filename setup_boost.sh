#!/bin/sh

if [ $# -ne 1 ] ; then
    echo "usage: $0 path/to/boost/root"
    exit 1
fi

BOOST_ROOT="$1"
echo "BOOST_ROOT=$BOOST_ROOT"

PREFIX="$(pwd)"
echo "PREFIX=$PREFIX"



cd "$BOOST_ROOT" || exit 0
cp -r boost "$PREFIX/include/"
cp -r stage/x64/Debug/lib/* "$PREFIX/lib/"
