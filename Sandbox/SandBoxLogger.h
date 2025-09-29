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
#ifndef SLIMENANO_ENGINE_SANDBOX_SANDBOX_LOGGER_H
#define SLIMENANO_ENGINE_SANDBOX_SANDBOX_LOGGER_H

#include <SlimenanoEngine/Core/Log/ILogger.h>

namespace Slimenano::SandBox {

class SandBoxLogger final : public Slimenano::Core::Log::ILogger {
public:
    ~SandBoxLogger() override = default;
    [[nodiscard]] auto GetName() const -> const char* override;
    auto SetLevel(const Slimenano::Core::Log::ILogger::Level& level) const -> void override;
    auto Log(const Slimenano::Core::Log::ILogger::Level& level, const char* message) const -> void override;
    void Trace(const char* message) const override;
    void Debug(const char* message) const override;
    void Info(const char* message) const override;
    void Warn(const char* message) const override;
    void Error(const char* message) const override;
    void Fatal(const char* message) const override;
};
} // namespace Slimenano::SandBox

#endif
