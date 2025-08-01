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
#include "Engine.h"
#include "EngineContext.h"
#include "../Module/IModule.h"
#include "../Exception/IExceptionHandler.h"

namespace Slimenano::Core::Engine {

using namespace Base;
using namespace Module;

Engine::Engine(EngineContext* context) : m_pContext(context) {
}

Engine::~Engine() {
    Stop();
}

auto Engine::Start() -> Status {
    m_running = true;

    std::vector<IModule*> modules;

    auto status = m_pContext->GetModules(modules);
    if (status.IsFailure()) {
        return status;
    }

    for (IModule* pModule : modules) {
        if (pModule) {
            auto status = pModule->OnInit();
            if (status.IsFailure()) {
                return status;
            }
        }
    }
    return MainLoop();
}

auto Engine::Stop() -> Status {
    if (!m_running) {
        return Status::Success(Status::Category::Internal);
    }
    m_running = false;
    return Status::Success(Status::Category::Internal);
}

auto Engine::MainLoop() -> Status {

    auto pExceptionHandler = m_pContext->FindModule<Exception::IExceptionHandler>();

    std::vector<IModule*> modules;
    auto status = m_pContext->GetModules(modules);
    if (status.IsFailure()) {
        if (pExceptionHandler != nullptr) {
            pExceptionHandler->Handle(status);
        }
    }

    while (m_running) {
        for (Module::IModule* pModule : modules) {
            if (pModule) {
                auto status = pModule->OnUpdate();
                if (status.IsFailure()) {
                    if (pExceptionHandler != nullptr) {
                        pExceptionHandler->Handle(status);
                    }
                }
            }
        }
    }

    // cleanup
    for (Module::IModule* pModule : modules) {
        if (pModule) {
            auto status = pModule->OnShutdown();
            if (status.IsFailure()) {
                if (pExceptionHandler != nullptr) {
                    pExceptionHandler->Handle(status);
                }
            }
        }
    }

    return Status::Success(Status::Category::Internal);
}

auto Engine::getEngineContext() -> EngineContext* {
    return m_pContext;
}

} // namespace Slimenano::Core::Engine
