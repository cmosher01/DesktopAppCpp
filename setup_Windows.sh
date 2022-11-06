#!/bin/sh
set -x

sudo pacman -S --noconfirm libcurl

vWx=3.2.1
curl -L -O wxMSW_Dev.7x "https://github.com/wxWidgets/wxWidgets/releases/download/v$vWx/wxMSW-$vWx_vc14x_x64_Dev.7z"
curl -L -O wxMSW_ReleaseDLL.7z "https://github.com/wxWidgets/wxWidgets/releases/download/v$vWx/wxMSW-$vWx_vc14x_x64_ReleaseDLL.7z"

7z l wxMSW_Dev.7x
7z x wxMSW_Dev.7x -o lib/wxmsw

7z l wxMSW_ReleaseDLL.7x
7z x wxMSW_ReleaseDLL.7x -o lib/wxmsw
