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
#include <chrono>
#include <string>

#include "SandBoxApplication.h"
#include "SlimenanoEngine/Core/Base/Status.h"
#include "SlimenanoEngine/Core/Engine/Engine.h"
#include "SlimenanoEngine/Core/Log/ILoggerManager.h"

namespace Slimenano::SandBox {

auto SandBoxApplication::OnInstall(Slimenano::Core::Engine::Engine* engine) -> Slimenano::Core::Base::Status {

    this->pEngine = engine;

    return Slimenano::Core::Base::Status::Success(this->GetModuleStatusCategory());
}

auto SandBoxApplication::OnUninstall() -> void {

    this->pEngine = nullptr;
}

auto SandBoxApplication::OnInit() -> Slimenano::Core::Base::Status {
    const auto pLoggerManager = pEngine->FindModule<Slimenano::Core::Log::ILoggerManager>();
    pLogger = pLoggerManager->GetLogger("Sandbox");
    pLogger->Warn("Sandbox initialized");
    startTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    return Slimenano::Core::Base::Status::Success(Slimenano::Core::Base::Status::Category::Application);
}

auto SandBoxApplication::OnShutdown() -> Slimenano::Core::Base::Status {
    pLogger->Warn("Sandbox shutdown");
    const auto pLoggerManager = pEngine->FindModule<Slimenano::Core::Log::ILoggerManager>();
    pLoggerManager->FreeLogger(pLogger);
    pLogger = nullptr;
    return Slimenano::Core::Base::Status::Success(Slimenano::Core::Base::Status::Category::Application);
}

auto SandBoxApplication::OnUpdate() -> Slimenano::Core::Base::Status {
    auto now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    if (((now - startTime) % 1000) == 0) {
        pLogger->Error((std::string("Sandbox onUpdate ") + std::to_string((now - startTime) / 1000)).c_str());
    }
    if ((now - startTime) > 10000) {
        pEngine->Stop();
    }
    return Slimenano::Core::Base::Status::Success(Slimenano::Core::Base::Status::Category::Application);
}

auto SandBoxApplication::GetModuleName() const -> const char* {
    return "Sandbox";
}

auto SandBoxApplication::GetModuleStatusCategory() const -> Slimenano::Core::Base::State {
    return Slimenano::Core::Base::Status::Category::Application;
}

} // namespace Slimenano::Sandbox
