cmake_minimum_required(VERSION 3.15.0)

project(SlimenanoObject
        VERSION 1.0.0
        DESCRIPTION "This is slimenano garbage collection library."
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED 11)

set(SRC_ROOT_DIR "${PROJECT_SOURCE_DIR}/src")
set(SRC_DIR "${SRC_ROOT_DIR}/slimenano/gc")

set(SRC_FILES
        "${SRC_DIR}/GCObject.cpp"
        "${SRC_DIR}/GCHandle.cpp"
        "${SRC_DIR}/main.cpp"
        "${SRC_DIR}/GarbageCollectorManager.cpp"
)

set(INCLUDE_FILES
        "${SRC_DIR}/GCObject.hpp"
        "${SRC_DIR}/GCHandle.hpp"
        "${SRC_DIR}/IGarbageCollector.hpp"
        "${SRC_DIR}/GarbageCollectorManager.hpp"
        "${SRC_DIR}/mem/IGCAllocator.hpp"

)

add_library(slimenano-object ${SRC_FILES} ${INCLUDE_FILES})

target_include_directories(slimenano-object PUBLIC "${SRC_ROOT_DIR}")
