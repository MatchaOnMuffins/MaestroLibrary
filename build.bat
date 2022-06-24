@echo off
mkdir bin
echo Compiling MaestroControl.dll ...
2>NUL g++ -fPIC --shared -o bin/MaestroControl.dll lib/libMaestroControl.cpp
echo Compiling MaestroControl.exe ...
g++ -L. -lbin/MaestroControl -o bin/MaestroControl.exe main.cpp
echo Done