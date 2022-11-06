#!/bin/sh
set -x

sudo apt-get -qqqq update
sudo apt-get -qqqq install software-properties-common
sudo add-apt-repository "deb http://mirror.math.princeton.edu/pub/ubuntu kinetic main restricted universe multivers"
sudo apt-get -qqqq update
sudo apt-get -qqqq install libwxgtk3.2-dev
