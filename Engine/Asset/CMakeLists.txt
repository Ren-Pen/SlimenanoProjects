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

project(SlimenanoEngineAsset
    VERSION 1.0.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED 20)

set(LIB_NAME Asset)
set(TARGET_NAME ${NAMESPACE}-${LIB_NAME})

add_library(${TARGET_NAME})
add_library(${NAMESPACE}::${LIB_NAME} ALIAS ${TARGET_NAME})

target_sources(${TARGET_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/LibMain.cpp)
target_include_directories(${TARGET_NAME} PRIVATE ${PROJECT_SOURCE_DIR})

