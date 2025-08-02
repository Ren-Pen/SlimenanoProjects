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

add_subdirectory(SlimenanoEngine/Asset)
add_subdirectory(SlimenanoEngine/Audio)
add_subdirectory(SlimenanoEngine/Core)
add_subdirectory(SlimenanoEngine/Renderer)
add_subdirectory(SlimenanoEngine/Gameplay)
add_subdirectory(SlimenanoEngine/Scripting)

set(TARGET_NAME Slimenano-Engine)

if(BUILD_SHARED_LIBS)
    add_compile_definitions(SLIMENANO_SHARED)
endif()

add_library(${TARGET_NAME} INTERFACE)
add_library(Slimenano::Engine::API ALIAS ${TARGET_NAME})

target_include_directories(${TARGET_NAME} INTERFACE ${PROJECT_SOURCE_DIR})

target_link_libraries(${TARGET_NAME} INTERFACE Slimenano::Engine::Core)
