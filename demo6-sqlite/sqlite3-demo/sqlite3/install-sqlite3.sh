#!/bin/bash

chmod 755 sqlite3
chmod 755 libsqlite3.so.0.8.6
chmod 755 libsqlite3.la

if [ ! -d "/usr/local/bin/" ]; then
    mkdir -p /usr/local/bin/
fi
if [ ! -d "/usr/local/lib/" ]; then
    mkdir -p /usr/local/lib/
fi
if [ ! -d "/usr/local/include/" ]; then
    mkdir -p /usr/local/include/
fi
if [ ! -d "/usr/local/share/man/man1/" ]; then
    mkdir -p /usr/local/share/man/man1/
fi
if [ ! -d "/usr/local/lib/pkgconfig/" ]; then
    mkdir -p /usr/local/lib/pkgconfig/
fi

cp -v sqlite3 /usr/local/bin/
cp -v sqlite3ext.h /usr/local/include/
cp -v sqlite3.h /usr/local/include/
cp -v sqlite3.1 /usr/local/share/man/man1/
cp -v sqlite3.pc /usr/local/lib/pkgconfig/
cp -v libsqlite3.so.0.8.6 /usr/local/lib/
cp -v libsqlite3.la /usr/local/lib/
cp -v libsqlite3.a /usr/local/lib/

ln -s /usr/local/lib/libsqlite3.so.0.8.6 /usr/local/lib/libsqlite3.so
ln -s /usr/local/lib/libsqlite3.so.0.8.6 /usr/local/lib/libsqlite3.so.0
      #应用程序的路径                           #桌面目录下的快捷方式名称

