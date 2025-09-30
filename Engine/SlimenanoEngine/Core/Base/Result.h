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

#ifndef SLIMENANO_PROJECT_ENGINE_CORE_BASE_RESULT_H
#define SLIMENANO_PROJECT_ENGINE_CORE_BASE_RESULT_H

#include "Status.h"
#include <optional>
#include <utility>

namespace Slimenano::Core::Base {

template <typename T>
class Result {
public:
    constexpr Result(const Status status) noexcept :
        mStatus(status), mValue(std::nullopt) {}

    template <typename U>
    Result(const Status status, U&& value) noexcept :
        mStatus(status), mValue(std::forward<U>(value)) {}

    [[nodiscard]] constexpr auto IsSuccess() const -> bool {
        return mStatus.IsSuccess();
    }

    [[nodiscard]] constexpr auto IsFailure() const -> bool {
        return mStatus.IsFailure();
    }

    [[nodiscard]] constexpr const Status& GetStatus() const {
        return mStatus;
    }

    [[nodiscard]] bool HasValue() const {
        return mValue.has_value();
    }

    [[nodiscard]] const T& GetValue() const {
        return mValue.value();
    }

    [[nodiscard]] T& GetValue() {
        return mValue.value();
    }

private:
    Status mStatus;
    std::optional<T> mValue;
};

} // namespace Slimenano::Core::Base

#endif
