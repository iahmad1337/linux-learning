add_library(common)

target_sources(
    common
    PRIVATE
        src/common.cc
)

target_include_directories(
    common
    PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include
)
