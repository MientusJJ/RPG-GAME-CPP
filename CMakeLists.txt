cmake_minimum_required(VERSION 3.21)
project(IO_project)

set(CMAKE_CXX_STANDARD 20)

add_executable(IO_project Source.cpp Chambers.cpp Character.cpp Equipment.cpp Game.cpp Events.cpp Events.h)