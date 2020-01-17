#pragma once

#include <tensorflow/cc/saved_model/constants.h>
#include <tensorflow/cc/saved_model/loader.h>

#include <polhemus.hpp>

class RLModel {
  namespace plhm = polhemus;
  namespace tf = tensorflow;

  RLModel(unsigned int input_size = 5, tf::DataType dt);

  RLModel(RLModel const&) = delete;
  RLModel(RLModel&&) noexcept = default;

  auto operator=(RLModel const&) -> RLModel& = delete;
  auto operator=(RLModel&&) noexcept -> RLModel& = default;

  [[nodiscard]] auto predict(tf::Tensor const& input) -> tf::Tensor;

private:
  tf::SessionOptions sess_opts_ = tf::SessionOptions();
  tf::RunOptions run_opts_ = tf::RunOptions();
  tf::SavedModelBundleLite model_;
  tf::SignatureDef const sig_def_ = model_.GetSignatures().at(tf::kSavedModelTagServe);
  tf::String const input_name_ = sig_def_.inputs().at("input").name();
  tf::TensorShape const input_shape_;
  tf::Tensor const input_tensor_;
};
