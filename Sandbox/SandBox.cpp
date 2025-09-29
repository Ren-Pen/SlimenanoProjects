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
#include <SlimenanoEngine/Common/Core/Log/SPDLoggerManager.h>
#include <iostream>

#include "SandBoxApplication.h"
#include "SandBoxLoggerManager.h"

auto main(const int argc, const char** argv) -> int {

    auto engine = Slimenano::Core::Engine::Engine();

    auto loggerManager = Slimenano::Core::Log::SPDLoggerManager();
    std::cout << loggerManager.GetModuleName() << " " << engine.Install(&loggerManager).GetState() << std::endl;

    auto sandboxLoggerManager = Slimenano::SandBox::SandBoxLoggerManager();
    std::cout << sandboxLoggerManager.GetModuleName() << " " << engine.Install(&sandboxLoggerManager).GetState() << std::endl;

    auto sandbox = Slimenano::SandBox::SandBoxApplication();
    std::cout << engine.Install(&sandbox).GetState() << std::endl;

    engine.Start();

    return 0;
}
