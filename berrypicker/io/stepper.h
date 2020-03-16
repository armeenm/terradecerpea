#pragma once

#include <gpiod.hpp>
#include <optional>

class Stepper {
public:
  template <typename T> struct GenericPins {
    T step, dir, enable;
    std::optional<T> ms1 = std::nullopt;
    std::optional<T> ms2 = std::nullopt;
    std::optional<T> ms3 = std::nullopt;
  };

  using OffsetPins = GenericPins<unsigned int>;
  using LinePins = GenericPins<gpiod::line>;

  Stepper(OffsetPins, gpiod::chip);

  Stepper(Stepper const&) = delete;
  Stepper(Stepper&&) noexcept = default;

  auto operator=(Stepper const&) -> Stepper& = delete;
  auto operator=(Stepper &&) -> Stepper& = default;

  ~Stepper() = default;

private:
  LinePins pins_;
  gpiod::chip chip_;
};
