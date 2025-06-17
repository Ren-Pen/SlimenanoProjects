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
#ifndef SLIMENANO_PROJECT_ENGINE_CORE_PROVIDER_PROVIDER_MANAGER_H
#    define SLIMENANO_PROJECT_ENGINE_CORE_PROVIDER_PROVIDER_MANAGER_H
#    include "Base/Types.h"
#    include "Provider/IProvider.h"
#    include "Memory/Memory.h"

namespace slimenano {

class ProviderManager {

  public:
    template <typename T>
    auto RegisterProvider() -> void;
};

template <typename T>
auto ProviderManager::RegisterProvider() -> void{
    RawPtr ptr = Memory::Malloc(sizeof(T));
    IBaseProvider* provider = static_cast<IBaseProvider*>(new (ptr) T());
    auto id = provider->getTypeId();

}

} // namespace slimenano

#endif // SLIMENANO_PROJECT_ENGINE_CORE_PROVIDER_PROVIDER_MANAGER_H
