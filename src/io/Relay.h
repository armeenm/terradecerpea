#pragma once

#include <gpiod.hpp>

class Relay {
public:
  struct Pins {
    unsigned int stepper, compressor;
  };

  struct State {
    bool stepper, compressor;
  };

  Relay(Pins, gpiod::chip);

  Relay(Relay const&) = delete;
  Relay(Relay&&) noexcept = default;

  auto operator=(Relay const&) -> Relay& = delete;
  auto operator=(Relay&&) noexcept -> Relay& = default;

  ~Relay() = default;

  auto state() const noexcept -> State;

private:
  Pins pins_;
  gpiod::chip chip_;
  State state_;
};
