
Debian
====================
This directory contains files used to package vividd/vivid-qt
for Debian-based Linux systems. If you compile vividd/vivid-qt yourself, there are some useful files here.

## vivid: URI support ##


vivid-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install vivid-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your vividqt binary to `/usr/bin`
and the `../../share/pixmaps/vivid128.png` to `/usr/share/pixmaps`

vivid-qt.protocol (KDE)

