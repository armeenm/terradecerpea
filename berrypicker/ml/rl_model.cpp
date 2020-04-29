#include "berrypicker/ml/rl_model.h"

#include <iostream>

RLModel::RLModel(std::string_view model_file) : model_file_{model_file} {
  module_ = torch::jit::load(model_file_.c_str());
}

auto RLModel::predict(ilanta::PoseTL<float> const& pose, Pressure const& pressure)
    -> std::pair<std::optional<Pressure>, float> {

  auto input = std::vector<torch::jit::IValue>{torch::empty({1, 5})};

  input[0] = pose.x();
  input[1] = pose.y();
  input[2] = pose.z();
  input[3] = pressure.bending;
  input[4] = pressure.rotating;

  auto output = module_.forward(input).toTensor();

  std::cout << output << '\n';

  // TODO: what is this float??
  return {Pressure{output[0].item<float>(), output[1].item<float>()}, 0.0f};
}
