//#include "berrypicker/ml/rl_model.h"
#include "pressure.h"

#include <algorithm>
#include <filesystem>
#include <ilanta/control/pose.hpp>
#include <ilanta/hal/hw/pca9685.hpp>
#include <ilanta/hal/hw/gpiod.hpp>
#include <polhemus.hpp>
#include <range/v3/algorithm/find.hpp>
#include <range/v3/view/transform.hpp>
#include <spdlog/spdlog.h>
#include <string>
#include <thread>
#include <chrono>

#ifdef NDEBUG
auto constexpr inline is_debug = false;
#else
auto constexpr inline is_debug = true;
#endif

auto main(int const argc, char const* const* const argv) -> int {
  using namespace std::literals;
  using namespace ranges;

  spdlog::set_level(is_debug ? spdlog::level::debug : spdlog::level::info);

  // Argument handling //
  if (argc != 2) {
    spdlog::error("Invalid argument count");
    spdlog::error("Usage: {} [arm-length]", argv[0]);
    return -1;
  }

  auto constexpr i2c_port = 0U;

  try {
    /*
    auto servo = ilanta::PCA9685{ilanta::i2c_path(i2c_port)};

    auto err = servo.freq(50);
    if (err)
      spdlog::error("Failed to set frequency: {}", err.message());

    err = servo.duty_cycle(0, std::stoi(argv[1]));
    if (err)
      spdlog::error("Failed to set duty_cycle: {}", err.message());
    */

    for (auto const& chip : gpiod::make_chip_iter())
      fmt::print("{} [{}], Num. Lines: {}\n", chip.name(), chip.label(), chip.num_lines());

    auto const chip = gpiod::chip{"tegra-gpio"};
    auto line = chip.get_line(78);
    line.request({"Terradecerpea", gpiod::line_request::DIRECTION_OUTPUT, 0}, 0);
    std::this_thread::sleep_for(1s);
    line.set_value(1);
    std::this_thread::sleep_for(1s);

  } catch (std::exception const& e) {
    spdlog::error("Exception thrown: {}", e.what());
  }

  /*
  auto const model_dir = fmt::format("models/actormodel{}", argv[1]);

  // GPIO Test //

  // RL Model //
  auto rlmodel = RLModel(model_dir);

  auto constexpr input_pose = ilanta::PoseTL{0.0F, 30.0F, 0.5F};
  auto constexpr input_pressure = Pressure{0.0F, 30.0F};
  auto [opt_pressure, err] = rlmodel.predict(input_pose, input_pressure);

  fmt::print("Pressure: {}, {}; Error: {}", opt_pressure->bending, opt_pressure->rotating, err);
  */
}
