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

project(SlimenanoEngineSandbox
    VERSION 1.0.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED 20)

set(NAMESPACE Slimenano)

add_executable(SandBox)

target_sources(SandBox PRIVATE ${PROJECT_SOURCE_DIR}/SandBox.cpp)
target_sources(SandBox PRIVATE ${PROJECT_SOURCE_DIR}/SandBoxApplication.h)
target_sources(SandBox PRIVATE ${PROJECT_SOURCE_DIR}/SandBoxApplication.cpp)
target_sources(SandBox PRIVATE ${PROJECT_SOURCE_DIR}/SandBoxLogger.h)
target_sources(SandBox PRIVATE ${PROJECT_SOURCE_DIR}/SandBoxLogger.cpp)
target_sources(SandBox PRIVATE ${PROJECT_SOURCE_DIR}/SandBoxLoggerManager.h)
target_sources(SandBox PRIVATE ${PROJECT_SOURCE_DIR}/SandBoxLoggerManager.cpp)

if (NOT TARGET Slimenano::Engine::Runtime)
    find_package(Slimenano::Engine REQUIRED)
endif ()

target_link_libraries(SandBox Slimenano::Engine::Runtime)