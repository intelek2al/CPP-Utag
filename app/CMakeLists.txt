cmake_minimum_required(VERSION 3.15)

project(utag)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

# add_subdirectory(src)

find_library(TAGLIB taglib)

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Quick REQUIRED)


set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(Qt5Core_DIR "/Users/snikolayen/.brew/Cellar/qt/5.15.1/lib/cmake/Qt5Core")
set(Qt5_DIR "/Users/snikolayen/.brew/Cellar/qt/5.15.1/lib/cmake/Qt5")

set(CMAKE_PREFIX_PATH "/Users/snikolayen/.brew/Cellar/qt/5.15.1/lib/cmake/Qt5Core")

include_directories(../3dparty/taglib/taglib/)
include_directories(../3dparty/taglib/taglib/mpeg/)
include_directories(../3dparty/taglib/taglib/mpeg/id3v2/)
include_directories(../3dparty/taglib/taglib/frames/)
include_directories(../3dparty/taglib/taglib/toolkit)
include_directories(../build/3dparty/taglib/)
include_directories(../cmake-build-debug/3dparty/taglib/)

include_directories(src)
include_directories(${Qt5_DIR})

add_compile_options(
        -std=c++17
#        -Wdev
         -Werror
         -Wall
         -Wextra
         -Wpedantic
#        -Wno-unused-parameter
)

set(SOURCE_EXE main.cpp)
add_executable(utag ${SOURCE_EXE})
target_link_libraries(utag tag)

target_link_libraries(utag Qt5::Core)
target_link_libraries(utag Qt5::Widgets)
target_link_libraries(utag Qt5::Quick)