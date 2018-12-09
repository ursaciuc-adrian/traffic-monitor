cmake_minimum_required(VERSION 3.12)
project(server)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES *.h *.cpp)

add_executable(ClionProject ${SOURCE_FILES} ${SOURCES} ../Shared/CommunicationHelper.h)
add_executable(server main.cpp)