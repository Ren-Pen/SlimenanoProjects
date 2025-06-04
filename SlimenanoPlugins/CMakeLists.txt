cmake_minimum_required(VERSION 3.15.0)

project(SlimenanoPlugins
        VERSION 1.0.0
        DESCRIPTION "This is slimenano plugin supports library."
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED 11)

set(SRC_DIR "${PROJECT_SOURCE_DIR}/src/slimenano/plugin")

# set(SRC_FILES
#         "${SRC_DIR}/lib_main.cpp"
# )

# set(INCLUDE_FILES
#         "${SRC_DIR}/IMemoryManager.hpp"
# )

# add_library(slimenano-plugins ${SRC_FILES} ${INCLUDE_FILES})