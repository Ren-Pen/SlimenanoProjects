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
#ifndef SLIMENANO_PROJECT_ENGINE_CORE_BASE_EXPORT_H
#    define SLIMENANO_PROJECT_ENGINE_CORE_BASE_EXPORT_H

#    ifdef SLIMENANO_SHARED

#        ifdef _MSC_VER

#            ifdef SLIMENANO_CORE_LIBRARY
#                define SLIMENANO_CORE_API __declspec(dllexport)
#            else
#                define SLIMENANO_CORE_API __declspec(dllimport)
#            endif //! SLIMENANO_CORE_LIBRARY

#            ifdef SLIMENANO_RUNTIME_LIBRARY
#                define SLIMENANO_RUNTIME_API __declspec(dllexport)
#            else
#                define SLIMENANO_RUNTIME_API __declspec(dllimport)
#            endif //! SLIMENANO_RUNTIME_LIBRARY

#        elif __GNUC__

#            ifdef SLIMENANO_CORE_LIBRARY
#                define SLIMENANO_CORE_API __attribute__((visibility("default")))
#            else
#                define SLIMENANO_CORE_API
#            endif //! SLIMENANO_CORE_LIBRARY

#            ifdef SLIMENANO_RUNTIME_LIBRARY
#                define SLIMENANO_RUNTIME_API __attribute__((visibility("default")))
#            else
#                define SLIMENANO_RUNTIME_API
#            endif //! SLIMENANO_RUNTIME_LIBRARY

#        else

#            define SLIMENANO_CORE_API
#            pragma warning Unknown dynamic link import / export semantics.
#            define SLIMENANO_RUNTIME_API
#            pragma warning Unknown dynamic link import / export semantics.

#        endif

#    else

#        define SLIMENANO_CORE_API
#        define SLIMENANO_RUNTIME_API

#    endif

#endif
