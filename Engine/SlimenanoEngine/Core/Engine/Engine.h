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
#include <atomic>

#include "../Export.h"
#include "../Base/Status.h"

#include "EngineContext.h"

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
    SLIMENANO_CORE_API explicit Engine();

    /**
     * @brief Destructor that ensures the engine is properly stopped.
     */
    SLIMENANO_CORE_API ~Engine();

    /**
     * @brief Starts the engine and enters the main loop.
     * Initializes and starts all registered modules.
     */
    SLIMENANO_CORE_API auto Start() -> Slimenano::Core::Base::Status;

    /**
     * @brief Stops the engine and shuts down all running modules.
     */
    SLIMENANO_CORE_API auto Stop() -> Slimenano::Core::Base::Status;

    SLIMENANO_CORE_API [[nodiscard]] auto getEngineContext() const -> EngineContext*;

private:
    /**
     * @brief Reference to the engine context shared across all modules.
     */
    EngineContext* m_pContext;

    /**
     * @brief Whether the engine is currently running.
     */
    std::atomic<bool> m_running = false;

    /**
     * @brief The main engine loop that drives all active modules.
     * This runs until Stop() is called.
     */
    [[nodiscard]] auto MainLoop() const -> Slimenano::Core::Base::Status;
};
} // namespace Slimenano::Core::Engine

#endif
