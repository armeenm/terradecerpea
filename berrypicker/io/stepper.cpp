#include "berrypicker/io/stepper.h"

#include "berrypicker/constants.h"
#include <ilanta/io/gpiod.hpp>

#include <chrono>
#include <exception>
#include <spdlog/fmt/bundled/core.h>
#include <spdlog/spdlog.h>
#include <thread>

Stepper::Stepper(Pins&& pins, ilanta::LogicLevel const reverse) : pins_(std::move(pins)) {
  spdlog::info("Constructing Stepper");

  ILANTA_GPIO_OUTPUT_THROW(pins_.step);

  ILANTA_GPIO_OUTPUT_THROW(pins_.dir, reverse == ilanta::LogicLevel::LOW);

  if (pins_.en)
    ILANTA_GPIO_OUTPUT_THROW(*pins_.en, true);

  if (pins_.rst)
    ILANTA_GPIO_OUTPUT_THROW(*pins_.rst, true);

  if (pins_.sleep)
    ILANTA_GPIO_OUTPUT_THROW(*pins_.sleep, true);

  if (pins_.ms)
    for (auto&& pin : *pins_.ms)
      ILANTA_GPIO_OUTPUT_THROW(pin);
}

/**
 * Blocking function which moves the stepper motor a given number of steps in the specified
 * direction. Bitbangs a square wave; RT may be necessary for smooth movement of the stepper
 */
auto Stepper::move(Direction const dir, unsigned int const steps) noexcept -> void {
  using namespace std::chrono_literals;

  auto constexpr PERIOD_HALF = 50ns;

  // Set desired direction
  pins_.dir.set_value(dir);

  for (unsigned int i = 0; i < steps; i++) {
    pins_.step.set_value(1);
    std::this_thread::sleep_for(PERIOD_HALF);
    pins_.step.set_value(0);
    std::this_thread::sleep_for(PERIOD_HALF);
  }
}
