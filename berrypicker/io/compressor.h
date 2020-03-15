#pragma once

#include <gpiod.hpp>

class Compressor {
public:
  struct Config {
    gpiod::line enable_line;
    bool is_active_low;
  };

  struct State {
    bool enabled;
  };

  Compressor(Config);

  Compressor(Compressor const&) = delete;
  Compressor(Compressor&&) noexcept = default;

  auto operator=(Compressor const&) -> Compressor& = delete;
  auto operator=(Compressor&&) noexcept -> Compressor& = default;

  ~Compressor() = default;

  auto state() const noexcept -> State;
  auto set(bool enable) noexcept -> void;
  auto periodic() noexcept -> void;

private:
  Config conf_;
  State state_;
};
