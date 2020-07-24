#pragma once

#include <gpiod.hpp>
#include <ilanta/hal/logic_level.hpp>

using ilanta::LogicLevel;

class Compressor {
 public:
  [[nodiscard]] Compressor(gpiod::line const& enable_line)
      : Compressor{enable_line, LogicLevel::Low} {}

  [[nodiscard]] Compressor(gpiod::line const& enable_line, LogicLevel active_state);

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
