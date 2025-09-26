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

#include "../Export.h"
#include "../Base/TypesImpl.h"

#include "IResourceManager.h"

template SLIMENANO_CORE_API auto Slimenano::Core::Base::TypeId::Get<Slimenano::Core::Resource::IResourceManager>() -> const Slimenano::Core::Base::TypeId*;
