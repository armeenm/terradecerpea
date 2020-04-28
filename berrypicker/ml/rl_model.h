#pragma once

#include "berrypicker/pressure.h"
#include <ilanta/control/pose.hpp>
#include <ilanta/ml/tf_model.hpp>

#include <optional>
#include <utility>

class RLModel {
public:
  RLModel(std::string_view model_dir);

  RLModel(RLModel const&) = default;
  RLModel(RLModel&&) noexcept = default;

  auto operator=(RLModel const&) -> RLModel& = default;
  auto operator=(RLModel&&) noexcept -> RLModel& = default;

  ~RLModel() = default;

  [[nodiscard]] auto predict(ilanta::PoseTL<float> const&, Pressure const&)
      -> std::pair<std::optional<Pressure>, float>;

private:
  TFModel model_;
};
