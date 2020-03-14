#include "io/Relay.h"

#include <spdlog/spdlog.h>

Compressor::Compressor(Config conf) : enable_line_(std::move(conf.enable_line)) {
  spdlog::info("Constructing Compressor with enable line {}", enable_line_.offset());

  if (enable_line_.is_used())
    spdlog::warn("Line {} is in use by another process: {}", enable_line_.offset(), enable_line_.consumer());

  enable_line_.request(DIRECTION_OUTPUT, LogicLevel::);
}
