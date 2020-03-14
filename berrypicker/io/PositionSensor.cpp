#include "berrypicker/io/PositionSensor.h"
#include "berrypicker/data.h"

PositionSensor::PositionSensor(plhm::DevType dev_type) : sensor_(plhm::DevHandle(nullptr, dev_type)) {}

auto PositionSensor::get() const noexcept -> Pose {}
