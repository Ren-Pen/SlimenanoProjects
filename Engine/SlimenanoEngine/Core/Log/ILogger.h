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
#ifndef SLIMENANO_ENGINE_CORE_LOG_I_LOGGER_H
#    define SLIMENANO_ENGINE_CORE_LOG_I_LOGGER_H

#    include "../Base/Export.h"

namespace Slimenano::Core::Log {

class SLIMENANO_CORE_API ILogger {
  public:
    enum class Level;
    virtual ~ILogger() = default;
    [[nodiscard]] virtual auto GetName() const -> const char* = 0;
    virtual auto SetLevel(const Level& level) const -> void = 0;
    virtual auto Log(const Level& level, const char* message) const -> void = 0;
    virtual auto Trace(const char* message) const -> void = 0;
    virtual auto Debug(const char* message) const -> void = 0;
    virtual auto Info(const char* message) const -> void = 0;
    virtual auto Warn(const char* message) const -> void = 0;
    virtual auto Error(const char* message) const -> void = 0;
    virtual auto Fatal(const char* message) const -> void = 0;
};

enum class ILogger::Level {
    Trace = 0,
    Debug,
    Info,
    Warn,
    Error,
    Fatal,
    Off,
};

} // namespace Slimenano::Core::Log
#endif
