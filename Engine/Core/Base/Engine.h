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
#ifndef SLIMENANO_PROJECT_ENGINE_CORE_BASE_ENGINE_H
#    define SLIMENANO_PROJECT_ENGINE_CORE_BASE_ENGINE_H

namespace slimenano {

class Engine final {
public:
    static auto GetInstance() -> Engine&;

    ~Engine() = default;
    Engine(const Engine& other) = delete;
    Engine(Engine&& other) noexcept = delete;
    Engine& operator=(const Engine& other) = delete;
    Engine& operator=(Engine&& other) noexcept = delete;

    auto Initialize() -> void;
    // auto Start() -> void;
    // auto Shutdown() -> void;
    // auto IsRunning() -> bool;
    // auto IsInitialized() -> bool;

private:
    Engine() = default;
};

} // namespace slimenano

#endif // SLIMENANO_PROJECT_ENGINE_CORE_BASE_ENGINE_H
