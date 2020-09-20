cmake_minimum_required(VERSION 3.15)

project(utag VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

add_subdirectory(app)
add_subdirectory(3dparty)
