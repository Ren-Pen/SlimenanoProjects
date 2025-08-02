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
#ifndef SLIMENANO_PROJECT_ENGINE_CORE_MODULE_MODULE_DEPENDENCIES_TREE_H
#    define SLIMENANO_PROJECT_ENGINE_CORE_MODULE_MODULE_DEPENDENCIES_TREE_H
#    include <vector>
#    include "../Base/Types.h"
namespace Slimenano::Core::Module {
class SLIMENANO_API ModuleDependenciesTree {

  public:
    ModuleDependenciesTree();

    template <class T>
    auto AddModule() -> void {
        auto pModuleId = Base::TypeId::Get<T>();
        m_pTail->m_pNext = new Node(pModuleId);
        m_pTail = m_pTail->m_pNext;
    }

    auto GetModules(std::vector<Base::TypeId*> out) const -> void;

  private:
    class SLIMENANO_API Node {
      public:
        explicit Node(Base::TypeId* pModuleId);
        ~Node();
        Node* m_pNext = nullptr;
        Base::TypeId* m_pModuleId = nullptr;
    };

    Node m_root = Node(nullptr);
    Node* m_pTail = nullptr;
};
} // namespace Slimenano::Core::Module
#endif
