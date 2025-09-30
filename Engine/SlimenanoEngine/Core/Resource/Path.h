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
#ifndef SLIMENANO_PROJECT_ENGINE_CORE_RESOURCE_PATH_H
#define SLIMENANO_PROJECT_ENGINE_CORE_RESOURCE_PATH_H

namespace Slimenano::Core::Resource {

     // @brief 引擎内所有的资源访问用的路径类
     // 路径的格式 <namespace>:/path/to/resource
     // 引擎中的有一个资源包的抽象概念，资源包拥有一个命名空间并且拥有一个虚拟的分区表指向文件的路径，通过虚拟的路径从资源包里获取一个资源的handle从而实现对资源的读写
     // 比如想要新建一个配置的时候可以
     // auto pResMgr = engine->FindModule<IResourceManager>();
     // auto config = FileResourceBundle::Config();
     // config.addFile("C:/test/asset/0E2091847220475830213", "/test-pic.jpg");
     // config.addFile("C:/test/asset/0E2091847220475830214", "/test-pic2.jpg");
     // config.mount("C:/test/asset2", "/asset2");
     // pResMgr->CreateBundle<"Test::Asset", FileResourceBundle>(config);
     // auto Handle = pResMgr->Open("Test::Asset:/test-pic.jpg");
    class Path{

    };

}

#endif
