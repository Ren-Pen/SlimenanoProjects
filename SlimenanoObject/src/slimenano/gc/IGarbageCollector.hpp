#pragma once
#ifndef SLIMENANO_GC_I_GARBAGE_COLLECTOR_HPP
#    define SLIMENANO_GC_I_GARBAGE_COLLECTOR_HPP

#include "slimenano/gc/mem/IGCAllocator.hpp"
#include "slimenano/gc/GCHandle.hpp"

namespace slimenano {
namespace gc {

class IGarbageCollector {
    friend class GarbageCollectorManager;
    friend class GCHandle;

  public:
    IGarbageCollector() = default;
    virtual ~IGarbageCollector() = default;

  public:
    auto Collect() -> void;
    virtual auto Start() -> void = 0;
    virtual auto Shutdown() -> void = 0;

  protected:
    virtual auto Allocator() -> IGCAllocator&;
};

} // namespace gc
} // namespace slimenano

#endif // SLIMENANO_GC_I_GARBAGE_COLLECTOR_HPP
