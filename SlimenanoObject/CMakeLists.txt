cmake_minimum_required(VERSION 3.15.0)

project(SlimenanoObject
        VERSION 1.0.0
        DESCRIPTION "This is slimenano garbage collection library."
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED 11)

set(SRC_ROOT_DIR "${PROJECT_SOURCE_DIR}/src")
set(SRC_DIR "${SRC_ROOT_DIR}/slimenano/object")

set(SRC_FILES
        "${SRC_DIR}/Object.cpp"
)

set(INCLUDE_FILES
        "${SRC_DIR}/Object.hpp"
        "${SRC_DIR}/IGarbageCollector.hpp"
)

add_library(slimenano-object ${SRC_FILES} ${INCLUDE_FILES})

target_include_directories(slimenano-object PUBLIC "${SRC_ROOT_DIR}")
