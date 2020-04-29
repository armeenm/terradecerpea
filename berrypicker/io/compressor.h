#pragma once

#include <gpiod.hpp>
#include <ilanta/io/logic_level.hpp>

using ilanta::LogicLevel;

class Compressor {
public:
  [[nodiscard]] Compressor(gpiod::line&& enable_line, LogicLevel active_state = LogicLevel::LOW);

  Compressor(Compressor const&) = delete;
  Compressor(Compressor&&) noexcept = default;

  auto operator=(Compressor const&) -> Compressor& = delete;
  auto operator=(Compressor&&) noexcept -> Compressor& = default;

  ~Compressor() = default;

  [[nodiscard]] auto enabled() const noexcept -> bool;

  auto set(bool enabled) noexcept -> void;
  auto enable() noexcept -> void;
  auto disable() noexcept -> void;

private:
  gpiod::line enable_line_;
  bool enabled_ = false;
};
