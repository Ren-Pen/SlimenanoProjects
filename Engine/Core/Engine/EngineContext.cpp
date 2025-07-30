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
#include <algorithm>
#include <vector>

#include "EngineContext.h"
#include "../Module/IModule.h"

namespace Slimenano::Core::Engine {

using namespace Base;
using namespace Module;

auto EngineContext::GetModules(std::vector<IModule*>& outModules) const -> Status {
    std::transform(m_modules.begin(), m_modules.end(), std::back_inserter(outModules), [](const auto& pair) {
        return pair.second;
    });
    return State(StateCategory::Internal, StateCode::kSuccess);
}

auto EngineContext::RegisterModule(Module::IModule* pModule) -> Base::Status {
    using Base::TypeId;
    using Base::State;
    using Base::StateCategory;
    using Base::StateCode;
    if (!pModule) {
        return State(StateCategory::Internal, StateCode::kInvalidParameter);
    }
    const auto typeId = pModule->GetModuleId();
    if (m_modules.find(typeId) != m_modules.end()) {
        return State(StateCategory::Internal, StateCode::kAlreadyExists);
    }
    m_modules[typeId] = pModule;
    return State(StateCategory::Internal, StateCode::kSuccess);
}

auto EngineContext::UnregisterModule(Module::IModule* pModule) -> Base::Status {
    using Base::TypeId;
    using Base::State;
    using Base::StateCategory;
    using Base::StateCode;
    if (!pModule) {
        return State(StateCategory::Internal, StateCode::kInvalidParameter);
    }
    const auto typeId = pModule->GetModuleId();
    const auto it = m_modules.find(typeId);
    if (it == m_modules.end()) {
        return State(StateCategory::Internal, StateCode::kNotFound);
    }
    if (it->second != pModule) {
        return State(StateCategory::Internal, StateCode::kNotPermitted);
    }
    m_modules.erase(typeId);
    return State(StateCategory::Internal, StateCode::kSuccess);
}

} // namespace Slimenano::Core::Engine
