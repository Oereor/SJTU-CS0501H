cmake_minimum_required(VERSION 4.1)
project(linear_lists)

set(CMAKE_CXX_STANDARD 20)

add_executable(linear_lists main.cpp
        stack.h
        stack.cpp
        list.h
        ArrayList.cpp
        ArrayList.h
        LinkedList.cpp
        LinkedList.h
        hw01.cpp)
