cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(Chat)

add_executable(chat Main.cpp Chat.h Chat.cpp User.h Message.h)