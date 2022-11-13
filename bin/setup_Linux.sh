#!/bin/sh

echo "::group::install dependencies"
sudo apt-get -qqqq update
sudo apt-get -qqqq install tree libboost-all-dev libwxgtk3.0-gtk3-dev
echo "::endgroup::"
