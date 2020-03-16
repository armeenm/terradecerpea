#pragma once

namespace ilanta {
namespace io {

enum class LogicLevel : int { LOW, HIGH };

auto operator!(LogicLevel& orig) -> LogicLevel& {
  return (orig == LogicLevel::LOW) ? LogicLevel::HIGH : LogicLevel::LOW;
}

} // namespace io
} // namespace ilanta
