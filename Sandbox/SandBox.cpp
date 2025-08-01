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
#include "Core/Log/ILogger.h"
#include <SlimenanoEngine.h>
#include <chrono>
#include <iostream>
#include <string>

using namespace Slimenano::Core::Application;
using namespace Slimenano::Core::Base;
using namespace Slimenano::Core::Engine;
using namespace Slimenano::Core::Module;
using namespace Slimenano::Core::Exception;
using namespace Slimenano::Core::Log;

class SandboxLogger : public ILogger {
  public:
    virtual ~SandboxLogger() = default;
    virtual auto Log(Level level, const char* message) const -> void override {
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
        }
        std::cout << message << std::endl;
    }
    virtual void Trace(const char* message) const override { this->Log(ILogger::Level::Trace, message); };
    virtual void Debug(const char* message) const override { this->Log(ILogger::Level::Debug, message); };
    virtual void Info(const char* message) const override { this->Log(ILogger::Level::Info, message); };
    virtual void Warn(const char* message) const override { this->Log(ILogger::Level::Warn, message); };
    virtual void Error(const char* message) const override { this->Log(ILogger::Level::Error, message); };
    virtual void Fatal(const char* message) const override { this->Log(ILogger::Level::Fatal, message); };
};

class SandboxLoggerManager : public ILoggerManager {
  public:
    virtual ~SandboxLoggerManager() = default;
    virtual auto GetLogger(const char* name) -> ILogger* override { return new SandboxLogger(); }

    virtual auto FreeLogger(ILogger* logger) -> void override { delete logger; };

    virtual auto OnInit() -> Status override { return Status::Success(Status::Category::Application); };

    virtual auto OnShutdown() -> Status override { return Status::Success(Status::Category::Application); };

    virtual auto OnUpdate() -> Status override { return Status::Success(Status::Category::Application); };

    virtual auto GetModuleName() const -> const char* override { return "SandboxLoggerManager"; };
};

class Sandbox final : public IApplication {
  public:
    ~Sandbox() override = default;
    /**
     * @brief Called when the module is initialized during engine startup
     * @return true if initialized successfully
     */
    virtual auto OnInit() -> Status override {
        auto pLoggerManager = GetLoggerManager();
        pLogger = pLoggerManager->GetLogger("Sandbox");
        pLogger->Warn("Sandbox initialized");
        startTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        return Status::Success(Status::Category::Application);
    }

    /**
     * @brief Called when the module is being shut down during engine shutdown
     */
    virtual auto OnShutdown() -> Status override {
        pLogger->Warn("Sandbox shutdown");
        return Status::Success(Status::Category::Application);
    }
    /**
     * @brief Called every frame after engine startup
     */
    virtual auto OnUpdate() -> Status override {
        auto now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        if (((now - startTime) % 1000) == 0) {
            // std::cout << "Sandbox onUpdate " << (now - startTime) / 1000 << std::endl;
            pLogger->Info((std::string("Sandbox onUpdate ") + std::to_string((now - startTime) / 1000)).c_str());
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
    virtual auto GetModuleName() const -> const char* override { return "Sandbox"; }

  private:
    unsigned long long startTime = 0;
    ILogger* pLogger = nullptr;
};

auto main(const int argc, const char** argv) -> int {

    auto engineContext = EngineContext();
    auto engine = Engine(&engineContext);

    auto loggerManager = SandboxLoggerManager();
    std::cout << loggerManager.Install(&engine).GetState() << std::endl;

    auto sandbox = Sandbox();
    std::cout << sandbox.Install(&engine).GetState() << std::endl;

    engine.Start();

    return 0;
}
