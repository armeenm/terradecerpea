#include "berrypicker/io/stepper.h"

Stepper::Stepper(Pins pins) : pins_(std::move(pins)) {
  if (!chip_)
    throw std::runtime_error("GPIO chip invalid");
}

// auto Stepper::move(Direction const dir, unsigned int steps) noexcept -> void {}
