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
project(SlimenanoProject)

set(SLIMENANO_PLATFORM "WINDOWS") # Allow value WINDOWS, LINUX, MACOS, ANDROID
set(SLIMENANO_GRAPHICS "OPENGL") # Allow value OPENGL, VULKAN, DIRECTX

add_subdirectory(Libraries)
add_subdirectory(Engine)
add_subdirectory(Runtime)
add_subdirectory(Sandbox)
add_subdirectory(Reflection)
