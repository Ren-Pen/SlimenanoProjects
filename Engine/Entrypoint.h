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
#ifndef SLIMENANO_PROJECT_ENGINE_ENTRYPOINT_H
#    define SLIMENANO_PROJECT_ENGINE_ENTRYPOINT_H
#    include "Core/Base/IApplication.h"
#    include "Core/Provider/IProvider.h"
#    include "Core/Provider/ProviderManager.h"

namespace slimenano {
class Entrypoint final {
  public:
    template <class IApplication>
    static auto App(int argc, const char** argv) -> int;
};

template <class App>
class ApplicationProvider final : public IProvider<IApplication> {

  public:
    auto provide() -> std::unique_ptr<IApplication> override;
};

template <class App>
auto ApplicationProvider<App>::provide() -> std::unique_ptr<IApplication> {
    return std::make_unique<App>();
}

template <class Application>
auto Entrypoint::App(const int argc, const char** argv) -> int {

    ProviderManager::GetInstance().RegisterProvider<ApplicationProvider<Application>>();

    return 0;
}

} // namespace slimenano

#endif
