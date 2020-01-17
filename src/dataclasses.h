#pragma once

struct Pose {
  float x = 0.0f;
  float y = 0.0f;
  float z = 0.0f;

  auto operator+(Pose const& other) const noexcept -> Pose { return Pose{x + other.x, y + other.y, z + other.y}; }
  auto operator-(Pose const& other) const noexcept -> Pose { return Pose{x - other.x, y - other.y, z - other.z}; }
};

struct Pressure {
  float bending = 0.0f;
  float rotation = 0.0f;
};
