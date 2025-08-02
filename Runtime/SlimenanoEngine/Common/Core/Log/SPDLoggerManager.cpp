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

#include "SPDLogger.h"
#include "SPDLoggerManager.h"

namespace Slimenano::Core::Log {

using namespace Base;

auto SPDLoggerManager::GetLogger(const char* name) -> ILogger* {
    return new SPDLogger(name);
}
auto SPDLoggerManager::FreeLogger(ILogger* logger) -> void {
    delete logger;
}
auto SPDLoggerManager::OnInit() -> Status {
    return Status::Success(Status::Category::Logger);
}
auto SPDLoggerManager::OnShutdown() -> Status {
    return Status::Success(Status::Category::Logger);
}
auto SPDLoggerManager::OnUpdate() -> Status {
    return Status::Success(Status::Category::Logger);
}
auto SPDLoggerManager::GetModuleName() const -> const char* {
    return "SPDLoggerManager";
}
} // namespace Slimenano::Core::Log
