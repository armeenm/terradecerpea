#pragma once

#include <type_traits>

namespace ilanta {
namespace util {

template <typename E> auto to_underlying(E e) {
  return static_cast<typename std::underlying_type_t<E>>(e);
}

} // namespace util
} // namespace ilanta
