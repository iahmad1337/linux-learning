project(tlpi-49 LANGUAGES C CXX)

link_libraries(common)

add_executable(01-sig-receiver 01-sig-receiver.cc)
add_executable(01-sig-sender 01-sig-sender.cc)
add_executable(02-sig-ignore 02-sig-ignore.cc)
add_executable(03-nodefer 03-nodefer.cc)

install(
    TARGETS
        01-sig-receiver
        01-sig-sender
        02-sig-ignore
        03-nodefer
    DESTINATION
        ${CMAKE_CURRENT_LIST_DIR}/bin
)
