//#include "berrypicker/ml/rl_model.h"
#include "pressure.h"

#include <algorithm>
#include <gpiod.hpp>
#include <ilanta/control/pose.hpp>
#include <ilanta/hal/hw/pca9685.hpp>
#include <polhemus.hpp>
#include <range/v3/algorithm/find.hpp>
#include <range/v3/view/transform.hpp>
#include <spdlog/spdlog.h>

#ifdef NDEBUG
auto constexpr inline is_debug = false;
#else
auto constexpr inline is_debug = true;
#endif

auto main(int const argc, char const* const* const argv) -> int {
  using namespace std::literals;
  using namespace ranges;

  spdlog::set_level(is_debug ? spdlog::level::debug : spdlog::level::info);
  spdlog::set_level(spdlog::level::debug);

  // Argument handling //
  if (argc != 2) {
    spdlog::error("Invalid argument count");
    spdlog::error("Usage: {} [arm-length]", argv[0]);
    return -1;
  }

  spdlog::debug("Testing");

  auto constexpr i2c_path = "/dev/i2c-1"sv;

  auto const i2c_infos = ilanta::I2C::find_buses();
  auto i2c_paths = i2c_infos | views::transform([](ilanta::I2C::Info info) {
    return info.path.string();
  });

  auto const found = ranges::find(i2c_paths, i2c_path);

  if (found == ranges::end(i2c_paths)) {
    spdlog::error("Failed to find I2C bus");
    return -1;
  } else {
    spdlog::info("Successfully found I2C bus");
  }

  auto i2c = ilanta::I2C{i2c_path};

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
