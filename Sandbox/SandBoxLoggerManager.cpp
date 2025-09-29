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
#include "SandBoxLogger.h"
#include "SandBoxLoggerManager.h"

namespace Slimenano::SandBox {
auto SandBoxLoggerManager::GetLogger(const char* name) -> Slimenano::Core::Log::ILogger* {
    return new SandBoxLogger();
}

auto SandBoxLoggerManager::FreeLogger(Slimenano::Core::Log::ILogger* logger) -> Slimenano::Core::Base::Status {
    delete logger;
    return Slimenano::Core::Base::Status::Success(GetModuleStatusCategory());
}

auto SandBoxLoggerManager::OnInstall(Slimenano::Core::Engine::Engine* context) -> Slimenano::Core::Base::Status {
    return Slimenano::Core::Base::Status::Success(GetModuleStatusCategory());
}

auto SandBoxLoggerManager::OnUninstall() -> void {
}

auto SandBoxLoggerManager::OnInit() -> Slimenano::Core::Base::Status {
    return Slimenano::Core::Base::Status::Success(GetModuleStatusCategory());
}

auto SandBoxLoggerManager::OnShutdown() -> Slimenano::Core::Base::Status {
    return Slimenano::Core::Base::Status::Success(GetModuleStatusCategory());
}

auto SandBoxLoggerManager::OnUpdate() -> Slimenano::Core::Base::Status {
    return Slimenano::Core::Base::Status::Success(GetModuleStatusCategory());
}

auto SandBoxLoggerManager::GetModuleName() const -> const char* {
    return "SandboxLoggerManager";
}
auto SandBoxLoggerManager::GetModuleStatusCategory() const -> Slimenano::Core::Base::State {
    return Slimenano::Core::Base::Status::Category::Logger;
}

auto SandBoxLoggerManager::SetDefaultLevel(const Slimenano::Core::Log::ILogger::Level& level) -> void {
}
} // namespace Slimenano::SandBox
