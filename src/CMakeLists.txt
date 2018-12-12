cmake_minimum_required(VERSION 3.2)
add_library(blk SHARED lib.cpp)
set_target_properties(blk PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)
