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
#include <vector>
#include "../Base/Types.h"
#include "ModuleDependenciesTree.h"

namespace Slimenano::Core::Module {

ModuleDependenciesTree::ModuleDependenciesTree() {
    m_pTail = &m_root;
}

auto ModuleDependenciesTree::GetModules(std::vector<Base::TypeId*> out) const -> void {
    const Node* pNode = m_root.m_pNext;
    while (pNode != nullptr) {
        if (pNode->m_pModuleId != nullptr) {
            out.push_back(pNode->m_pModuleId);
        }
        pNode = pNode->m_pNext;
    }
}
ModuleDependenciesTree::Node::Node(Base::TypeId* pModuleId) : m_pModuleId(pModuleId) {
}
ModuleDependenciesTree::Node::~Node() {
    delete m_pNext;
}

} // namespace Slimenano::Core::Module
