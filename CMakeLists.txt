cmake_minimum_required(VERSION 3.22)
project(MaestroLibrary)

set(CMAKE_CXX_STANDARD 14)
add_library(MaestroLibrary SHARED lib/libMaestroControl.h lib/libMaestroControl.cpp)
add_executable(MaestroControl main.cpp)
target_link_libraries(MaestroControl MaestroLibrary)
