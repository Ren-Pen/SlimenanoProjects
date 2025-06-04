#pragma once

#ifndef SLIMENANO_GC_GC_HANDLE_HPP
#    define SLIMENANO_GC_GC_HANDLE_HPP
#    include "slimenano/gc/IGarbageCollector.hpp"
#    include "slimenano/gc/mem/IGCAllocator.hpp"
namespace slimenano {
namespace gc {

class GCHandle {
    friend class IGarbageCollector;
    friend class GCBaseObject;

  public:
    GCHandle(const GCHandle&&) noexcept;
    GCHandle& operator=(const GCHandle&&) noexcept;

  private:
    GCHandle(class IGarbageCollector& owner, GCAddress address);
    GCHandle(const GCHandle&) = delete;
    GCHandle& operator=(const GCHandle&) = delete;

    auto Raw() const -> const void*;
    auto Raw() -> void*;
    auto Address() const -> GCAddress;
    auto IsNull() const -> bool;

  private:
    class IGarbageCollector& m_owner;
    GCAddress m_address;
};

} // namespace gc
} // namespace slimenano

#endif // SLIMENANO_GC_GC_HANDLE_HPP
