cmake_minimum_required(VERSION 3.12)
project(client)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS -pthread)

add_executable(client main.cpp)