cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(Chat)

add_executable(chat Main.cpp ../include/Chat.h ../source/Chat.cpp ../include/User.h ../include/Message.h)