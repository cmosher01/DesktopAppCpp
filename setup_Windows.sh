#!/bin/sh
set -x
set -e

mkdir -p lib
cd lib
vWx=3.2.1
curl -L -s -o wxMSW_Dev.7x "https://github.com/wxWidgets/wxWidgets/releases/download/v${vWx}/wxMSW-${vWx}_vc14x_x64_Dev.7z"
7z x wxMSW_Dev.7x -owx

ls -l
ls -l wx
ls -l wx/lib
ls -l wx/lib/vc14x_x64_dll

cd -
