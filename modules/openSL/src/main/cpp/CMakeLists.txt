cmake_minimum_required(VERSION 3.18.1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")


set(openSL_header_dir ${CMAKE_SOURCE_DIR}/include)
set(openSL_source_dir ${CMAKE_SOURCE_DIR}/imp)
include_directories(
        ${openSL_source_dir}
)

add_library(AudioOpenSL
        SHARED
        imp/Audio.cpp
        imp/AudioOpenSLJni.cpp)

target_link_libraries(
        AudioOpenSL
        OpenSLES
)