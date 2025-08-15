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
#ifndef SLIMENANO_PROJECT_ENGINE_CORE_MODULE_I_BASE_MODULE_H
#    define SLIMENANO_PROJECT_ENGINE_CORE_MODULE_I_BASE_MODULE_H

#    include "../Engine/Engine.h"
#    include "../Engine/EngineContext.h"
#    include "../Base/Types.h"
#    include "IModule.h"

namespace Slimenano::Core::Module {

/**
 * @brief Base interface for all engine modules
 */
template <class T>
class IBaseModule : public IModule {
  public:
    ~IBaseModule() override;

    [[nodiscard]] auto GetModuleId() const -> const Base::TypeId* final;

    [[nodiscard]] auto GetModuleStatusCategory() const -> Base::State override;

    auto Install(Engine::Engine* engine) -> Base::Status;

    auto Uninstall() -> Base::Status;

    [[nodiscard]] auto GetEngine() const -> Engine::Engine*;

  protected:
    template <class MODULE>
    auto FindModule() -> MODULE*;

  private:
    Engine::Engine* m_pEngine = nullptr;
};

template <class T>
auto IBaseModule<T>::GetModuleId() const -> const Base::TypeId* {
    return Base::TypeId::Get<T>();
}

template <class T>
auto IBaseModule<T>::GetModuleStatusCategory() const -> Base::State {
    return Base::Status::Category::Internal;
}

template <class T>
auto IBaseModule<T>::Install(Engine::Engine* engine) -> Base::Status {
    if (const auto pEngineContext = engine->getEngineContext()) {
        auto registerModuleStatus = pEngineContext->RegisterModule(this);
        if (registerModuleStatus.IsSuccess()) {
            this->m_pEngine = engine;
        }
        return registerModuleStatus;
    }

    return Base::Status::Success(Base::Status::Category::Internal);
}

template <class T>
auto IBaseModule<T>::Uninstall() -> Base::Status {
    if (const auto pEngine = GetEngine()) {
        if (const auto pEngineContext = pEngine->getEngineContext()) {
            auto unregisterModuleStatus = pEngineContext->UnregisterModule(this);
            if (unregisterModuleStatus.IsSuccess()) {
                this->m_pEngine = nullptr;
            }
            return unregisterModuleStatus;
        }
    }
    return Base::Status::Success(Base::Status::Category::Internal);
}

template <class T>
IBaseModule<T>::~IBaseModule() {
    this->Uninstall();
}

template <class T>
auto IBaseModule<T>::GetEngine() const -> Engine::Engine* {
    return this->m_pEngine;
}

template <class T>
template <class MODULE>
auto IBaseModule<T>::FindModule() -> MODULE* {
    if (const auto pEngine = GetEngine()) {
        if (const auto pEngineContext = pEngine->getEngineContext()) {
            return pEngineContext->template FindModule<MODULE>();
        }
    }
    return nullptr;
}

} // namespace Slimenano::Core::Module

#endif
