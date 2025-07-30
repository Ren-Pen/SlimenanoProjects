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

namespace Slimenano::Core::Engine {

using namespace Base;
using namespace Module;

Engine::Engine(EngineContext& context) : m_context(context) {
}

Engine::~Engine() {
    Stop();
}

Status Engine::Start() {
    m_running = true;

    std::vector<IModule*> modules;

    auto status = m_context.GetModules(modules);
    if (IsFailure(status)) {
        return status;
    }

    for (IModule* pModule : modules) {
        if (pModule) {
            auto status = pModule->OnInit(this);
            if (IsFailure(status)) {
                return status;
            }
        }
    }
    return MainLoop();
}

Status Engine::Stop() {
    if (!m_running) {
        return State(StateCategory::Internal, StateCode::kSuccess);
    }
    m_running = false;
    return State(StateCategory::Internal, StateCode::kSuccess);
}

Status Engine::MainLoop() {

    std::vector<IModule*> modules;
    auto status = m_context.GetModules(modules);
    if (IsFailure(status)) {
        return status;
    }

    while (m_running) {
        for (Module::IModule* pModule : modules) {
            if (pModule) {
                auto status = pModule->OnUpdate();
                if (IsFailure(status)) {
                    //TODO: handle error
                    // return status;
                }
            }
        }
    }

    // cleanup
    for (Module::IModule* pModule : modules) {
        if (pModule) {
            auto status = pModule->OnShutdown();
            if (IsFailure(status)) {
                // return status;
            }
        }
    }

    return State(StateCategory::Internal, StateCode::kSuccess);
}

} // namespace Slimenano::Core::Engine
