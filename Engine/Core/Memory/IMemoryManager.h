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
#include "IMemoryAllocator.h"
#ifndef SLIMENANO_PROJECT_ENGINE_CORE_MEMORY_I_MEMORY_MANAGER_H
#    define SLIMENANO_PROJECT_ENGINE_CORE_MEMORY_I_MEMORY_MANAGER_H

#    include <cstddef>
#    include <utility>
#    include <type_traits>
#    include <unordered_set>
#    include "../Base/Status.h"
#    include "../Module/IBaseModule.h"

namespace Slimenano::Core::Memory {

class IMemoryAllocator;

class IMemoryManager : public Module::IBaseModule<IMemoryManager> {
  public:
    virtual ~IMemoryManager() = default;
    [[nodiscard]] virtual auto Malloc(size_t size, size_t alignment) -> void* = 0;
    [[nodiscard]] virtual auto Malloc(const size_t size) -> void*;
    virtual auto Free(void* ptr) -> Base::Status = 0;
    virtual auto Reset() -> Base::Status = 0;
    virtual auto OnUpdate() -> Base::Status;

    template <class T, typename... Args>
    [[nodiscard]] auto New(Args&&... args) -> T*;

    template <class T>
    auto Delete(T* ptr) -> Base::Status;

    auto AddAllocator(IMemoryAllocator * pAllocator) -> void;
    auto RemoveAllocator(IMemoryAllocator * pAllocator) -> void;

  private:
    std::unordered_set<IMemoryAllocator*> m_Allocators = std::unordered_set<IMemoryAllocator*>();
};

template <class T, typename... Args>
auto IMemoryManager::New(Args&&... args) -> T* {
    static_assert(std::is_constructible_v<T, Args&&...>, "T must be constructible with given arguments");
    return new (Malloc(sizeof(T), alignof(T))) T(std::forward<Args>(args)...);
}

template <class T>
auto IMemoryManager::Delete(T* ptr) -> Base::Status {
    static_assert(std::is_constructible_v<T>, "T must be constructible with given arguments");
    if (ptr != nullptr) [[likely]] {
        ptr->~T();
        return Free(ptr);
    }
    return Base::State(Base::StateCategory::Memory, Base::StateCode::kSuccess);
}

} // namespace Slimenano::Core::Memory

#endif
