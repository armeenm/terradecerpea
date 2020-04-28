#include <fmt/format.h>

#include <gpiod.hpp>
#include <polhemus.hpp>

#include "berrypicker/ml/rl_model.h"
#include "berrypicker/pressure.h"
#include <ilanta/control/pose.hpp>

int main(int argc, char** argv) {
  /* Argument Handling */
  if (argc != 2) {
    fmt::print(stderr, "Invalid argument count\n");
    fmt::print(stderr, "Usage: {} [arm-length]\n", argv[0]);
    return -1;
  }

  const auto model_dir = fmt::format("../models/actormodel{}", argv[1]);

  /* GPIO Test */
  for (const auto& chip : gpiod::make_chip_iter()) {
    fmt::print("{} [{}], Num. Lines: {}\n", chip.name(), chip.label(), chip.num_lines());
  }

  /* RL Model */
  auto rlmodel = RLModel(model_dir);

  auto input_pose = ilanta::PoseTL{0.0F, 30.0F, 0.5F};
  auto input_pressure = Pressure{0.0F, 30.0F};
  auto [opt_pressure, err] = rlmodel.predict(input_pose, input_pressure);

  fmt::print("Pressure: {}, {}; Error: {}", opt_pressure->bending, opt_pressure->rotating, err);
}
