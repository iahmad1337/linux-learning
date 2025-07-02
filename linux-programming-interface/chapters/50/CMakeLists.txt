project(tlpi-50 LANGUAGES C CXX)

link_libraries(common)

add_executable(01-rlimit-mlock 01-rlimit-mlock.cc)
add_executable(02-madv-dontneed 02-madv-dontneed.cc)

install(
    TARGETS
        01-rlimit-mlock
        02-madv-dontneed
    DESTINATION
        ${CMAKE_CURRENT_LIST_DIR}/bin
)
