cmake_minimum_required(VERSION 3.1)

if (CMAKE_VERSION VERSION_LESS "3.1")
  add_definitions(-std=c++11)
else()
  set(CMAKE_CXX_STANDARD 11)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_CXX_EXTENSIONS OFF)
endif()

project(client)

if(WIN32)
  SET(COMPILER_PATH C:/MinGW/bin)
  SET(CMAKE_C_COMPILER ${COMPILER_PATH}/gcc.exe)
  SET(CMAKE_CXX_COMPILER ${COMPILER_PATH}/g++.exe)
endif(WIN32)

#include_directories(src)

set(SOURCES
	src/main.cpp)
add_executable(client ${SOURCES})

install(TARGETS client DESTINATION build)