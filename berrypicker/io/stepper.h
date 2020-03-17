#pragma once

#include <array>
#include <gpiod.hpp>
#include <ilanta/io/logic_level.hpp>
#include <optional>

using gpiod::line;

class Stepper {
public:
  // TODO: check directions
  enum Direction : int { FORWARD, REVERSE };

  struct Pins {
    line step, dir;
    std::optional<line> en = std::nullopt;
    std::optional<line> rst = std::nullopt;
    std::optional<line> sleep = std::nullopt;
    std::optional<std::array<line, 3>> ms = std::nullopt;
  };

  Stepper(Pins&&, ilanta::LogicLevel reverse = ilanta::LogicLevel::HIGH);

  Stepper(Stepper const&) = delete;
  Stepper(Stepper&&) noexcept = default;

  auto operator=(Stepper const&) -> Stepper& = delete;
  auto operator=(Stepper &&) -> Stepper& = default;

  ~Stepper() = default;

  auto move(Direction, unsigned int steps) noexcept -> void;

private:
  Pins pins_;
};
