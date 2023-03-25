cmake_minimum_required(VERSION 2.8)

project(socketChatApp)

set(SOURCES
        implementation/NetworkImpl.cpp
        implementation/ClientImpl.cpp
        implementation/ServerImpl.cpp
        include/INetwork.h
        include/IClient.h
        include/IServer.h)
include_directories(include)

add_library(${PROJECT_NAME} STATIC ${SOURCES})