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
#ifndef SLIMENANO_PROJECT_ENGINE_CORE_EXCEPTION_I_EXCEPTION_HANDLER_H
#    define SLIMENANO_PROJECT_ENGINE_CORE_EXCEPTION_I_EXCEPTION_HANDLER_H

#    include "../Base/Status.h"
#    include "../Base/Export.h"
#    include "../Module/IBaseModule.h"

namespace Slimenano::Core::Exception {
class SLIMENANO_API IExceptionHandler : public Module::IBaseModule<IExceptionHandler> {
  public:
    virtual void Handle(Base::Status status) = 0;
    virtual void Handle(Base::Status status, const char* message) = 0;
};
} // namespace Slimenano::Core::Exception
#endif
