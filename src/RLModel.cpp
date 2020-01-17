#include "RLModel.h"

#include <exception>
#include <tensorflow/cc/saved_model/constants.h>
#include <tensorflow/core/lib/core/status.h>

namespace tf = tensorflow;

RLModel::RLModel(std::string_view model_dir, std::uint8_t const input_size, tf::DataType const dtype)
    : model_dir_(model_dir), input_shape_(tf::TensorShape({1, input_size})),
      input_tensor_(tf::Tensor(dtype, input_shape_)) {

  auto status = tf::LoadSavedModel(sess_opts_, run_opts_, model_dir_, {tf::kSavedModelTagServe}, &model_);
  if (!status.ok()) {
    throw std::runtime_error(status.ToString());
  }
}
