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
#ifndef SLIMENANO_ENGINE_CORE_ENGINE_ENGINE_CONTEXT_H
#    define SLIMENANO_ENGINE_CORE_ENGINE_ENGINE_CONTEXT_H
#    include <vector>
#    include <unordered_map>
#    include "../Base/Types.h"
#    include "../Base/Status.h"
#    include "../Module/IModule.h"

namespace Slimenano::Core::Engine {

class EngineContext {
  public:
    template <class T>
    Base::Status RegisterModule(T* pModule);

    template <class T>
    T* FindModule();

    Base::Status GetModules(std::vector<Module::IModule*>& outModules) const;

  private:
    std::unordered_map<const Base::TypeId*, Module::IModule*> m_modules = std::unordered_map<const Base::TypeId*, Module::IModule*>();
};

template <class T>
Base::Status EngineContext::RegisterModule(T* pModule) {
    using Base::TypeId;
    using Base::State;
    using Base::StateCategory;
    using Base::StateCode;
    if (!pModule) {
        return State(StateCategory::Internal, StateCode::kInvalidParameter);
    }
    const auto typeId = TypeId::Get<T>();
    if (m_modules.find(typeId) != m_modules.end()) {
        return State(StateCategory::Internal, StateCode::kAlreadyExists);
    }
    m_modules[typeId] = pModule;
    return State(StateCategory::Internal, StateCode::kSuccess);
}

template <class T>
T* EngineContext::FindModule() {
    using Base::TypeId;
    const auto typeId = TypeId::Get<T>();
    if (m_modules.find(typeId) == m_modules.end()) {
        return nullptr;
    }
    return static_cast<T*>(m_modules[typeId]);
}

} // namespace Slimenano::Core::Engine

#endif
