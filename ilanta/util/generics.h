#pragma once

#include <type_traits>

namespace ilanta {
namespace util {

template <typename E> constexpr auto underlying_cast(E e) {
  return static_cast<typename std::underlying_type_t<E>>(e);
}

} // namespace util
} // namespace ilanta
