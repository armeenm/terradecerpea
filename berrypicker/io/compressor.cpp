#include "berrypicker/io/compressor.h"

#include "berrypicker/constants.h"
#include "ilanta/io/gpiod.h"

#include <exception>
#include <fmt/core.h>
#include <spdlog/spdlog.h>

Compressor::Compressor(gpiod::line&& enable_line, LogicLevel active_state)
    : enable_line_(std::move(enable_line)) {
  spdlog::info("Constructing Compressor");

  auto ILANTA_GPIO_OUTPUT_THROW(enable_line, active_state == LogicLevel::LOW);
}

auto Compressor::enabled() const noexcept -> bool { return enabled_; }

auto Compressor::set(bool enable) noexcept -> void {
  enable_line_.set_value(static_cast<int>(enable));
}
