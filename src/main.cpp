//#include "berrypicker/ml/rl_model.h"
#include "pressure.h"

#include <algorithm>
#include <filesystem>
#include <string>
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

  auto constexpr bus_path = "/dev/i2c-0"sv;
  auto const bus_paths = ilanta::SMBus::find_buses();

  auto bus_strs =
      bus_paths | views::transform([](std::filesystem::path path) { return path.string(); });

  auto const found = ranges::find(bus_strs, bus_path);

  if (found == ranges::end(bus_strs)) {
    spdlog::error("Failed to find SMBus bus");
    return -1;
  } else
    spdlog::info("Successfully found SMBus bus");

  auto bus = ilanta::SMBus{bus_path};
  auto servo = ilanta::PCA9685{bus};

  auto err = servo.freq(50);
  if (err)
    spdlog::error("Failed to set frequency: {}", err.message());

  servo.duty_cycle(0, std::stoi(argv[1]));
  if (err)
    spdlog::error("Failed to set duty_cycle: {}", err.message());

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
