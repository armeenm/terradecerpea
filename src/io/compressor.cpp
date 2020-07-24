#include "io/compressor.h"

#include <ilanta/hal/hw/gpiod.hpp>

#include "const.h"

Compressor::Compressor(gpiod::line const& enable_line, LogicLevel active_state)
    : enable_line_{std::move(enable_line)} {
  ilanta::request_output(enable_line_, consumer_name, active_state == LogicLevel::Low);
}

auto Compressor::enabled() const noexcept -> bool { return enabled_; }

auto Compressor::set(bool const enable) noexcept -> void {
  enable_line_.set_value(static_cast<int>(enable));
  enabled_ = enable;
}

auto Compressor::enable() noexcept -> void { set(true); }
auto Compressor::disable() noexcept -> void { set(false); }
