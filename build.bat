@echo off

echo Skipping webserver dependencies...
rem g++ -fPIC --shared -o bin/stdHelpers.dll lib/stdHelpers.cpp
rem g++ -fPIC --shared -L. -lbin/stdHelpers -o bin/UrlHelper.dll lib/UrlHelper.cpp
rem g++ -c -o bin/Socket.o  lib/Socket.cpp
rem g++ -fPIC --shared -o bin/base64.dll lib/base64.cpp
rem g++ -c -o bin/webserver.o  lib/webserver.cpp
echo Compiling MaestroControl.dll ...
2>NUL g++ -fPIC --shared -o bin/MaestroControl.dll lib/libMaestroControl.cpp
echo Compiling MaestroControl.exe ...
rem g++  bin/Socket.o bin/webserver.o  -L. -lbin/MaestroControl -lbin/base64  -lbin/UrlHelper  -lbin/stdHelpers -lwsock32 -o bin/main.exe main.cpp
g++ -L. -lbin/MaestroControl -o bin/MaestroControl.exe main.cpp

echo Done