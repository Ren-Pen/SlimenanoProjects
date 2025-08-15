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

#    include "Export.h"

namespace Slimenano::Core::Base {

using State = unsigned long long;

class SLIMENANO_CORE_API Status {
  public:
    constexpr Status(State category, State code);
    constexpr Status(State category, State code, const char* message);

    [[nodiscard]] constexpr auto GetState() const -> State;
    [[nodiscard]] constexpr auto GetCategory() const -> State;
    [[nodiscard]] constexpr auto GetCode() const -> State;
    [[nodiscard]] constexpr auto GetMessage() const -> const char*;
    [[nodiscard]] constexpr auto IsSuccess() const -> bool;
    [[nodiscard]] constexpr auto IsFailure() const -> bool;

    constexpr static auto Success(State category) -> Status;
    constexpr static auto NullPointerException(State category) -> Status;

    class Category {
      public:
        constexpr static State Internal = 0x0000;
        constexpr static State Memory = 0x0001;
        constexpr static State Logger = 0x0002;
        constexpr static State Application = 0x0003;
    };

    class Code {
      public:
        constexpr static State Success = 0x0000;
        constexpr static State InvalidParameter = 0x0001;
        constexpr static State AlreadyExists = 0x0002;
        constexpr static State NotFound = 0x0003;
        constexpr static State NotPermitted = 0x0003;
    };

  private:
    const State m_category;
    const State m_code;
    const char* m_message;
};

constexpr Status::Status(const State category, const State code) : m_category(category & 0xFFFF), m_code(code & 0xFFFF), m_message("") {
}

constexpr Status::Status(const State category, const State code, const char* message) : m_category(category & 0xFFFF), m_code(code & 0xFFFF), m_message(message) {
}

constexpr auto Status::Success(State category) -> Status {
    return {category, Code::Success};
}

constexpr auto Status::NullPointerException(State category) -> Status {
    return {category, Code::InvalidParameter, "NullPointerException"};
}

constexpr auto Status::GetState() const -> State {
    return (this->m_category << 16) & 0xFFFF0000 | this->m_code & 0xFFFF;
}

constexpr auto Status::GetCategory() const -> State {
    return this->m_category;
}

constexpr auto Status::GetCode() const -> State {
    return this->m_code;
}

constexpr auto Status::GetMessage() const -> const char* {
    return this->m_message;
}

constexpr auto Status::IsSuccess() const -> bool {
    return m_code == Code::Success;
}

constexpr auto Status::IsFailure() const -> bool {
    return !this->IsSuccess();
}

} // namespace Slimenano::Core::Base
#endif
