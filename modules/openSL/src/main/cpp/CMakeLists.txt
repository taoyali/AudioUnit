cmake_minimum_required(VERSION 3.18.1)

project(AudioOpenSL LANGUAGES C CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

#set(CMAKE_C_STANDARD 11)
#set(CMAKE_CXX_STANDARD 11)

set(openSL_header_dir ${CMAKE_SOURCE_DIR}/include)
set(openSL_source_dir ${CMAKE_SOURCE_DIR}/imp)


#include_directories(
#        ${openSL_header_dir}
#)

AUX_SOURCE_DIRECTORY(${openSL_source_dir} openSL_source)

add_library(${CMAKE_PROJECT_NAME}
        SHARED
            ${openSL_source}
)

target_link_libraries(${CMAKE_PROJECT_NAME}
        PRIVATE
            OpenSLES
            android
            log
            atomic)