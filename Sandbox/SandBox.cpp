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
#include <SlimenanoEngine.h>

class Sandbox final : public slimenano::IApplication {
  public:
    ~Sandbox() override = default;
    auto Initialize() -> void override {}

    auto Shutdown() -> void override {}
};

auto main(const int argc, const char** argv) -> int {
    slimenano::Entrypoint::App<Sandbox>(argc, argv);
    return 0;
}
