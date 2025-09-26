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
#ifndef SLIMENANO_PROJECT_RUNTIME_COMMON_CORE_LOG_SPD_LOGGER_MANAGER_H
#define SLIMENANO_PROJECT_RUNTIME_COMMON_CORE_LOG_SPD_LOGGER_MANAGER_H
#include <SlimenanoEngine/Core/Log/ILoggerManager.h>
#include "../Export.h"

namespace Slimenano::Core::Log {

class SLIMENANO_RUNTIME_CORE_API SPDLoggerManager final : public ILoggerManager {
public:
    SPDLoggerManager();
    ~SPDLoggerManager() override;

    auto GetLogger(const char* name) -> ILogger* override;
    auto FreeLogger(ILogger* logger) -> Slimenano::Core::Base::Status override;

    auto OnInit() -> Slimenano::Core::Base::Status override;
    auto OnShutdown() -> Slimenano::Core::Base::Status override;
    auto OnUpdate() -> Slimenano::Core::Base::Status override;
    auto SetDefaultLevel(const ILogger::Level& level) -> void override;
    [[nodiscard]] auto GetModuleName() const -> const char* override;

private:
    class Impl;
    Impl* m_pImpl;
};

} // namespace Slimenano::Core::Log

#endif
