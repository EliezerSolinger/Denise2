@echo off
if not exist build mkdir build
cd build
if not exist bin mkdir bin
cd bin
if exist boxes.exe del boxes.exe
cd ..
mingw32-make
copy boxes.exe bin
cd bin
boxes
cd ..\..\
