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
#include "IMemoryManager.h"
#include "IMemoryAllocator.h"

#include "../Exception/IExceptionHandler.h"

namespace Slimenano::Core::Memory {

auto IMemoryManager::Malloc(const size_t size) -> void* {
    return Malloc(size, alignof(std::max_align_t));
}

auto IMemoryManager::OnUpdate() -> Base::Status {

    for (auto& allocator : m_Allocators) {
        auto status = allocator->OnUpdate();
        if (Base::IsFailure(status)) {
            auto pExceptionHandler = FindModule<Exception::IExceptionHandler>();
            if (pExceptionHandler != nullptr) {
                pExceptionHandler->Handle(status);
            }
        }
    }
    return Base::State(Base::StateCategory::Memory, Base::StateCode::kSuccess);
}

} // namespace Slimenano::Core::Memory
