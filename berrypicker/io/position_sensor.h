#pragma once

#include <ilanta/control/pose.hpp>
#include <optional>
#include <polhemus.hpp>

namespace plhm = polhemus;

class PositionSensor {
public:
  [[nodiscard]] PositionSensor(plhm::DevType);
  [[nodiscard]] PositionSensor() : PositionSensor{plhm::DevType::PATRIOT_HS} {}

  PositionSensor(PositionSensor const&) = delete;
  PositionSensor(PositionSensor&&) noexcept = default;

  auto operator=(PositionSensor const&) -> PositionSensor& = delete;
  auto operator=(PositionSensor&&) noexcept -> PositionSensor& = default;

  ~PositionSensor() = default;

  auto pose() const noexcept -> std::optional<ilanta::PoseTL<float>>;

private:
  plhm::DevHandle sensor_;
};
