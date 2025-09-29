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
#ifndef SLIMENANO_ENGINE_SANDBOX_SANDBOX_LOGGER_MANAGER_H
#define SLIMENANO_ENGINE_SANDBOX_SANDBOX_LOGGER_MANAGER_H

#include <SlimenanoEngine/Core/Log/ILoggerManager.h>

namespace Slimenano::SandBox {

class SandBoxLoggerManager final : public Slimenano::Core::Log::ILoggerManager {
public:
    ~SandBoxLoggerManager() override = default;
    auto GetLogger(const char* name) -> Slimenano::Core::Log::ILogger* override;

    auto FreeLogger(Slimenano::Core::Log::ILogger* logger) -> Slimenano::Core::Base::Status override;

    auto OnInstall(Slimenano::Core::Engine::Engine* context) -> Slimenano::Core::Base::Status override;

    auto OnUninstall() -> void override;

    auto OnInit() -> Slimenano::Core::Base::Status override;

    auto OnShutdown() -> Slimenano::Core::Base::Status override;

    auto OnUpdate() -> Slimenano::Core::Base::Status override;

    [[nodiscard]] auto GetModuleName() const -> const char* override;

    [[nodiscard]] auto GetModuleStatusCategory() const -> Slimenano::Core::Base::State override;

    auto SetDefaultLevel(const Slimenano::Core::Log::ILogger::Level& level) -> void override;

};

} // namespace Slimenano::SandBox

#endif
