cmake_minimum_required(VERSION 3.15)

project(src VERSION 1.0 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# set (headers tag_functions.h)

# set(sources tag_functions.cpp)


add_library(src STATIC ${headers} ${sources})

