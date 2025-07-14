project(tlpi-49 LANGUAGES C CXX)

link_libraries(common)

add_executable(01-cp-mmap 01-cp-mmap.cc)
add_executable(03-mmap-signals 03-mmap-signals.cc)
add_executable(04-mmap-nonlinear 04-mmap-nonlinear.cc)

install(
    TARGETS
        01-cp-mmap
        03-mmap-signals
        04-mmap-nonlinear
    DESTINATION
        ${CMAKE_CURRENT_LIST_DIR}/bin
)
