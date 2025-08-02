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
#ifndef SLIMENANO_ENGINE_CORE_LOG_I_LOGGER_MANAGER_H
#    define SLIMENANO_ENGINE_CORE_LOG_I_LOGGER_MANAGER_H

#    include "../Base/Export.h"
#    include "../Module/IBaseModule.h"
#    include "ILogger.h"

namespace Slimenano::Core::Log {

class SLIMENANO_API ILoggerManager : public Module::IBaseModule<ILoggerManager> {
  public:
    ~ILoggerManager() override = default;
    virtual auto GetLogger(const char* name) -> ILogger* = 0;
    virtual auto FreeLogger(ILogger* logger) -> void = 0;
};

} // namespace Slimenano::Core::Log
#endif
