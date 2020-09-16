cmake_minimum_required(VERSION 3.15)

project(utag)

set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(app)

add_subdirectory(3dparty)

set(CMAKE_CXX_STANDARD 17)
