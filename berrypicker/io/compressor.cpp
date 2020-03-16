#include "berrypicker/io/compressor.h"

#include <exception>
#include <fmt/core.h>
#include <spdlog/spdlog.h>

Compressor::Compressor(gpiod::line enable_line, ilanta::io::LogicLevel active_state)
    : enable_line_(std::move(enable_line)), active_state_(active_state) {
  spdlog::info("Constructing Compressor with enable line {}", enable_line_.offset());

  if (enable_line_.is_used())
    spdlog::warn("Line {} is in use by another process: {}", enable_line_.offset(),
                 enable_line_.consumer());

  enable_line_.request(DIRECTION_OUTPUT, !conf_.active_state);

  if (!enable_line_.is_requested()) {
    auto const err = fmt::format("Failed to request line {}", enable_line_.offset());
    spdlog::error(err);
    throw std::runtime_error(err);
  }
}

auto Compressor::active_state() const noexcept -> ilanta::io::LogicLevel { return active_state_; }
auto Compressor::enabled() const noexcept -> bool { return enabled_; }

auto Compressor::set(bool enable) noexcept -> void {
  enable_line_.set_value(enable ? active_state_ : !active_state_);
}
