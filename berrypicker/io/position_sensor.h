#pragma once

#include "ilanta/control/pose.h"
#include <optional>
#include <polhemus.hpp>

namespace plhm = polhemus;

class PositionSensor {
public:
  PositionSensor(plhm::DevType = plhm::PATRIOT_HS);

  PositionSensor(PositionSensor const&) = delete;
  PositionSensor(PositionSensor&&) noexcept = default;

  auto operator=(PositionSensor const&) -> PositionSensor& = delete;
  auto operator=(PositionSensor&&) noexcept -> PositionSensor& = default;

  ~PositionSensor() = default;

  auto pose() const noexcept -> std::optional<PoseTL>;

private:
  plhm::DevHandle sensor_;
};
