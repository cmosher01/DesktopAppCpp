#!/bin/sh

set -e

if [ -e "$1/CMakeCache.txt" ] ; then
    builddir="$1"
else
    mkdir -p tmp
    builddir=$(mktemp -d tmp/tmp.XXXXXXXXXX)
fi
cd $builddir

git log --max-count=1 --pretty=tformat:%H --no-abbrev-commit
git describe --tags --dirty --broken --always

echo "::group::cmake"
cmake ../..
echo "::endgroup::"

echo "::group::cmake --build"
cmake --build .
echo "::endgroup::"

if [ "$1" = "-n" ] ; then
	exit 0
fi

echo "::group::cpack"
cpack
echo "::endgroup::"
