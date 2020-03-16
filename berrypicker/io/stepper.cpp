#include "berrypicker/io/stepper.h"

Stepper::Stepper(OffsetPins pins, gpiod::chip chip) {
  if (!chip)
    throw std::runtime_error("GPIO chip invalid");
}

// auto Stepper::move(Direction const dir, unsigned int steps) noexcept -> void {}
