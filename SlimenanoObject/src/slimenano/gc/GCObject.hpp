#pragma once
#ifndef SLIMENANO_GC_GC_OBJECT_HPP
#    define SLIMENANO_GC_GC_OBJECT_HPP
#    include <cstddef>
#    include "slimenano/gc/GCHandle.hpp"

#    define SLIMENANO_GC_OBJECT(cls) slimenano::gc::GCObject<cls>
#    define SLIMENANO_GC_CLASS(cls) class cls : public SLIMENANO_GC_OBJECT(cls)

namespace slimenano {
namespace gc {

class GCBaseObject {

    template <typename T>
    friend class GCObject;

  private:
    explicit GCBaseObject(size_t size);
    virtual ~GCBaseObject();

  private:
    class GCHandle m_handle;
};

template <typename T>
class GCObject : public GCBaseObject {
  public:
    template <typename... Args>
    static auto New(Args... args) -> GCObject;
    static auto Null() -> GCObject;

  public:
    virtual ~GCObject() = default;

  protected:
    GCObject() : GCBaseObject(sizeof(T)) {}
};

} // namespace gc
} // namespace slimenano

#endif // SLIMENANO_GC_GC_OBJECT_HPPs
