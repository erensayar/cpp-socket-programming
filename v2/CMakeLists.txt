cmake_minimum_required(VERSION 2.8)

if (CMAKE_VERSION VERSION_LESS "3.1")
    add_definitions(-std=c++11)
else ()
    set(CMAKE_CXX_STANDARD 11)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif ()

project(socketChatApp)

if (WIN32)
    SET(COMPILER_PATH C:/MinGW/bin)
    SET(CMAKE_C_COMPILER ${COMPILER_PATH}/gcc.exe)
    SET(CMAKE_CXX_COMPILER ${COMPILER_PATH}/g++.exe)
endif (WIN32)

# Lib
add_subdirectory(lib/implementation)
include_directories(lib/include)

set(SOURCES
        main/MainClient.cpp
        main/MainServer.cpp)
add_library(${PROJECT_NAME} ${SOURCES})

# Link Libraries
target_link_libraries(MainClient ${PROJECT_NAME})
target_link_libraries(MainServer ${PROJECT_NAME})

install(TARGETS MainClient DESTINATION build)
install(TARGETS MainServer DESTINATION build)