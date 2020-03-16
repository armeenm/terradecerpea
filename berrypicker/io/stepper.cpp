#include "berrypicker/io/stepper.h"

#include "berrypicker/constants.h"
#include "ilanta/io/gpiod.h"
#include "ilanta/util/generics.h"

#include <exception>
#include <fmt/core.h>
#include <spdlog/spdlog.h>

Stepper::Stepper(Pins&& pins, ilanta::LogicLevel reverse) : pins_(std::move(pins)) {
  spdlog::info("Constructing Stepper");

  // auto success...
  auto ILANTA_GPIO_OUTPUT_THROW(pins_.step);

  ILANTA_GPIO_OUTPUT_THROW(pins_.dir, reverse == ilanta::LogicLevel::LOW);

  if (pins_.en) {
    ILANTA_GPIO_OUTPUT_THROW(*pins_.en, true);
  }

  if (pins_.rst)
    ILANTA_GPIO_OUTPUT_THROW(*pins_.rst, true);

  if (pins_.sleep)
    ILANTA_GPIO_OUTPUT_THROW(*pins_.sleep, true);

  if (pins_.ms)
    for (auto&& pin : *pins_.ms) {
      ILANTA_GPIO_OUTPUT_THROW(pin);
    }
}

/**
 * Blocking function which moves the stepper motor a given number of steps in the specified
 * direction. Bitbangs a square wave; RT may be necessary for smooth movement of the stepper
 */
auto Stepper::move(Direction const dir, unsigned int steps) noexcept -> unsigned int {
  unsigned int i = 0;
  pins_.dir.set_value(ilanta::underlying_cast(dir));
  for (; i < steps; i++) {
    // pins_.
  }
}
