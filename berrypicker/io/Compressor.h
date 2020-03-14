#pragma once

#include <gpiod.hpp>

class Compressor {
public:
  struct Config {
    gpiod::line enable_line;
  };

  struct State {
    bool enabled;
  };

  Relay(Config);

  Relay(Relay const&) = delete;
  Relay(Relay&&) noexcept = default;

  auto operator=(Relay const&) -> Relay& = delete;
  auto operator=(Relay&&) noexcept -> Relay& = default;

  ~Relay() = default;

  auto state() const noexcept -> State;
  auto set(bool enable) noexcept -> void;
  auto periodic() noexcept -> void;

private:
  gpiod::line enable_line_;
  State state_;
};
