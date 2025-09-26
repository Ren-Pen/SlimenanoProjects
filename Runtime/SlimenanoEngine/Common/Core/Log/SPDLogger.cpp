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

#include <spdlog/sinks/stdout_color_sinks-inl.h>
#include <spdlog/spdlog.h>

#include "SPDLogger.h"

namespace Slimenano::Core::Log {

class SPDLogger::Impl {
    friend SPDLogger;

    explicit Impl(const char* name) :
        m_Name(name), m_pLogger(spdlog::stdout_color_mt(name)) {}
    ~Impl() = default;

    const char* m_Name;
    std::shared_ptr<spdlog::logger> m_pLogger;
    SPDLogger* m_pInterface{};
};

auto Level2SpdLevel(const ILogger::Level& level) -> spdlog::level::level_enum {
    switch (level) {
    case ILogger::Level::Trace:
        return spdlog::level::trace;
    case ILogger::Level::Debug:
        return spdlog::level::debug;
    case ILogger::Level::Info:
        return spdlog::level::info;
    case ILogger::Level::Warn:
        return spdlog::level::warn;
    case ILogger::Level::Error:
        return spdlog::level::err;
    case ILogger::Level::Fatal:
        return spdlog::level::critical;
    default:;
    }
    return spdlog::level::off;
}

SPDLogger::SPDLogger(const char* name) :
    m_pImpl(new Impl(name)) {
}

SPDLogger::~SPDLogger() {
    delete m_pImpl;
}

auto SPDLogger::SetLevel(const Level& level) const -> void {
    m_pImpl->m_pLogger->set_level(Level2SpdLevel(level));
}

auto SPDLogger::Log(const Level& level, const char* message) const -> void {
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
    default:;
    }
}
auto SPDLogger::Trace(const char* message) const -> void {
    m_pImpl->m_pLogger->trace(message);
}
auto SPDLogger::Debug(const char* message) const -> void {
    m_pImpl->m_pLogger->debug(message);
}
auto SPDLogger::Info(const char* message) const -> void {
    m_pImpl->m_pLogger->info(message);
}
auto SPDLogger::Warn(const char* message) const -> void {
    m_pImpl->m_pLogger->warn(message);
}
auto SPDLogger::Error(const char* message) const -> void {
    m_pImpl->m_pLogger->error(message);
}
auto SPDLogger::Fatal(const char* message) const -> void {
    m_pImpl->m_pLogger->critical(message);
}
auto SPDLogger::GetName() const -> const char* {
    return m_pImpl->m_Name;
}

} // namespace Slimenano::Core::Log
