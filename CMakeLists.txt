cmake_minimum_required(VERSION 3.28)
project(coologger)

set(CMAKE_CXX_STANDARD 20)

add_executable(coologger example.cpp
        include/coologger.hpp)
