cmake_minimum_required(VERSION 3.12)
project(server)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCE_FILES *.h *.cpp)

add_executable(ClionProject ${SOURCE_FILES} ${SOURCES} ../Shared/CommunicationHelper.h Handlers/Handler.h Models/Command.cpp Models/Command.h Models/Argument.cpp Models/Argument.h Models/Response.h Handlers/SpeedHandler.cpp Handlers/SpeedHandler.h Helpers/Deserializer.h)
