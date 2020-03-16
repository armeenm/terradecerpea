#pragma once

#include "ilanta/io/logic_level.h"
#include <gpiod.hpp>

using ilanta::LogicLevel;

class Compressor {
public:
  Compressor(gpiod::line&& enable_line, LogicLevel active_state = LogicLevel::LOW);

  Compressor(Compressor const&) = delete;
  Compressor(Compressor&&) noexcept = default;

  auto operator=(Compressor const&) -> Compressor& = delete;
  auto operator=(Compressor&&) noexcept -> Compressor& = default;

  ~Compressor() = default;

  auto enabled() const noexcept -> bool;

  auto set(bool enable) noexcept -> void;

private:
  gpiod::line enable_line_;
  bool enabled_;
};
