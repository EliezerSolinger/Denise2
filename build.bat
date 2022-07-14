@echo off
cls
if not exist build mkdir build
cd build
if not exist bin mkdir bin
rem cd bin
if exist boxes.exe del boxes.exe
rem cd ..
mingw32-make && boxes
rem copy boxes.exe bin
rem cd bin
REM boxes
cd ..\..\
