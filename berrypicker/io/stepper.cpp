#include "berrypicker/io/stepper.h"

#include <ilanta/io/gpiod.hpp>

#include <chrono>
#include <exception>
#include <spdlog/spdlog.h>
#include <thread>

Stepper::Stepper(Pins&& pins, ilanta::LogicLevel const reverse) : pins_(std::move(pins)) {
  spdlog::info("Constructing Stepper");

  auto constexpr setup_l = [](gpiod::line const& l, auto&&... ts) {
    ilanta::request_output(l, "Berrypicker", std::forward<decltype(ts)>(ts)...);
  };

  setup_l(pins_.step);

  setup_l(pins_.dir, reverse == ilanta::LogicLevel::LOW);

  if (pins_.en)
    setup_l(*pins_.en, true);

  if (pins_.rst)
    setup_l(*pins_.rst, true);

  if (pins_.sleep)
    setup_l(*pins_.sleep, true);

  if (pins_.ms)
    for (const auto& pin : *pins_.ms)
      setup_l(pin);
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
