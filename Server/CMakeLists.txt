cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(Server)

add_executable(server Main.cpp ../include/Chat.h ../source/Chat.cpp ../include/User.h ../include/Message.h)