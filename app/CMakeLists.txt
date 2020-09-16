cmake_minimum_required(VERSION 3.15)

project(utag LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(SOURCE_EXE main.cpp)


#        src/Game.cpp
#        src/snake.cpp)


#add_subdirectory(src)

find_library(TAGLIB taglib)

include_directories(../3dparty/taglib/)

add_compile_options(
        -std=c++17
#        -Wdev
        -Werror
        -Wall
        -Wextra
        -Wpedantic
#        -Wno-unused-parameter
)

add_executable(utag ${SOURCE_EXE})

target_link_libraries(utag -ltaglib src)

include_directories(utag ${TAGLIB_DIR})