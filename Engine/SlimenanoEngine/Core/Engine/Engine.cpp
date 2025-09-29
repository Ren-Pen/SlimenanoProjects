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

#include <vector>
#include <algorithm>
#include <iterator>

#include "../Module/IModule.h"
#include "../Exception/IExceptionHandler.h"

#include "Engine.h"

namespace Slimenano::Core::Engine {

Engine::~Engine() {
    Stop();
}

auto Engine::Start() -> Slimenano::Core::Base::Status {
    if (m_running.load(std::memory_order_relaxed)) {
        return Slimenano::Core::Base::Status::Success(Slimenano::Core::Base::Status::Category::Internal);
    }
    m_running.store(true, std::memory_order_relaxed);

    std::vector<Slimenano::Core::Module::IModule*> modules;

    if (const auto getModuleStatus = GetModules(modules); getModuleStatus.IsFailure()) {
        return getModuleStatus;
    }

    for (Slimenano::Core::Module::IModule* pModule : modules) {
        if (pModule) {
            if (const auto initModuleStatus = pModule->OnInit(); initModuleStatus.IsFailure()) {
                return initModuleStatus;
            }
        }
    }
    return MainLoop();
}

auto Engine::Stop() -> Slimenano::Core::Base::Status {
    if (!m_running.load(std::memory_order_relaxed)) {
        return Slimenano::Core::Base::Status::Success(Slimenano::Core::Base::Status::Category::Internal);
    }
    m_running.store(false, std::memory_order_relaxed);
    return Slimenano::Core::Base::Status::Success(Slimenano::Core::Base::Status::Category::Internal);
}

auto Engine::MainLoop() -> Slimenano::Core::Base::Status {

    const auto pExceptionHandler = this->FindModule<Exception::IExceptionHandler>();

    std::vector<Slimenano::Core::Module::IModule*> modules;
    if (const auto getModuleStatus = GetModules(modules); getModuleStatus.IsFailure()) {
        if (pExceptionHandler != nullptr) {
            pExceptionHandler->Handle(getModuleStatus);
        }
    }

    while (m_running.load(std::memory_order_relaxed)) {
        for (Slimenano::Core::Module::IModule* pModule : modules) {
            if (pModule) {
                if (auto updateModuleStatus = pModule->OnUpdate(); updateModuleStatus.IsFailure()) {
                    if (pExceptionHandler != nullptr) {
                        pExceptionHandler->Handle(updateModuleStatus);
                    }
                }
            }
        }
    }

    // cleanup
    for (Slimenano::Core::Module::IModule* pModule : modules) {
        if (pModule) {
            if (auto shutdownModuleStatus = pModule->OnShutdown(); shutdownModuleStatus.IsFailure()) {
                if (pExceptionHandler != nullptr) {
                    pExceptionHandler->Handle(shutdownModuleStatus);
                }
            }
        }
    }

    return Slimenano::Core::Base::Status::Success(Slimenano::Core::Base::Status::Category::Internal);
}

auto Engine::GetModules(std::vector<Slimenano::Core::Module::IModule*>& outModules) const -> Slimenano::Core::Base::Status {
    std::ranges::transform(m_modules, std::back_inserter(outModules), [](const auto& pair) {
        return pair.second;
    });
    return Slimenano::Core::Base::Status::Success(Slimenano::Core::Base::Status::Category::Internal);
}

auto Engine::Install(Slimenano::Core::Module::IModule* pModule) -> Slimenano::Core::Base::Status {
    if (!pModule) {
        return {
            Slimenano::Core::Base::Status::Category::Internal,
            Slimenano::Core::Base::Status::Code::InvalidParameter,
            "Cannot install nullptr as a module."
        };
    }

    const auto typeId = pModule->GetModuleId();
    if (m_modules.contains(typeId)) {
        return {
            Slimenano::Core::Base::Status::Category::Internal,
            Slimenano::Core::Base::Status::Code::AlreadyExists,
            "Module already be install."
        };
    }

    const auto installModuleStatus = pModule->OnInstall(this);
    if (installModuleStatus.IsFailure()) {
        return installModuleStatus;
    }

    m_modules[typeId] = pModule;

    return Slimenano::Core::Base::Status::Success(Slimenano::Core::Base::Status::Category::Internal);
}

auto Engine::Uninstall(const Slimenano::Core::Module::IModule* pModule) -> Slimenano::Core::Base::Status {
    if (!pModule) {
        return {
            Slimenano::Core::Base::Status::Category::Internal,
            Slimenano::Core::Base::Status::Code::InvalidParameter,
            "Cannot uninstall a nullptr."
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
