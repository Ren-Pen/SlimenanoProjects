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
#ifndef SLIMENANO_PROJECT_ENGINE_CORE_ENGINE_ENGINE_CONTEXT_H
#define SLIMENANO_PROJECT_ENGINE_CORE_ENGINE_ENGINE_CONTEXT_H
#include <vector>
#include <unordered_map>

#include "../Export.h"
#include "../Base/Types.h"
#include "../Base/Status.h"
#include "../Module/IModule.h"

namespace Slimenano::Core::Engine {

class EngineContext {

    friend class Slimenano::Core::Engine::Engine;

public:
    ~EngineContext() = default;

    template <class T>
    auto FindModule() -> T*;

    SLIMENANO_CORE_API auto RegisterModule(Slimenano::Core::Module::IModule* pModule) -> Base::Status;
    SLIMENANO_CORE_API auto UnregisterModule(const Slimenano::Core::Module::IModule* pModule) -> Base::Status;
    SLIMENANO_CORE_API auto GetModules(std::vector<Slimenano::Core::Module::IModule*>& outModules) const -> Base::Status;

private:
    EngineContext() = default;
    std::unordered_map<const Slimenano::Core::Base::TypeId*, Slimenano::Core::Module::IModule*> m_modules = std::unordered_map<const Slimenano::Core::Base::TypeId*, Slimenano::Core::Module::IModule*>();
};

template <class T>
auto EngineContext::FindModule() -> T* {
    const auto typeId = Slimenano::Core::Base::TypeId::Get<T>();
    if (!m_modules.contains(typeId)) {
        return nullptr;
    }
    return static_cast<T*>(m_modules[typeId]);
}

} // namespace Slimenano::Core::Engine

#endif
