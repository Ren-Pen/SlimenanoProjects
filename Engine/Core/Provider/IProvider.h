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
#ifndef SLIMENANO_PROJECT_ENGINE_CORE_PROVIDER_PROVIDER_H
#define SLIMENANO_PROJECT_ENGINE_CORE_PROVIDER_PROVIDER_H

/**
 * This interface defines a contract for service providers.
 * Implementations of this interface should be registered with the ProviderManager.
 * When the system requires a specific module, it retrieves a Provider from the ProviderManager,
 * and then obtains the corresponding Service interface from the Provider for use.
 */
class IProvider {

    IProvider() = default;
    virtual ~IProvider() = default;
    

};


#endif //SLIMENANO_PROJECT_ENGINE_CORE_PROVIDER_PROVIDER_H