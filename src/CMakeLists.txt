cmake_minimum_required(VERSION 3.2)
add_library(blk
    lib.cpp
    handler.cpp
    brace_handler.cpp
    command_handler.cpp
    handler_fabric.cpp
    bulk.cpp
    bulk_proxy.cpp
    output_helper.cpp
    )
set_target_properties(blk PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)
