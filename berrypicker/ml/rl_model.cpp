#include "berrypicker/ml/rl_model.h"

RLModel::RLModel(std::string_view model_dir) : model_(TFModel(model_dir)) {}

auto RLModel::predict(ilanta::PoseTL const& pose, Pressure const& pressure)
    -> std::pair<std::optional<Pressure>, float> {
  auto shape = tf::TensorShape({1, 5});
  auto input = tf::Tensor(tf::DT_FLOAT, shape);
  auto input_data = input.flat<float>().data();

  input_data[0] = pose.x;
  input_data[1] = pose.y;
  input_data[2] = pose.z;
  input_data[3] = pressure.bending;
  input_data[4] = pressure.rotating;

  auto output = model_.predict(input);
  auto output_data = output.flat<float>().data();
  auto output_pressure = Pressure{output_data[0], output_data[1]};

  return {output_pressure, 0.0f};
}
