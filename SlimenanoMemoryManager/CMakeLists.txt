cmake_minimum_required(VERSION 3.15.0)

project(SlimenanoMemoryManager
        VERSION 1.0.0
        DESCRIPTION "This is slimenano memory allocator library."
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED 11)

set(SRC_DIR "${PROJECT_SOURCE_DIR}/src/slimenano/memory")

set(SRC_FILES
        "${SRC_DIR}/lib_main.cpp"
)

set(INCLUDE_FILES
        "${SRC_DIR}/IMemoryManager.hpp"
)

add_library(slimenano-memory-manager ${SRC_FILES} ${INCLUDE_FILES})