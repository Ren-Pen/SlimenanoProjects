#[[
    Slimenano Engine
    Copyright (C) 2025  zyu.xiao

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
]]
#
cmake_minimum_required(VERSION 3.10.0)

project(SlimenanoEngineCoreImplement
        VERSION 1.0.0
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED 20)

set(TARGET_NAME Slimenano-Engine-Runtime-Core)

if (BUILD_SHARED_LIBS)
    add_compile_definitions(SLIMENANO_SHARED)
endif ()

add_library(${TARGET_NAME})
add_library(Slimenano::Engine::Runtime::Core ALIAS ${TARGET_NAME})

if (NOT TARGET spdlog)
    find_package(spdlog REQUIRED)
endif ()

if (NOT TARGET Slimenano::Engine::API)
    find_package(Slimenano::Engine REQUIRED)
endif ()

target_link_libraries(${TARGET_NAME} PUBLIC Slimenano::Engine::API)

target_link_libraries(${TARGET_NAME} PRIVATE spdlog::spdlog)

target_compile_definitions(${TARGET_NAME} PRIVATE SLIMENANO_LIBRARY)

target_compile_options(${TARGET_NAME} PRIVATE "$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

target_sources(${TARGET_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/Log/SPDLoggerManager.h)
target_sources(${TARGET_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/Log/SPDLoggerManager.cpp)


