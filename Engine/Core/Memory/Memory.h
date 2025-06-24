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
#ifndef SLIMENANO_PROJECT_ENGINE_CORE_MEMORY_MEMORY_H
#    define SLIMENANO_PROJECT_ENGINE_CORE_MEMORY_MEMORY_H

#    include <cstddef>
#    include <memory>
#    include <type_traits>
#    include "IMemoryManager.h"

namespace slimenano {

class Memory {
  public:
    static auto Initialize() -> void;
    static auto Malloc(size_t size, size_t alignment = alignof(std::max_align_t)) -> void*;
    static auto Free(void* ptr) -> void;

    template<class T, typename ...Args>
    static auto New(Args&&... args) -> T*;

    template<class T>
    static auto Delete(T* ptr) -> void;

    template<class T, typename ...Args>
    static auto MakeUnique(Args&&... args) -> std::unique_ptr<T>;
  private:
    static std::unique_ptr<IMemoryManager> m_MemoryManager;
};

template <class T, typename... Args>
auto Memory::New(Args&&... args) -> T* {
    static_assert(std::is_constructible_v<T, Args&&...>, "T must be constructible with given arguments");
    return new (Malloc(sizeof(T), alignof(T))) T(std::forward<Args>(args)...);
}

template<class T>
auto Memory::Delete(T* ptr) -> void {
    static_assert(std::is_constructible_v<T>, "T must be constructible with given arguments");
    if (ptr != nullptr) [[likely]] {
        ptr->~T();
        Free(ptr);
    }
}

template <class T, typename... Args>
auto Memory::MakeUnique(Args&&... args) -> std::unique_ptr<T> {
    static_assert(std::is_constructible_v<T, Args&&...>, "T must be constructible with given arguments");

    auto ptr = New<T>(std::forward<Args>(args)...);
    return std::unique_ptr<T>(ptr, &Memory::Delete<T>);
}



} // namespace slimenano

#endif // !SLIMENANO_PROJECT_ENGINE_CORE_MEMORY_MEMORY_H
