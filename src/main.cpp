#include <fmt/format.h>
#include <tensorflow/cc/saved_model/constants.h>
#include <tensorflow/cc/saved_model/loader.h>
#include <tensorflow/cc/saved_model/signature_constants.h>
#include <tensorflow/cc/saved_model/tag_constants.h>
#include <tensorflow/core/lib/core/status.h>

#include <gpiod.hpp>
#include <iostream>
#include <polhemus.hpp>
#include <vector>

namespace tf = tensorflow;

template <typename V> using tf_str_vec = std::vector<std::pair<tf::string, V>>;

using input_pairs = tf_str_vec<tf::Tensor>;

int main(int argc, char** argv) {
  /* Argument Handling */
  if (argc != 2) {
    std::cerr << "Invalid argument count\n";
    fmt::print(stderr, "Usage: {} [arm-length]\n", argv[0]);
    return -1;
  }

  const auto model_dir = fmt::format("../models/actormodel{}", argv[1]);

  /* GPIO Test */
  for (const auto& chip : gpiod::make_chip_iter()) {
    fmt::print("{} [{}], Num. Lines: {}\n", chip.name(), chip.label(), chip.num_lines());
  }

  /* Tensorflow RL Arm Control Model */
  tf::SavedModelBundleLite arm_model;
  auto sess_opts = tf::SessionOptions();
  auto run_opts = tf::RunOptions();

  auto status = tensorflow::LoadSavedModel(sess_opts, run_opts, model_dir, {tf::kSavedModelTagServe}, &arm_model);
  if (!status.ok()) {
    std::cerr << "Failed to load model: " << status << '\n';
    return -1;
  }

  auto* sess = arm_model.GetSession();
  auto sig = arm_model.GetSignatures().at(tf::kDefaultServingSignatureDefKey);

  auto input_name = sig.inputs().at("input").name();
  auto input_shape = tf::TensorShape({1, 5});
  auto input_tensor = tf::Tensor(tf::DT_FLOAT, input_shape);
  auto input_data = input_tensor.flat<float>().data();
  // Dummy data, for now
  for (int i = 0; i < 5; i++) {
    input_data[i] = 1.0;
  }
  auto input = input_pairs({{input_name, input_tensor}});

  auto output_name = sig.outputs().at("output").name();
  auto output = std::vector<tf::Tensor>();

  status = sess->Run(input, {output_name}, {}, &output);
  if (!status.ok()) {
    std::cout << "Failed to infer: " << status.ToString() << '\n';
    return -1;
  }

  std::cout << "Output: " << output[0].DebugString() << '\n';
}
