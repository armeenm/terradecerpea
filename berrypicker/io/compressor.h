#pragma once

#include "ilanta/io/logic_level.h"
#include <gpiod.hpp>

class Compressor {
public:
  Compressor(gpiod::line enable_line, ilanta::io::LogicLevel active_state = LogicLevel::LOW);

  Compressor(Compressor const&) = delete;
  Compressor(Compressor&&) noexcept = default;

  auto operator=(Compressor const&) -> Compressor& = delete;
  auto operator=(Compressor&&) noexcept -> Compressor& = default;

  ~Compressor() = default;

  auto active_state() const noexcept -> ilanta::io::LogicLevel;
  auto enabled() const noexcept -> bool;

  auto set(bool enable) noexcept -> void;

private:
  ilanta::io::LogicLevel active_state_;
  bool enabled_;

  gpiod::line enable_line_;
};
