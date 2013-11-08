#!/bin/sh

rm -rf debian
mkdir -v -p debian/DEBIAN
mkdir -v -p debian/usr/bin
mkdir -v -p debian/usr/share/applications
mkdir -v -p debian/usr/share/icons

cp -v control debian/DEBIAN
cp -v  bin/$1 debian/usr/bin
cp -v *.desktop debian/usr/share/applications
cp -v *.svg debian/usr/share/icons

fakeroot dpkg --build debian

mv debian.deb $1.deb
