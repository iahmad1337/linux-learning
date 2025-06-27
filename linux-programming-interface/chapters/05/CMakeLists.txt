cmake_minimum_required(VERSION 3.12)
project(tlpi-05 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS -g)

# Define the first executable
add_executable(02-append-seek 02-append-seek.cc)
add_executable(03-atomic-append 03-atomic-append.cc)
add_executable(04-dup 04-dup.cc)
add_executable(05-dup 05-dup.cc)

install(
    TARGETS
        02-append-seek
        03-atomic-append
        04-dup
        05-dup
    DESTINATION
        bin
)
