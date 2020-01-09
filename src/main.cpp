#include <fmt/format.h>
#include <tensorflow/cc/saved_model/loader.h>
#include <tensorflow/cc/saved_model/tag_constants.h>

#include <gpiod.hpp>
#include <iostream>

namespace tf = tensorflow;

int main(int argc, char** argv) {
    /* Argument Handling */
    if (argc != 2) {
        std::cerr << "Invalid argument count\n";
        fmt::print(stderr, "Usage: {} [model-dir]\n", argv[0]);
        return -1;
    }

    const auto model_dir = argv[1];

    /* GPIO Test */
    for (const auto& chip : gpiod::make_chip_iter()) {
        fmt::print("{} [{}], Num. Lines: {}\n", chip.name(), chip.label(),
                   chip.num_lines());
    }

    /* Tensorflow RL Arm Control Model */
    tf::SavedModelBundleLite arm_model;
    auto sess_opts = tf::SessionOptions();
    auto run_opts = tf::RunOptions();

    auto status = tensorflow::LoadSavedModel(
        sess_opts, run_opts, model_dir, {tf::kSavedModelTagServe}, &arm_model);
    if (!status.ok()) {
        std::cerr << "Failed to load model: " << status << '\n';
        return -1;
    }

    /* Start */
    // auto arm = Arm(arm_model);
    // std::cout << "Ready\n";
}
