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
#ifndef SLIMENANO_PROJECT_ENGINE_CORE_BASE_STATUS_H
#    define SLIMENANO_PROJECT_ENGINE_CORE_BASE_STATUS_H

namespace Slimenano::Core::Base {
using Status = unsigned long long;

class StateCategory {
  public:
    constexpr static Status Internal = 0x0000;
    constexpr static Status Application = 0x0000;
};

class StateCode {
  public:
    constexpr static Status kSuccess = 0x0000;
    constexpr static Status kInvalidParameter = 0x0001;
    constexpr static Status kAlreadyExists = 0x0002;
};

static inline Status State(Status category, Status code) {
    return category << 16 | code;
}

static inline Status Category(Status status) {
    return (status >> 16) & 0xFFFF;
}

static inline Status Code(Status status) {
    return status & 0xFFFF;
}

static inline bool IsSuccess(Status status) {
    return Code(status) == StateCode::kSuccess;
}


static inline bool IsFailure(Status status) {
    return Code(status) != StateCode::kSuccess;
}

} // namespace Slimenano::Core::Base
#endif
