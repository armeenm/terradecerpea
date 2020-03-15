#pragma once

#include "berrypicker/data.h"
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

  auto get() const noexcept -> Pose;

private:
  plhm::DevHandle const sensor_;
};
