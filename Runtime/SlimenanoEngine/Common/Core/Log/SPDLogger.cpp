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

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks-inl.h>

#include "SPDLogger.h"

namespace Slimenano::Core::Log {

SPDLogger::SPDLogger(const char* name) : m_Name(name), m_pLogger(spdlog::stdout_color_mt(name)) {
}

auto SPDLogger::Log(const Level level, const char* message) const -> void {
    switch (level) {
    case Level::Trace:
        this->Trace(message);
        break;
    case Level::Debug:
        this->Debug(message);
        break;
    case Level::Info:
        this->Info(message);
        break;
    case Level::Warn:
        this->Warn(message);
        break;
    case Level::Error:
        this->Error(message);
        break;
    case Level::Fatal:
        this->Fatal(message);
        break;
    }
}
auto SPDLogger::Trace(const char* message) const -> void {
    spdlog::get(m_Name)->trace(message);
}
auto SPDLogger::Debug(const char* message) const -> void {
    spdlog::get(m_Name)->debug(message);
}
auto SPDLogger::Info(const char* message) const -> void {
    spdlog::get(m_Name)->info(message);
}
auto SPDLogger::Warn(const char* message) const -> void {
    spdlog::get(m_Name)->warn(message);
}
auto SPDLogger::Error(const char* message) const -> void {
    spdlog::get(m_Name)->error(message);
}
auto SPDLogger::Fatal(const char* message) const -> void {
    spdlog::get(m_Name)->critical(message);
}

} // namespace Slimenano::Core::Log
