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

project(SlimenanoEngineCore
    VERSION 1.0.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED 20)

set(TARGET_NAME Slimenano-Engine-Core)

if(BUILD_SHARED_LIBS)
    add_compile_definitions(SLIMENANO_SHARED)
endif()

add_library(${TARGET_NAME})
add_library(Slimenano::Engine::Core ALIAS ${TARGET_NAME})

target_compile_definitions(${TARGET_NAME} PRIVATE SLIMENANO_CORE_LIBRARY)

target_compile_options(${TARGET_NAME} PRIVATE "$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

target_sources(${TARGET_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/Export.h)

target_sources(${TARGET_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/Application/IApplication.h)
target_sources(${TARGET_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/Application/IApplication.cpp)

target_sources(${TARGET_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/Base/Result.h)
target_sources(${TARGET_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/Base/Types.h)
target_sources(${TARGET_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/Base/Status.h)

target_sources(${TARGET_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/Engine/Engine.h)
target_sources(${TARGET_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/Engine/Engine.cpp)

target_sources(${TARGET_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/Exception/IExceptionHandler.h)
target_sources(${TARGET_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/Exception/IExceptionHandler.cpp)

target_sources(${TARGET_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/Log/ILogger.h)
target_sources(${TARGET_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/Log/ILoggerManager.h)
target_sources(${TARGET_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/Log/ILoggerManager.cpp)

target_sources(${TARGET_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/Memory/IMemoryManager.h)
target_sources(${TARGET_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/Memory/IMemoryManager.cpp)

target_sources(${TARGET_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/Module/IModule.h)

target_sources(${TARGET_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/Reflection/Reflections.h)

target_sources(${TARGET_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/Resource/IResourceManager.h)
target_sources(${TARGET_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/Resource/IResourceManager.cpp)

