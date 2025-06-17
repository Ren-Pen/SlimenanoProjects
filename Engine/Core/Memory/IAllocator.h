/*
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
*/
#pragma once
#ifndef SLIMENANO_PROJECT_ENGINE_CORE_MEMORY_I_ALLOCATOR_H
#    define SLIMENANO_PROJECT_ENGINE_CORE_MEMORY_ALLOCATOR_H
#    include <cstddef>

namespace slimenano {
class IAllocator {
  public:
    virtual auto Malloc(size_t size, size_t alignment = alignof(std::max_align_t)) -> void* = 0;
    virtual auto Free(void* ptr) -> void = 0;
    virtual ~IAllocator() = default;
};
} // namespace slimenano

#endif // SLIMENANO_PROJECT_ENGINE_CORE_MEMORY_ALLOCATOR_H
