#include "io/Stepper.h"

Stepper::Stepper(Pins pins, gpiod::chip chip) : pins_(std::move(pins)), chip_(std::move(chip)) {
  if (!chip_)
    throw std::runtime_error("GPIO chip invalid");
}
