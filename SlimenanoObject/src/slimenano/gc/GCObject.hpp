#pragma once
#ifndef SLIMENANO_GC_GC_OBJECT_HPP
#    define SLIMENANO_GC_GC_OBJECT_HPP

namespace slimenano {
namespace gc {

template <typename T>
class GCObject final {
  public:
    template <typename... Args>
    static auto New(Args... args) -> GCObject;

  protected:
    GCObject() = default;
    ~GCObject() = default;

};

} // namespace gc
} // namespace slimenano

#endif // SLIMENANO_GC_GC_OBJECT_HPP