#!/bin/sh

echo "::group::add repos"
sudo apt-get -qqqq update
sudo apt-get -qqqq install software-properties-common
sudo add-apt-repository "deb http://mirror.math.princeton.edu/pub/ubuntu kinetic main restricted universe multiverse"
sudo apt-get -qqqq update
echo "::endgroup::"

echo "::group::install dependencies"
sudo apt-get -qqqq install libboost-all-dev libwxgtk3.2-dev
echo "::endgroup::"
