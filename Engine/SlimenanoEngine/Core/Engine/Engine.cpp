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

#include "../Module/IModule.h"
#include "../Exception/IExceptionHandler.h"

#include "Engine.h"
#include "EngineContext.h"

namespace Slimenano::Core::Engine {

Engine::Engine() :
    m_pContext(new EngineContext()) {
}

Engine::~Engine() {
    Stop();
    if (this->m_pContext != nullptr) {
        delete this->m_pContext;
        this->m_pContext = nullptr;
    }
}

auto Engine::Start() -> Slimenano::Core::Base::Status {
    m_running.store(true, std::memory_order_relaxed);

    std::vector<Slimenano::Core::Module::IModule*> modules;

    if (const auto getModuleStatus = m_pContext->GetModules(modules); getModuleStatus.IsFailure()) {
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

auto Engine::MainLoop() const -> Slimenano::Core::Base::Status {

    const auto pExceptionHandler = m_pContext->FindModule<Exception::IExceptionHandler>();

    std::vector<Slimenano::Core::Module::IModule*> modules;
    if (const auto getModuleStatus = m_pContext->GetModules(modules); getModuleStatus.IsFailure()) {
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

auto Engine::getEngineContext() const -> EngineContext* {
    return m_pContext;
}

} // namespace Slimenano::Core::Engine
