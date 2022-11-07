#!/bin/sh

if [ $# -ne 1 ] ; then
    echo "usage: $0 path/to/boost/staging"
    exit 1
fi

root="$(pwd)"
echo "github workspace: $root"

echo "boost staging directory: $1"
cd "$1" | exit 1

ls -l

cp -r boost "$root/include/"
cp -r stage/x64/Debug/lib/* "$root/lib/"

ls -l "$root/include/"
ls -l "$root/lib/"
