#pragma once
#ifndef SLIMENANO_GC_I_GARBAGE_COLLECTOR_HPP
#    define SLIMENANO_GC_I_GARBAGE_COLLECTOR_HPP

namespace slimenano {
namespace gc {

class IGarbageCollector {
    friend class GarbageCollectorManager;
  public:
    using GCAddress = size_t;
    IGarbageCollector() = default;
    virtual ~IGarbageCollector() = default;

  public:
    auto Collect() -> void;

  protected:
    virtual auto Start() -> void = 0;
    virtual auto Shutdown() -> void = 0;

  protected:
    virtual auto Allocate(size_t size) -> GCAddress = 0;
    virtual auto Free(GCAddress address) -> void = 0;
    virtual auto GetSize(GCAddress address) const -> size_t = 0;
    virtual auto IsValid(GCAddress address) const -> bool = 0;

    virtual auto Get(GCAddress address) -> void* = 0;
    virtual auto Get(GCAddress address) const -> const void* = 0;

    virtual auto Set(GCAddress address, void* value) -> void = 0;
    virtual auto Set(GCAddress address, const void* value) -> void = 0;

};

} // namespace gc
} // namespace slimenano

#endif // SLIMENANO_GC_I_GARBAGE_COLLECTOR_HPP
