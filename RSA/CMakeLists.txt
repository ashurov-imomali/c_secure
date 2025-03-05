cmake_minimum_required(VERSION 3.26)
project(RSA)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(RSA
        main.cpp
        main.h)
