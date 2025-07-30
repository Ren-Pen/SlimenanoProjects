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
#include "Core/Base/Status.h"
#include <SlimenanoEngine.h>
#include <chrono>
#include <iostream>

using namespace Slimenano::Core::Base;
using namespace Slimenano::Core::Engine;
using namespace Slimenano::Core::Module;

class Sandbox final : public IModule {
  public:
    ~Sandbox() override = default;
    /**
     * @brief Called when the module is initialized during engine startup
     * @return true if initialized successfully
     */
    virtual Status OnInit(Engine* engine) override {
        std::cout << "Sandbox initialized" << std::endl;
        m_engine = engine;
        startTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        return State(StateCategory::Application, StateCode::kSuccess);
    }

    /**
     * @brief Called when the module is being shut down during engine shutdown
     */
    virtual Status OnShutdown() override {
        std::cout << "Sandbox shutdown" << std::endl;
        return State(StateCategory::Application, StateCode::kSuccess);
    }
    /**
     * @brief Called every frame after engine startup
     */
    virtual Status OnUpdate() override {
        auto now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        if (((now - startTime) % 1000) == 0) {
            std::cout << "Sandbox onUpdate " << (now - startTime) / 1000 << std::endl;
        }
        if ((now - startTime) > 10000) {
            m_engine->Stop();
        }
        return State(StateCategory::Application, StateCode::kSuccess);
    }
    /**
     * @brief Returns the name of the module (for logging or debugging)
     * @return const char* representing the module name
     */
    virtual const char* GetModuleName() const override { return "Sandbox"; }

  private:
    Engine* m_engine = nullptr;
    unsigned long long startTime = 0;
};

auto main(const int argc, const char** argv) -> int {
    auto sandbox = Sandbox();

    auto engineContext = EngineContext();
    engineContext.RegisterModule(&sandbox);

    auto engine = Engine(engineContext);

    engine.Start();

    return 0;
}
