#pragma once

#include <tensorflow/cc/saved_model/loader.h>
#include <tensorflow/cc/saved_model/tag_constants.h>

#include <cstdint>
#include <polhemus.hpp>
#include <string>
#include <string_view>

class RLModel {
  namespace plhm = polhemus;
  namespace tf = tensorflow;

  RLModel(std::string_view model_dir, std::uint8_t input_size = 5, tf::DataType dtype);

  RLModel(RLModel const&) = delete;
  RLModel(RLModel&&) noexcept = default;

  auto operator=(RLModel const&) -> RLModel& = delete;
  auto operator=(RLModel&&) noexcept -> RLModel& = default;

  ~RLModel();

  [[nodiscard]] auto predict(tf::Tensor const& input) -> tf::Tensor;

private:
  std::string model_dir_;
  tf::SessionOptions sess_opts_ = tf::SessionOptions();
  tf::RunOptions run_opts_ = tf::RunOptions();
  tf::SavedModelBundleLite model_;
  tf::SignatureDef const sig_def_ = model_.GetSignatures().at(tf::kDefaultServingSignatureDefKey);
  tf::String const input_name_ = sig_def_.inputs().at("input").name();
  tf::TensorShape const input_shape_;
  tf::Tensor const input_tensor_;
};
