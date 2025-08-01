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
#ifndef SLIMENANO_PROJECT_ENGINE_CORE_MODULE_I_MODULE_H
#    define SLIMENANO_PROJECT_ENGINE_CORE_MODULE_I_MODULE_H

#    include <vector>
#    include "../Base/Status.h"
#    include "../Base/Types.h"

namespace Slimenano::Core::Engine {
class Engine;
}

namespace Slimenano::Core::Module {

class SLIMENANO_API ModuleDependenciesTree {

  public:
    ModuleDependenciesTree() { m_pTail = &m_root; }

    template <class T>
    auto AddModule() -> void {
        auto pModuleId = Base::TypeId::Get<T>();
        m_pTail->m_pNext = new Node(pModuleId);
        m_pTail = m_pTail->m_pNext;
    }

    inline auto GetModules(std::vector<Base::TypeId*> out) const -> void {
        Node* pNode = m_root.m_pNext;
        while (pNode != nullptr) {
            if (pNode->m_pModuleId != nullptr) {
                out.push_back(pNode->m_pModuleId);
            }
            pNode = pNode->m_pNext;
        }
    }

  private:
    class SLIMENANO_API Node {
      public:
        inline Node(Base::TypeId* pModuleId) : m_pModuleId(pModuleId) {}
        inline ~Node() {
            if (m_pNext) {
                delete m_pNext;
            }
        }
        Node* m_pNext = nullptr;
        Base::TypeId* m_pModuleId = nullptr;
    };

    Node m_root = Node(nullptr);
    Node* m_pTail = nullptr;
};

/**
 * @brief Base interface for all engine modules
 */
class SLIMENANO_API IModule {
  public:
    virtual ~IModule() = default;

    /**
     * @brief Called when the module is initialized during engine startup
     * @return true if initialized successfully
     */
    virtual auto OnInit() -> Base::Status = 0;

    /**
     * @brief Called when the module is being shut down during engine shutdown
     */
    virtual auto OnShutdown() -> Base::Status = 0;

    /**
     * @brief Called every frame after engine startup
     */
    virtual auto OnUpdate() -> Base::Status = 0;

    /**
     * @brief Returns the name of the module (for logging or debugging)
     * @return const char* representing the module name
     */
    virtual auto GetModuleName() const -> const char* = 0;

    virtual auto GetModuleId() const -> const Base::TypeId* = 0;

    virtual auto GetModuleDependencies() const -> const ModuleDependenciesTree& = 0;
};
} // namespace Slimenano::Core::Module

#endif
