#!/bin/sh
set -x
set -e

cd /c/

vWx=3.2.1
curl -L -s -o wxMSW_Dev.7z "https://github.com/wxWidgets/wxWidgets/releases/download/v${vWx}/wxMSW-${vWx}_vc14x_x64_Dev.7z"
7z x wxMSW_Dev.7z -owxWidgets
curl -L -s -o wxMSW_ReleaseDLL.7z "https://github.com/wxWidgets/wxWidgets/releases/download/v${vWx}/wxMSW-${vWx}_vc14x_x64_ReleaseDLL.7z"
7z x wxMSW_ReleaseDLL.7z -owxWidgets -aoa
curl -L -s -o wxWidgets-headers.7z "https://github.com/wxWidgets/wxWidgets/releases/download/v${vWx}/wxWidgets-${vWx}-headers.7z"
7z x wxWidgets-headers.7z -owxWidgets
