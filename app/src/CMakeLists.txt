cmake_minimum_required(VERSION 3.15)

project(src VERSION 1.0 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Quick REQUIRED)

find_library(TAGLIB taglib)

set (headers
        tag_functions.h
        )

set(sources
        tag_functions.cpp
        )


add_library(src
         STATIC ${headers} ${sources})


target_link_libraries(src tag)
target_link_libraries(src Qt5::Core Qt5::Widgets Qt5::Quick)

#target_link_libraries(src PRIVATE Qt${QT_VERSION_MAJOR}::Core)
#target_link_libraries(src PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
#target_link_libraries(src PRIVATE Qt${QT_VERSION_MAJOR}::Quick)

#target_link_libraries(src Qt5::Widgets)
#target_link_libraries(src Qt5::Quick)

#target_include_directories(src INTERFACE "$CMAKE_CURRENT_SOURCE_DIR}/src/")

