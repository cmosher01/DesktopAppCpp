#!/bin/sh

if [ $# -ne 1 ] ; then
    echo "usage: $0 path/to/boost/staging"
    exit 1
fi

project_dir="$(pwd)"
echo "github workspace: $project_dir"

boost_dir="$1"
cp=$(which cygpath)
if [ -x "$cp" ] ; then
    cygpath -u "$1"
    boost_dir="$(cygpath -u "$1")"
fi
echo "boost staging directory: $boost_dir"

cd "$boost_dir" || exit 1
cp -r boost "$project_dir/include/"
cp -r stage/x64/Debug/lib/* "$project_dir/lib/"
