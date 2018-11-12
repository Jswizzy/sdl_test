cmake_minimum_required(VERSION 3.12)
project(sdl_test)

set(CMAKE_CXX_STANDARD 14)

add_executable(sdl_test main.cpp)

# SDL2
set(SDL2_PATH "C:\\SDL2-2.0.9\\x86_64-w64-mingw32")

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIR})

target_link_libraries(sdl_test ${SDL2_LIBRARY})

# add images
configure_file(images/press.bmp images/press.bmp COPYONLY)
configure_file(images/up.bmp images/up.bmp COPYONLY)
configure_file(images/down.bmp images/down.bmp COPYONLY)
configure_file(images/left.bmp images/left.bmp COPYONLY)
configure_file(images/right.bmp images/right.bmp COPYONLY)