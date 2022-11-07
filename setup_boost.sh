#!/bin/sh

if [ $# -ne 1 ] ; then
    echo "usage: $0 path/to/boost/staging"
    exit 1
fi

root="$(pwd)"
echo "github workspace: $root"

xxx="$1"
cp=$(which cygpath)
if [ -x "$cp" ] ; then
    cygpath --help
    echo "using cygpath to convert path"
    cygpath -u "$1"
    xxx="$(cygpath -u "$1")"
fi
echo "boost staging directory: $xxx"
cd "$xxx" || exit 1

ls -l

cp -r boost "$root/include/"
cp -r stage/x64/Debug/lib/* "$root/lib/"

ls -l "$root/include/"
ls -l "$root/lib/"
