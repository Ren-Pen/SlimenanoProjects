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
#include <iostream>
#include <SlimenanoEngine/Core/Log/ILogger.h>
#include "SandBoxLogger.h"

namespace Slimenano::SandBox {
auto SandBoxLogger::GetName() const -> const char* {
    return "SandBoxLogger";
}
auto SandBoxLogger::SetLevel(const Slimenano::Core::Log::ILogger::Level& level) const -> void {
}
auto SandBoxLogger::Log(const Slimenano::Core::Log::ILogger::Level& level, const char* message) const -> void {
    switch (level) {
    case Slimenano::Core::Log::ILogger::Level::Trace:
        std::cout << "[T] ";
        break;
    case Slimenano::Core::Log::ILogger::Level::Debug:
        std::cout << "[D] ";
        break;
    case Slimenano::Core::Log::ILogger::Level::Info:
        std::cout << "[I] ";
        break;
    case Slimenano::Core::Log::ILogger::Level::Warn:
        std::cout << "[W] ";
        break;
    case Slimenano::Core::Log::ILogger::Level::Error:
        std::cout << "[E] ";
        break;
    case Slimenano::Core::Log::ILogger::Level::Fatal:
        std::cout << "[F] ";
    default:;
    }
    std::cout << message << std::endl;
}
void SandBoxLogger::Trace(const char* message) const {
    this->Log(Slimenano::Core::Log::ILogger::Level::Trace, message);
}
void SandBoxLogger::Debug(const char* message) const {
    this->Log(Slimenano::Core::Log::ILogger::Level::Debug, message);
}
void SandBoxLogger::Info(const char* message) const {
    this->Log(Slimenano::Core::Log::ILogger::Level::Info, message);
}
void SandBoxLogger::Warn(const char* message) const {
    this->Log(Slimenano::Core::Log::ILogger::Level::Warn, message);
}
void SandBoxLogger::Error(const char* message) const {
    this->Log(Slimenano::Core::Log::ILogger::Level::Error, message);
}
void SandBoxLogger::Fatal(const char* message) const {
    this->Log(Slimenano::Core::Log::ILogger::Level::Fatal, message);
}
} // namespace Slimenano::SandBox
