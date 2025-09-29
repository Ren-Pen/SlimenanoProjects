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
#ifndef SLIMENANO_PROJECT_ENGINE_CORE_ENGINE_ENGINE_H
#define SLIMENANO_PROJECT_ENGINE_CORE_ENGINE_ENGINE_H

#include <vector>
#include <atomic>
#include <unordered_map>

#include "../Export.h"
#include "../Base/Status.h"
#include "../Base/Types.h"
#include "../Module/IModule.h"

namespace Slimenano::Core::Engine {

/**
 * @brief Main engine driver responsible for initializing modules and managing the main loop.
 */
class Engine {
public:
    /**
     * @brief Construct the Engine with the given EngineContext.
     * @param context Reference to the engine context which holds global runtime dependencies.
     */
    SLIMENANO_CORE_API explicit Engine() = default;

    /**
     * @brief Destructor that ensures the engine is properly stopped.
     */
    SLIMENANO_CORE_API ~Engine();

    template <class T>
    auto FindModule() -> T*;

    SLIMENANO_CORE_API auto Start() -> Slimenano::Core::Base::Status;

    SLIMENANO_CORE_API auto Stop() -> Slimenano::Core::Base::Status;

    SLIMENANO_CORE_API auto Install(Slimenano::Core::Module::IModule* pModule) -> Base::Status;
    SLIMENANO_CORE_API auto Uninstall(const Slimenano::Core::Module::IModule* pModule) -> Base::Status;
    SLIMENANO_CORE_API auto GetModules(std::vector<Slimenano::Core::Module::IModule*>& outModules) const -> Base::Status;

private:
    [[nodiscard]] auto MainLoop() -> Slimenano::Core::Base::Status;

    std::unordered_map<const Slimenano::Core::Base::TypeId*, Slimenano::Core::Module::IModule*> m_modules = std::unordered_map<const Slimenano::Core::Base::TypeId*, Slimenano::Core::Module::IModule*>();

    std::atomic<bool> m_running = false;
};

template <class T>
auto Engine::FindModule() -> T* {
    const auto typeId = Slimenano::Core::Base::TypeId::Get<T>();
    if (!m_modules.contains(typeId)) {
        return nullptr;
    }
    return static_cast<T*>(m_modules[typeId]);
}
} // namespace Slimenano::Core::Engine

#endif
