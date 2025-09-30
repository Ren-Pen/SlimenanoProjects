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
project(gladwgl
    VERSION 2.0.8
    LANGUAGES C CXX
)

add_library(glad-wgl STATIC)

add_library(glad::wgl ALIAS glad-wgl)

target_sources(glad-wgl PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/wgl.c")
target_include_directories(glad-wgl PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_link_libraries(glad-wgl PUBLIC glad::glad)
