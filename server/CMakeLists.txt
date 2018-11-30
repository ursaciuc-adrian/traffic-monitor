cmake_minimum_required(VERSION 3.12)
project(server)

set(CMAKE_CXX_STANDARD 17)

add_executable(server main.cpp Models/Client.cpp Models/Client.h)

include_directories( ../Shared)