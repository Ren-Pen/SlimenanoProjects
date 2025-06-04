#pragma once
#ifndef SLIMENANO_GC_MEM_I_GC_ALLOCATOR_HPP
#    define SLIMENANO_GC_MEM_I_GC_ALLOCATOR_HPP
#    include <cstddef>

namespace slimenano {
namespace gc {

using GCAddress = size_t;

class IGCAllocator {

  public:
    virtual auto Allocate(size_t size) -> GCAddress = 0;
    virtual auto Free(GCAddress address) -> void = 0;
    virtual auto GetSize(GCAddress address) const -> size_t = 0;
    virtual auto IsValid(GCAddress address) const -> bool = 0;

    virtual auto Get(GCAddress address) const -> const void* = 0;
    virtual auto Set(GCAddress address, const void* value) -> void = 0;
};

} // namespace gc
} // namespace slimenano

#endif
