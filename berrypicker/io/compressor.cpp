#include "berrypicker/io/compressor.h"
#include "ilanta/util/generics.h"

#include <exception>
#include <fmt/core.h>
#include <spdlog/spdlog.h>

Compressor::Compressor(gpiod::line enable_line, LogicLevel active_state)
    : enable_line_(std::move(enable_line)) {
  spdlog::info("Constructing Compressor with enable line {}", enable_line_.offset());

  if (enable_line_.is_used())
    spdlog::warn("Line {} is in use by another process: {}", enable_line_.offset(),
                 enable_line_.consumer());

  enable_line_.request(
      {"Berrypicker", gpiod::line_request::DIRECTION_OUTPUT,
       (active_state == LogicLevel::LOW) ? gpiod::line_request::FLAG_ACTIVE_LOW : 0},
      0);

  if (!enable_line_.is_requested()) {
    auto const err = fmt::format("Failed to request line {}", enable_line_.offset());
    spdlog::error(err);
    throw std::runtime_error(err);
  }
}

auto Compressor::enabled() const noexcept -> bool { return enabled_; }

auto Compressor::set(bool enable) noexcept -> void {
  enable_line_.set_value(static_cast<int>(enable));
}
