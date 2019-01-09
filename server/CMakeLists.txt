cmake_minimum_required(VERSION 3.12)
project(server)

set(CMAKE_CXX_STANDARD 17)
file(GLOB SOURCE_FILES *.h *.cpp)

add_executable(ClionProject ${SOURCE_FILES} ../Shared/CommunicationHelper.h Handlers/Handler.h Models/Command.cpp Models/Command.h Models/Argument.cpp Models/Argument.h Models/Response.h Handlers/SpeedHandler.cpp Handlers/SpeedHandler.h Helpers/Deserializer.h Handlers/AccidentHandler.cpp Handlers/AccidentHandler.h Handlers/SubscribeHandler.cpp Handlers/SubscribeHandler.h Helpers/JsonHelper.h Handlers/NotifierHandler.cpp Handlers/NotifierHandler.h Handlers/LicensePlateHandler.cpp Handlers/LicensePlateHandler.h Handlers/LocationHandler.cpp Handlers/LocationHandler.h Helpers/Logger.h Handlers/HelpHandler.cpp Handlers/HelpHandler.h)
