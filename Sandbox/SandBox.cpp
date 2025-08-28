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
#include "SlimenanoEngine/Core/Log/ILogger.h"
#include <SlimenanoEngine/Common/Core/Log/SPDLoggerManager.h>
#include <SlimenanoEngine/SlimenanoEngine.h>
#include <chrono>
#include <iostream>
#include <string>

using namespace Slimenano::Core::Application;
using namespace Slimenano::Core::Base;
using namespace Slimenano::Core::Engine;
using namespace Slimenano::Core::Module;
using namespace Slimenano::Core::Exception;
using namespace Slimenano::Core::Log;

class SandboxLogger final : public ILogger {
  public:
    ~SandboxLogger() override = default;
    [[nodiscard]] auto GetName() const -> const char* override { return "SandboxLogger"; }
    auto SetLevel(const Level& level) const -> void override {}
    auto Log(const Level& level, const char* message) const -> void override {
        switch (level) {
        case Level::Trace:
            std::cout << "[T] ";
            break;
        case Level::Debug:
            std::cout << "[D] ";
            break;
        case Level::Info:
            std::cout << "[I] ";
            break;
        case Level::Warn:
            std::cout << "[W] ";
            break;
        case Level::Error:
            std::cout << "[E] ";
            break;
        case Level::Fatal:
            std::cout << "[F] ";
        default:;
        }
        std::cout << message << std::endl;
    }
    void Trace(const char* message) const override { this->Log(Level::Trace, message); }
    void Debug(const char* message) const override { this->Log(Level::Debug, message); }
    void Info(const char* message) const override { this->Log(Level::Info, message); }
    void Warn(const char* message) const override { this->Log(Level::Warn, message); }
    void Error(const char* message) const override { this->Log(Level::Error, message); }
    void Fatal(const char* message) const override { this->Log(Level::Fatal, message); }
};

class SandboxLoggerManager final : public ILoggerManager {
  public:
    ~SandboxLoggerManager() override = default;
    auto GetLogger(const char* name) -> ILogger* override { return new SandboxLogger(); }

    auto FreeLogger(ILogger* logger) -> Status override {
        delete logger;
        return Status::Success(GetModuleStatusCategory());
    }

    auto OnInit() -> Status override { return Status::Success(GetModuleStatusCategory()); }

    auto OnShutdown() -> Status override { return Status::Success(GetModuleStatusCategory()); }

    auto OnUpdate() -> Status override { return Status::Success(GetModuleStatusCategory()); }

    [[nodiscard]] auto GetModuleName() const -> const char* override { return "SandboxLoggerManager"; }

    auto SetDefaultLevel(const ILogger::Level& level) -> void override {}
};

class Sandbox final : public IApplication {
  public:
    ~Sandbox() override = default;
    /**
     * @brief Called when the module is initialized during engine startup
     * @return true if initialized successfully
     */
    auto OnInit() -> Status override {
        const auto pLoggerManager = GetLoggerManager();
        pLogger = pLoggerManager->GetLogger("Sandbox");
        pLogger->Warn("Sandbox initialized");
        startTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        return Status::Success(Status::Category::Application);
    }

    /**
     * @brief Called when the module is being shut down during engine shutdown
     */
    auto OnShutdown() -> Status override {
        pLogger->Warn("Sandbox shutdown");
        const auto pLoggerManager = GetLoggerManager();
        pLoggerManager->FreeLogger(pLogger);
        pLogger = nullptr;
        return Status::Success(Status::Category::Application);
    }
    /**
     * @brief Called every frame after engine startup
     */
    auto OnUpdate() -> Status override {
        auto now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        if (((now - startTime) % 1000) == 0) {
            pLogger->Error((std::string("Sandbox onUpdate ") + std::to_string((now - startTime) / 1000)).c_str());
        }
        if ((now - startTime) > 10000) {
            GetEngine()->Stop();
        }
        return Status::Success(Status::Category::Application);
    }
    /**
     * @brief Returns the name of the module (for logging or debugging)
     * @return const char* representing the module name
     */
    [[nodiscard]] auto GetModuleName() const -> const char* override { return "Sandbox"; }

  private:
    unsigned long long startTime = 0;
    ILogger* pLogger = nullptr;
};

auto main(const int argc, const char** argv) -> int {

    auto engineContext = EngineContext();
    auto engine = Engine(&engineContext);

    auto loggerManager = SPDLoggerManager();
    std::cout << loggerManager.GetModuleName() << " " << loggerManager.Install(&engine).GetState() << std::endl;

    auto sandboxLoggerManager = SandboxLoggerManager();
    std::cout << sandboxLoggerManager.GetModuleName() << " " << sandboxLoggerManager.Install(&engine).GetState() << std::endl;

    auto sandbox = Sandbox();
    std::cout << sandbox.Install(&engine).GetState() << std::endl;

    engine.Start();

    return 0;
}
