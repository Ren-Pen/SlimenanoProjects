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
#ifndef SLIMENANO_PROJECT_ENGINE_CORE_RESOURCE_I_RESOURCE_BASE_H
#define SLIMENANO_PROJECT_ENGINE_CORE_RESOURCE_I_RESOURCE_BASE_H
#include <cstddef>
#include <vector>
#include "../Export.h"
#include "../Base/Result.h"
#include "../Base/Status.h"

namespace Slimenano::Core::Resource {

using ResourceHandle = unsigned long long;

class SLIMENANO_CORE_API IResourceBase {
public:
    virtual ~IResourceBase() = default;
    virtual auto Open(const char* path, ResourceHandle& handle) -> Slimenano::Core::Base::Status = 0;
    virtual auto Close(const ResourceHandle handle) -> Slimenano::Core::Base::Status = 0;
    
    virtual auto Seek(const ResourceHandle handle, std::size_t offset, int origin) -> Slimenano::Core::Base::Status = 0;
    virtual auto Read(const ResourceHandle handle, void* buffer, size_t size) -> Slimenano::Core::Base::Result<size_t> = 0;
    virtual auto Write(const ResourceHandle handle, void* buffer, size_t size) -> Slimenano::Core::Base::Status = 0;

    virtual auto NewFile(const char* path) -> Slimenano::Core::Base::Status = 0;
    virtual auto List(const char* path) -> Slimenano::Core::Base::Result<std::vector<const char*>> = 0;
    virtual auto IsFile(const char* path) -> Slimenano::Core::Base::Result<bool> = 0;
};
} // namespace Slimenano::Core::Resource

#endif
