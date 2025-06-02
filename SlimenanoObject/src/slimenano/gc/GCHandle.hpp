#pragma once
#ifndef SLIMENANO_GC_GC_HANDLE_HPP
#    define SLIMENANO_GC_GC_HANDLE_HPP

namespace slimenano {
namespace gc {

#include <cstddef>

class CGHandle {
  public:
private:
    size_t m_handle;
};

} // namespace gc
} // namespace slimenano

#endif // SLIMENANO_GC_GC_HANDLE_HPP