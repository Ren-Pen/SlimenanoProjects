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
#ifndef SLIMENANO_PROJECT_RUNTIME_COMMON_CORE_LOG_SPD_LOGGER_H
#    define SLIMENANO_PROJECT_RUNTIME_COMMON_CORE_LOG_SPD_LOGGER_H

#    include <SlimenanoEngine/Core/Log/ILogger.h>

namespace Slimenano::Core::Log {
class SPDLogger final : public ILogger {
  public:
    explicit SPDLogger(const char* name);
    ~SPDLogger() override;

    [[nodiscard]] auto GetName() const -> const char* override;
    auto SetLevel(const Level& level) const -> void override;
    auto Log(const Level& level, const char* message) const -> void override;
    auto Trace(const char* message) const -> void override;
    auto Debug(const char* message) const -> void override;
    auto Info(const char* message) const -> void override;
    auto Warn(const char* message) const -> void override;
    auto Error(const char* message) const -> void override;
    auto Fatal(const char* message) const -> void override;


  private:
    class Impl;
    Impl* m_pImpl;
};
} // namespace Slimenano::Core::Log

#endif
