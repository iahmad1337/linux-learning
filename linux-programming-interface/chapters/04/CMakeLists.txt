project(tlpi-04 LANGUAGES C CXX)

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
        ${CMAKE_CURRENT_LIST_DIR}/bin
)
