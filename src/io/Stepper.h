#pragma once

#include <cstdint>
#include <gpiod.hpp>

class Stepper {
public:
  struct Pins {
    unsigned int step, dir, enable;
    std::optional<unsigned int> ms1, ms2, ms3;
  };

  Stepper(Pins, gpiod::chip);

  Stepper(Stepper const&) = delete;
  Stepper(Stepper&&) noexcept = default;

  auto operator=(Stepper const&) -> Stepper& = delete;
  auto operator=(Stepper &&) -> Stepper& = default;

  ~Stepper() = default;

private:
  Pins pins_;
  gpiod::chip chip_;
};
