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
#ifndef SLIMENANO_PROJECT_ENGINE_CORE_MODULE_I_MODULE_H
#define SLIMENANO_PROJECT_ENGINE_CORE_MODULE_I_MODULE_H
#include "../Base/Status.h"
#include "../Base/Types.h"

namespace Slimenano::Core::Engine {
class Engine;
}

namespace Slimenano::Core::Module {

/**
 * @brief Base interface for all engine modules
 */
class SLIMENANO_CORE_API IModule {
public:
    virtual ~IModule() = default;

    /**
     * @brief
     *
     * @param Engine
     * @return Slimenano::Core::Base::Status
     */
    virtual auto OnInstall(Slimenano::Core::Engine::Engine* context) -> Slimenano::Core::Base::Status = 0;

    /**
     * @brief
     *
     * @return Slimenano::Core::Base::Status
     */
    virtual auto OnUninstall() -> void = 0;

    /**
     * @brief Called when the module is initialized during engine startup
     * @return true if initialized successfully
     */
    virtual auto OnInit() -> Slimenano::Core::Base::Status = 0;

    /**
     * @brief Called when the module is being shut down during engine shutdown
     */
    virtual auto OnShutdown() -> Slimenano::Core::Base::Status = 0;

    /**
     * @brief Called every frame after engine startup
     */
    virtual auto OnUpdate() -> Slimenano::Core::Base::Status = 0;

    /**
     * @brief Returns the name of the module (for logging or debugging)
     * @return const char* representing the module name
     */
    [[nodiscard]] virtual auto GetModuleName() const -> const char* = 0;

    [[nodiscard]] virtual auto GetModuleId() const -> const Slimenano::Core::Base::TypeId* = 0;

    [[nodiscard]] virtual auto GetModuleStatusCategory() const -> Slimenano::Core::Base::State = 0;
};
} // namespace Slimenano::Core::Module

#define SLIMENANO_DECLARE_MODULE(API, NAMESPACE, MODULE)                                                    \
    namespace NAMESPACE{                                                                                    \
        class MODULE;                                                                                       \
        class API Typed##MODULE : public ::Slimenano::Core::Module::IModule {                               \
            public:                                                                                         \
            [[nodiscard]] virtual auto GetModuleId() const -> const Slimenano::Core::Base::TypeId* final;   \
        };                                                                                                  \
    }                                                                                                       \
    SLIMENANO_DECLARE_TYPEID(API, NAMESPACE::MODULE)

#define SLIMENANO_DEFINE_MODULE(API, NAMESPACE, MODULE)                                                     \
    namespace NAMESPACE {                                                                                   \
        [[nodiscard]] auto Typed##MODULE::GetModuleId() const -> const Slimenano::Core::Base::TypeId* {     \
            return Slimenano::Core::Base::TypeId::Get<MODULE>();                                            \
        }                                                                                                   \
    }                                                                                                       \
    SLIMENANO_DEFINE_TYPEID(API, NAMESPACE::MODULE)

#endif
