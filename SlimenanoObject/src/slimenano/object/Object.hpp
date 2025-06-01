#pragma once
#ifndef SLIMENANO_OBJECT_OBJECT_HPP
#define SLIMENANO_OBJECT_OBJECT_HPP

#    include <cstddef>
#    include <functional>

namespace slimenano {
namespace object {

class Object {
public:
    Object() = default;
    virtual ~Object() = default;
    virtual auto trace(std::function<auto(Object*) -> void> visitor) -> void = 0;
private:
    size_t m_Handle;
};

} // namespace object
} // namespace slimenano


#endif //SLIMENANO_OBJECT_OBJECT_HPP