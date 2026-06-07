cmake_minimum_required(VERSION 4.1)
project(Food_ordering_system)

set(CMAKE_CXX_STANDARD 20)

add_executable(Food_ordering_system main.cpp
        include/models/User.h)
