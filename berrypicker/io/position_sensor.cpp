#include "berrypicker/io/position_sensor.h"

#include <array>
#include <exception>
#include <fmt/core.h>
#include <spdlog/spdlog.h>
#include <string>

constexpr int MAX_RESP_SIZE = 1000;

PositionSensor::PositionSensor(plhm::DevType dev_type)
    : sensor_(plhm::DevHandle(nullptr, dev_type)) {
  spdlog::info("Constructing PositionSensor of type {}", dev_type);

  if (!sensor_.check_connection()) {
    auto const err = fmt::format("Failed to create Polhemus sensor of type {}", dev_type);
    spdlog::error(err);
    throw std::runtime_error(err);
  }

  sensor_.send_cmd("F0", MAX_RESP_SIZE);
  sensor_.send_cmd("U1", MAX_RESP_SIZE);
  sensor_.send_cmd("O*,2", MAX_RESP_SIZE);
}

auto PositionSensor::pose() const noexcept -> std::optional<PoseTL> {
  // TODO: Make libpolhemus not throw here
  try {
    auto pose = PoseTL();
    auto const delim = ',';
    auto const resp_str = sensor_.send_cmd("p", MAX_RESP_SIZE);

    auto const delim1 = std::find(std::begin(resp_str), std::end(resp_str), delim);
    [[unlikely]] if (delim1 == std::end(resp_str)) {
      spdlog::error("Pose data from sensor was invalid");
      return std::nullopt;
    }

    auto const delim2 = std::find(delim1 + 1, std::end(resp_str), delim);

    pose.x = std::stof(std::begin(resp_str));
    pose.y = std::stof(delim1 + 1);
    pose.z = std::stof(delim2 + 1);

  } catch (std::exception const& e) {
    spdlog::error(e.what());
  }
}
