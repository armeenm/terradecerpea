#include <spdlog/spdlog.h>

namespace ilanta {

auto request_output(gpiod::line const& l, std::string_view consumer, bool invert = false,
                    int default_val = 0) -> bool {
  spdlog::info("Requesting line '{}' with offset {}", l.name(), l.offset());

  if (l.is_used())
    spdlog::warn("Line {} is in use by consumer '{}'", l.offset(), l.consumer());

  l.request({consumer, gpiod::line_request::DIRECTION_OUTPUT,
             invert ? gpiod::line_request::FLAG_INACTIVE_LOW : 0});

  if (!l.requested()) {
    spdlog::error("Failed to request line {}", l.offset());
    return false;
  }

  spdlog::info("Successfully requested line {}", l.offset());
  return true;
}

} // namespace ilanta
