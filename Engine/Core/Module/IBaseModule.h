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
    virtual ~IBaseModule();

    virtual auto GetModuleId() const -> const Base::TypeId* override final;

    virtual auto GetModuleDependencies() const -> const ModuleDependenciesTree& override final;

    template <class MODULE>
    auto AddDependency() -> void;

    auto Install(Engine::Engine* engine) -> Base::Status;

    auto Uninstall() -> Base::Status;

    auto GetEngine() -> Engine::Engine*;

  protected:
    template <class MODULE>
    auto FindModule() -> MODULE*;

  private:
    Engine::Engine* m_pEngine = nullptr;
    ModuleDependenciesTree m_dependenciesTree = ModuleDependenciesTree();
};

template <class T>
auto IBaseModule<T>::GetModuleId() const -> const Base::TypeId* {
    return Base::TypeId::Get<T>();
}

template <class T>
auto IBaseModule<T>::GetModuleDependencies() const -> const ModuleDependenciesTree& {
    return this->m_dependenciesTree;
}

template <class T>
auto IBaseModule<T>::Install(Engine::Engine* engine) -> Base::Status {
    auto pEngineContext = engine->getEngineContext();
    if (pEngineContext) {
        auto status = pEngineContext->RegisterModule(this);
        if (status.IsSuccess()) {
            this->m_pEngine = engine;
        }
        return status;
    }

    return Base::Status::Success(Base::Status::Category::Internal);
}

template <class T>
auto IBaseModule<T>::Uninstall() -> Base::Status {
    auto pEngine = GetEngine();
    if (pEngine) {
        auto pEngineContext = pEngine->getEngineContext();
        if (pEngineContext) {
            auto status = pEngineContext->UnregisterModule(this);
            if (status.IsSuccess()) {
                this->m_pEngine = nullptr;
            }
            return status;
        }
    }
    return Base::Status::Success(Base::Status::Category::Internal);
}

template <class T>
IBaseModule<T>::~IBaseModule() {
    this->Uninstall();
}

template <class T>
auto IBaseModule<T>::GetEngine() -> Engine::Engine* {
    return this->m_pEngine;
}

template <class T>
template <class MODULE>
auto IBaseModule<T>::FindModule() -> MODULE* {
    auto pEngine = GetEngine();
    if (pEngine) {
        auto pEngineContext = pEngine->getEngineContext();
        if (pEngineContext) {
            return pEngineContext->template FindModule<MODULE>();
        }
    }
    return nullptr;
}

template <class T>
template <class MODULE>
auto IBaseModule<T>::AddDependency() -> void {
    this->m_dependenciesTree.AddModule<T>();
}

} // namespace Slimenano::Core::Module

#endif
