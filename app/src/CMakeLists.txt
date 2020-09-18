cmake_minimum_required(VERSION 3.15)

project(src VERSION 1.0 LANGUAGES CXX)

#find_package(Qt5Core REQUIRED)
#find_package(Qt5Widgets REQUIRED)
#find_package(Qt5Quick REQUIRED)


set (headers
        dialog.h
        tag_functions.h
        )

set(sources
        dialog.cpp
        tag_functions.cpp
        )


add_library(src
         STATIC ${headers} ${sources})


target_link_libraries(src tag)

target_link_libraries(src Qt5::Core)
target_link_libraries(src Qt5::Widgets)
target_link_libraries(src Qt5::Quick)

#target_include_directories(src INTERFACE "$CMAKE_CURRENT_SOURCE_DIR}/src/")

