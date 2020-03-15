#include "berrypicker/io/position_sensor.h"

PositionSensor::PositionSensor(plhm::DevType dev_type)
    : sensor_(plhm::DevHandle(nullptr, dev_type)) {}

auto PositionSensor::pose() const noexcept -> PoseTL {}
