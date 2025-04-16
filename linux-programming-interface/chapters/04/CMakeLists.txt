cmake_minimum_required(VERSION 3.12) # Ensure compatibility with your CMake version
project(tlpi-04 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define the first executable
add_executable(tee tee.c)
add_executable(cp cp.cc)
add_executable(make_hole make_hole.cc)
add_executable(wc wc.cc)

install(
    TARGETS
        tee
        cp
        make_hole
        wc
    DESTINATION
        bin
)
