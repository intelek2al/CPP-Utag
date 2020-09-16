cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_EXTENSIONS OFF)

set(TAGLIB_DIR "./taglib/")

#set(SFML_LIBRARY_DIR "./SFML/build/lib")


link_directories(TAGLIB_DIR)
#include_directories()

#find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)

#find_package(taglib)

add_subdirectory(taglib)