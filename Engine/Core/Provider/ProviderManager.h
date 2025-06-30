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

#    include <stdexcept>
#    include <unordered_map>
#    include "../Base/Types.h"
#    include "../Memory/Memory.h"
#    include "IProvider.h"

namespace slimenano {

class ProviderManager {
  public:
    template <class T>
    static auto RegisterProvider(IProvider<T>* provider) -> void;

    template <class T>
    static auto GetProvider() -> IProvider<T>*;

    ProviderManager(const ProviderManager&) = delete;
    ProviderManager& operator=(const ProviderManager&) = delete;
    ProviderManager(ProviderManager&&) = delete;
    ProviderManager& operator=(ProviderManager&&) = delete;

  private:
    std::unordered_map<const TypeId*, IBaseProvider*> m_Providers;
    static auto GetInstance() -> ProviderManager&;
    ProviderManager() = default;
    ~ProviderManager();
};

template <class T>
auto ProviderManager::RegisterProvider(IProvider<T>* provider) -> void {
    auto& pm = GetInstance();
    auto id = IProvider<T>::GetTypeId();
    if (pm.m_Providers.contains(id)) {
        throw std::runtime_error("Provider already registered!");
    }
    pm.m_Providers[id] = provider;
}

template <class T>
auto ProviderManager::GetProvider() -> IProvider<T>* {
    auto& pm = GetInstance();
    auto id = TypeId::Get<T>();
    if (!pm.m_Providers.contains(id)) {
        return nullptr;
    }
    return static_cast<IProvider<T>*>(pm.m_Providers[id]->GetRawPtr());
}

} // namespace slimenano

#endif // SLIMENANO_PROJECT_ENGINE_CORE_PROVIDER_PROVIDER_MANAGER_H
