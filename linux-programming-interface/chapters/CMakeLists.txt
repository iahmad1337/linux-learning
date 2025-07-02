cmake_minimum_required(VERSION 3.12)
project(tlpi-exercises LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS -g)

# First, the libcommon library
add_subdirectory(common)

# Then, the chapters
add_subdirectory(04)
add_subdirectory(05)
add_subdirectory(50)
