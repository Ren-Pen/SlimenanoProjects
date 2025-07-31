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

#include "../Base/Export.h"
#include "../Base/TypesImpl.h"
#include "IApplication.h"
template SLIMENANO_API auto Slimenano::Core::Base::TypeId::Get<Slimenano::Core::Application::IApplication>() -> const Slimenano::Core::Base::TypeId*;

namespace Slimenano::Core::Application {

auto IApplication::GetLoggerManager() -> Log::ILoggerManager* {
    return FindModule<Log::ILoggerManager>();
}

auto IApplication::GetExceptionHandler() -> Exception::IExceptionHandler* {
    return FindModule<Exception::IExceptionHandler>();
}

} // namespace Slimenano::Core::Application
