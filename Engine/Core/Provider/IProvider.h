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
#ifndef SLIMENANO_PROJECT_ENGINE_CORE_PROVIDER_I_PROVIDER_H
#    define SLIMENANO_PROJECT_ENGINE_CORE_PROVIDER_I_PROVIDER_H
#    include <memory>
#    include "Base/Types.h"

namespace slimenano {

/**
 * @class IBaseProvider
 * @brief Serves as the base class for all providers managed by the ProviderManager.
 *
 * This class uses type erasure to provide a unified interface for managing various
 * providers in the system.
 */
class IBaseProvider {
    friend class ProviderManager;

  public:
    IBaseProvider() = default;
    virtual ~IBaseProvider() = default;

  protected:
    /**
     * @brief Retrieves a raw pointer to the underlying provider object.
     * @return A void pointer to the actual provider.
     */
    virtual auto getRawPtr() -> RawPtr = 0;
    /**
     * @brief Retrieves the unique type identifier (TypeId) of the provider.
     * @return A pointer to the TypeId of the provider.
     */
    virtual auto getTypeId() const -> TypeId* = 0;
};

/**
 * @class IProvider
 * @brief Defines a contract for specialized service providers.
 *
 * @details This interface extends `IBaseProvider` and provides a typed template
 * to represent service providers. Implementations of this interface must be registered
 * with the `ProviderManager`. When the system requires a specific module,
 * the `ProviderManager` will retrieve a `Provider` implementation and utilize
 * the corresponding service interface provided by it.
 */
template <typename T>
class IProvider : private IBaseProvider {

  public:
    IProvider() = default;
    virtual ~IProvider() = default;

    /**
     * @brief Provides a unique pointer to the specific service instance.
     * @return A unique pointer containing the service interface of type `T`.
     */
    virtual auto provide() -> std::unique_ptr<T*> = 0;

  private:
    /**
     * @brief Retrieves a raw pointer to the underlying provider object.
     * Overrides the implementation in `IBaseProvider`.
     * @return A void pointer to the actual provider.
     */
    virtual auto getRawPtr() -> RawPtr override;

    /**
     * @brief Retrieves the unique type identifier (TypeId) of the provider.
     * Overrides the implementation in `IBaseProvider`.
     * @return A pointer to the TypeId of the provider.
     */
    virtual auto getTypeId() const -> TypeId* override;
};

template <typename T>
auto IProvider<T>::getRawPtr() -> RawPtr {
    return static_cast<RawPtr>(this);
}

template <typename T>
auto IProvider<T>::getTypeId() const -> TypeId* {
    return TypeId::Get<T>();
}

} // namespace slimenano

#endif // SLIMENANO_PROJECT_ENGINE_CORE_PROVIDER_PROVIDER_H
