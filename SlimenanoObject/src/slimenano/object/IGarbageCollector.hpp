#pragma once
#ifndef SLIMENANO_OBJECT_I_GARBAGE_COLLECTOR_HPP
#define SLIMENANO_OBJECT_I_GARBAGE_COLLECTOR_HPP

namespace slimenano {
namespace object {
class Object;

class IGarbageCollector {
    public:
        IGarbageCollector() = default;
        virtual ~IGarbageCollector() = default;
    public:
        auto gc() -> void;
        template<typename T>
        auto CreateObject() -> T;
        template<typename T>
        auto DestroyObject() -> T;
    protected:
        virtual auto Start() -> void = 0;
        virtual auto Shutdown() -> void  = 0;

    };

} // namespace object
} // namespace slimenano

#endif //SLIMENANO_OBJECT_I_GARBAGE_COLLECTOR_HPP