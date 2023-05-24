cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(Client)

set(SOURCES
    source/Main.cpp
    source/Chat.cpp
)

set(INCLUDES
    include/Chat.h
    include/User.h
    include/Message.h
)

add_executable(Client ${SOURCES} ${INCLUDES})

target_link_libraries(Client ws2_32)