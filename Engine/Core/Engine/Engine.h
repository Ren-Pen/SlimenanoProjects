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
#pragma once
#ifndef SLIMENANO_ENGINE_CORE_ENGINE_ENGINE_H
#    define SLIMENANO_ENGINE_CORE_ENGINE_ENGINE_H

#    include "../Base/Status.h"
#    include "EngineContext.h"

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
    Engine(EngineContext& context);

    /**
     * @brief Destructor that ensures the engine is properly stopped.
     */
    ~Engine();

    /**
     * @brief Starts the engine and enters the main loop.
     * Initializes and starts all registered modules.
     */
    Base::Status Start();

    /**
     * @brief Stops the engine and shuts down all running modules.
     */
    Base::Status Stop();

  private:
    /**
     * @brief Reference to the engine context shared across all modules.
     */
    EngineContext& m_context;

    /**
     * @brief Whether the engine is currently running.
     */
    bool m_running = false;

    /**
     * @brief The main engine loop that drives all active modules.
     * This runs until Stop() is called.
     */
    Base::Status MainLoop();
};
} // namespace Slimenano::Core::Engine

#endif
