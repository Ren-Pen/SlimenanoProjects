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

#include "../Module/IModule.h"

#include "EngineContext.h"

namespace Slimenano::Core::Engine {

auto EngineContext::GetModules(std::vector<Slimenano::Core::Module::IModule*>& outModules) const -> Slimenano::Core::Base::Status {
    std::ranges::transform(m_modules, std::back_inserter(outModules), [](const auto& pair) {
        return pair.second;
    });
    return Slimenano::Core::Base::Status::Success(Slimenano::Core::Base::Status::Category::Internal);
}

auto EngineContext::RegisterModule(Slimenano::Core::Module::IModule* pModule) -> Slimenano::Core::Base::Status {
    if (!pModule) {
        return {
            Slimenano::Core::Base::Status::Category::Internal,
            Slimenano::Core::Base::Status::Code::InvalidParameter,
            "Cannot register nullptr as a module."
        };
    }
    const auto typeId = pModule->GetModuleId();
    if (m_modules.contains(typeId)) {
        return {
            Slimenano::Core::Base::Status::Category::Internal,
            Slimenano::Core::Base::Status::Code::AlreadyExists,
            "Module already be register."
        };
    }
    m_modules[typeId] = pModule;
    return Slimenano::Core::Base::Status::Success(Slimenano::Core::Base::Status::Category::Internal);
}

auto EngineContext::UnregisterModule(const Slimenano::Core::Module::IModule* pModule) -> Slimenano::Core::Base::Status {
    if (!pModule) {
        return {
            Slimenano::Core::Base::Status::Category::Internal,
            Slimenano::Core::Base::Status::Code::InvalidParameter,
            "Cannot unregister a nullptr."
        };
    }
    const auto typeId = pModule->GetModuleId();
    const auto it = m_modules.find(typeId);
    if (it == m_modules.end()) {
        return {
            Slimenano::Core::Base::Status::Category::Internal,
            Slimenano::Core::Base::Status::Code::NotFound,
            "Module not found."
        };
    }
    if (it->second != pModule) {
        return {
            Slimenano::Core::Base::Status::Category::Internal,
            Slimenano::Core::Base::Status::Code::NotPermitted,
            "Module is not owner."
        };
    }
    m_modules.erase(typeId);
    return Slimenano::Core::Base::Status::Success(Slimenano::Core::Base::Status::Category::Internal);
}

} // namespace Slimenano::Core::Engine
