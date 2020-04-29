#include "berrypicker/io/compressor.h"
#include "berrypicker/const.h"

#include <ilanta/io/gpiod.hpp>
#include <spdlog/spdlog.h>

Compressor::Compressor(gpiod::line&& enable_line, LogicLevel active_state)
    : enable_line_{std::move(enable_line)} {
  spdlog::info("Constructing Compressor");

  ilanta::request_output(enable_line_, consumer_name, active_state == LogicLevel::LOW);
}

auto Compressor::enabled() const noexcept -> bool { return enabled_; }

auto Compressor::set(bool const enable) noexcept -> void {
  enable_line_.set_value(static_cast<int>(enable));
  enabled_ = enable;
}

auto Compressor::enable() noexcept -> void { set(true); }
auto Compressor::disable() noexcept -> void { set(false); }
