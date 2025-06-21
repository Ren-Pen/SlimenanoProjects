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
]]#

cmake_minimum_required(VERSION 3.10.0)

project(SlimenanoEngine
    VERSION 1.0.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED 20)

add_subdirectory(Asset)
add_subdirectory(Audio)
add_subdirectory(Core)
add_subdirectory(Renderer)
add_subdirectory(Runtime)
add_subdirectory(Scripting)

set(TARGET_NAME Slimenano-Engine)

add_library(${TARGET_NAME})
add_library(Slimenano::Engine ALIAS ${TARGET_NAME})

target_include_directories(${TARGET_NAME} PUBLIC ${PROJECT_SOURCE_DIR})

target_sources(${TARGET_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/SlimenanoEngine.h)
target_sources(${TARGET_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/Entrypoint.cpp)
target_sources(${TARGET_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/Entrypoint.h)

target_link_libraries(${TARGET_NAME} Slimenano::Engine::Core)