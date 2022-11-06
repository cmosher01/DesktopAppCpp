#!/bin/sh
set -x
set -e

sudo pacman -S --noconfirm libcurl

mkdir -p lib/wxmsw
cd lib/wxmsw
vWx=3.2.1
echo '======================================================================================'
curl -L -o wxMSW_Dev.7x "https://github.com/wxWidgets/wxWidgets/releases/download/v${vWx}/wxMSW-${vWx}_vc14x_x64_Dev.7z"
7z l wxMSW_Dev.7x
7z x wxMSW_Dev.7x -owxmsw
echo '======================================================================================'
curl -L -o wxMSW_ReleaseDLL.7z "https://github.com/wxWidgets/wxWidgets/releases/download/v${vWx}/wxMSW-${vWx}_vc14x_x64_ReleaseDLL.7z"
7z l wxMSW_ReleaseDLL.7x
7z x wxMSW_ReleaseDLL.7x -owxmsw
echo '======================================================================================'
cd -
