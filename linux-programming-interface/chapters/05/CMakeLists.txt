project(tlpi-05 LANGUAGES C CXX)

link_libraries(common)

add_executable(02-append-seek 02-append-seek.cc)
add_executable(03-atomic-append 03-atomic-append.cc)
add_executable(04-dup 04-dup.cc)
add_executable(05-dup 05-dup.cc)
add_executable(06-dup 06-dup.cc)

install(
    TARGETS
        02-append-seek
        03-atomic-append
        04-dup
        05-dup
        06-dup
    DESTINATION
        ${CMAKE_CURRENT_LIST_DIR}/bin
)
