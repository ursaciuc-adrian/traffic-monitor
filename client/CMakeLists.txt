cmake_minimum_required(VERSION 3.12)
project(client)

set(CMAKE_CXX_STANDARD 17)

add_executable(client main.cpp Models/Server.cpp Models/Server.h)

include_directories( ../Shared)