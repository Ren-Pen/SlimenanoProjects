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
#ifndef SLIMENANO_PROJECT_ENGINE_CORE_MEMORY_I_MEMORY_MANAGER_H
#    define SLIMENANO_PROJECT_ENGINE_CORE_MEMORY_I_MEMORY_MANAGER_H

#    include <cstddef>
#    include <utility>
#    include <type_traits>
#    include "../Base/Status.h"
#    include "../Base/Export.h"
#    include "../Module/IBaseModule.h"
#    include "IMemoryAllocator.h"

namespace Slimenano::Core::Memory {

class IMemoryAllocator;

class SLIMENANO_API IMemoryManager : public Module::IBaseModule<IMemoryManager> {
  public:
    ~IMemoryManager() override = default;
    [[nodiscard]] virtual auto Malloc(size_t size, size_t alignment) -> void* = 0;
    [[nodiscard]] virtual auto Malloc(size_t size) -> void*;
    virtual auto Free(void* ptr) -> Base::Status = 0;
    virtual auto Reset() -> Base::Status = 0;

    template <class T, typename... Args>
    [[nodiscard]] auto New(Args&&... args) -> T*;

    template <class T>
    auto Delete(T* ptr) -> Base::Status;

    template <class T>
    auto GetAllocator() -> T*;

    template <class T>
    auto ReleaseAllocator(T*) -> void;

  protected:
    virtual auto AddAllocator(IMemoryAllocator* pAllocator) -> void = 0;
    virtual auto RemoveAllocator(IMemoryAllocator* pAllocator) -> void = 0;
};

template <class T>
auto IMemoryManager::GetAllocator() -> T* {
    auto pAllocator = this->New<T>(this);
    AddAllocator(pAllocator);
    return pAllocator;
}

template <class T>
auto IMemoryManager::ReleaseAllocator(T* pAllocator) -> void {
    RemoveAllocator(pAllocator);
    this->Delete(pAllocator);
}

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
    return Base::Status::Success(Base::Status::Category::Memory);
}

} // namespace Slimenano::Core::Memory

#endif
