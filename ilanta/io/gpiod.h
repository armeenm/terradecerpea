#pragma once

#include "ilanta/util/strify.h"

#include <exception>
#include <fmt/core.h>
#include <gpiod.hpp>
#include <string_view>

#define ILANTA_GPIO_OUTPUT_THROW(l, ...)                                                           \
  success = ilanta::request_output(l, CONSUMER_NAME __VA_OPT__(, ) __VA_ARGS__);                   \
  if (!success)                                                                                    \
  throw std::runtime_error(                                                                        \
      fmt::format("Failed to request " ILANTA_STRIFY(l) " line; offset {}", (l).offset()))

namespace ilanta {

auto request_output(gpiod::line const& l, std::string_view consumer, bool invert = false,
                    int default_val = 0) -> bool;

} // namespace ilanta
