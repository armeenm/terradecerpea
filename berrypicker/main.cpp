//#include "berrypicker/ml/rl_model.h"
#include "berrypicker/pressure.h"

#include <fmt/format.h>
#include <gpiod.hpp>
#include <ilanta/control/pose.hpp>
#include <ilanta/hal/hw/pca9685.hpp>
#include <polhemus.hpp>

int main(int const argc, char const* const* const argv) {
  /* Argument Handling */
  if (argc != 2) {
    fmt::print(stderr, "Invalid argument count\n");
    fmt::print(stderr, "Usage: {} [arm-length]\n", argv[0]);
    return -1;
  }

  auto i2c = ilanta::I2C{"/dev/i2c-1"};

  /*
  auto const model_dir = fmt::format("models/actormodel{}", argv[1]);

  // GPIO Test //
  for (auto const& chip : gpiod::make_chip_iter())
    fmt::print("{} [{}], Num. Lines: {}\n", chip.name(), chip.label(), chip.num_lines());

  // RL Model //
  auto rlmodel = RLModel(model_dir);

  auto constexpr input_pose = ilanta::PoseTL{0.0F, 30.0F, 0.5F};
  auto constexpr input_pressure = Pressure{0.0F, 30.0F};
  auto [opt_pressure, err] = rlmodel.predict(input_pose, input_pressure);

  fmt::print("Pressure: {}, {}; Error: {}", opt_pressure->bending, opt_pressure->rotating, err);
  */
}
