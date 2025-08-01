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
#include <iterator>
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
    return Status::Success(Status::Category::Internal);
}

auto EngineContext::RegisterModule(Module::IModule* pModule) -> Base::Status {
    using Base::TypeId;
    using Base::Status;
    if (!pModule) {
        return Status::NullPointerException(Status::Category::Internal);
    }
    const auto typeId = pModule->GetModuleId();
    if (m_modules.find(typeId) != m_modules.end()) {
        return Status(Status::Category::Internal, Status::Code::AlreadyExists, "Module already be register.");
    }
    m_modules[typeId] = pModule;
    return Status::Success(Status::Category::Internal);
}

auto EngineContext::UnregisterModule(Module::IModule* pModule) -> Base::Status {
    using Base::TypeId;
    using Base::Status;
    if (!pModule) {
        return Status::NullPointerException(Status::Category::Internal);
    }
    const auto typeId = pModule->GetModuleId();
    const auto it = m_modules.find(typeId);
    if (it == m_modules.end()) {
        return Status(Status::Category::Internal, Status::Code::NotFound, "Module not found.");
    }
    if (it->second != pModule) {
        return Status(Status::Category::Internal, Status::Code::NotPermitted, "Module is not owner.");
    }
    m_modules.erase(typeId);
    return Status::Success(Status::Category::Internal);
}

} // namespace Slimenano::Core::Engine
