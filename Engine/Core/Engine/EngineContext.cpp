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
#include <algorithm>
#include <vector>

#include "EngineContext.h"
#include "../Module/IModule.h"

namespace Slimenano::Core::Engine {

using namespace Base;
using namespace Module;

Status EngineContext::GetModules(std::vector<IModule*>& outModules) const {
    std::transform(m_modules.begin(), m_modules.end(), std::back_inserter(outModules), [](const auto& pair) {
        return pair.second;
    });
    return State(StateCategory::Internal, StateCode::kSuccess);
}

} // namespace Slimenano::Core::Engine
