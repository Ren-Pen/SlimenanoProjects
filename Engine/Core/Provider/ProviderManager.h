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
#    include <unordered_map>

#    include "../Base/Types.h"

#    include "IProvider.h"

namespace slimenano {

class ProviderManager {
  public:
    static auto GetInstance() -> ProviderManager&;

    ProviderManager() = default;
    ~ProviderManager();

    ProviderManager(const ProviderManager&) = delete;
    ProviderManager& operator=(const ProviderManager&) = delete;
    ProviderManager(ProviderManager&&) = delete;
    ProviderManager& operator=(ProviderManager&&) = delete;

    template <class T>
    auto RegisterProvider() -> void;

    template <class T>
    auto GetProvider() -> IProvider<T>&;

  private:
    std::unordered_map<const TypeId*, IBaseProvider*> m_Providers;
};

template <class T>
auto ProviderManager::RegisterProvider() -> void {
    auto providerPtr = new T();
    auto id = providerPtr->getTypeId();
    m_Providers[id] = providerPtr;
}

template <class T>
auto ProviderManager::GetProvider() -> IProvider<T>& {
    auto id = TypeId::Get<T>();
    return *static_cast<IProvider<T>*>(m_Providers[id]->getRawPtr());
}


} // namespace slimenano

#endif // SLIMENANO_PROJECT_ENGINE_CORE_PROVIDER_PROVIDER_MANAGER_H
