#pragma once

/**
 * Translational pose structure
 */
struct PoseTL {
  float x = 0.0f;
  float y = 0.0f;
  float z = 0.0f;

  auto operator+(Pose const& other) const noexcept -> Pose { return Pose{x + other.x, y + other.y, z + other.y}; }
  auto operator-(Pose const& other) const noexcept -> Pose { return Pose{x - other.x, y - other.y, z - other.z}; }
};
