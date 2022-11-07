#!/bin/sh

if [ $# -ne 1 ] ; then
    echo "usage: $0 path/to/boost/staging"
    exit 1
fi

pwd
ls -l
ls -l ..
ls -l ../..

echo "boost staging: $1"
ls -l "$1"

# move staged boost (from github action build-boost in build.yaml workflow)
# to well-known location
# if [ -d lib/boost ] ; then
#     mv lib/boost/boost include/
#     cp -rv lib/boost/stage/x64/Debug/lib/* lib/
# fi
