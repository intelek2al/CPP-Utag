cmake_minimum_required(VERSION 3.15)

project(src LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

#set(Qt5Core_DIR "~/.brew/Cellar/qt/5.15.1/lib/cmake/Qt5Core")
#set(Qt5_DIR "~/.brew/Cellar/qt/5.15.1/lib/cmake/Qt5")
#set(CMAKE_PREFIX_PATH "~/.brew/Cellar/qt/5.15.1/lib/cmake/Qt5Core")

#include_directories(${Qt5_DIR})

#find_package(Qt5Core REQUIRED)
#find_package(Qt5Widgets REQUIRED)
#find_package(Qt5Quick REQUIRED)


add_library(src
        dialog.cpp tag_functions.cpp)


target_link_libraries (src tag)


