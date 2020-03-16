#pragma once

#include "berrypicker/ml/tf_model.h"
#include "berrypicker/pressure.h"
#include "ilanta/control/pose.h"

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

  [[nodiscard]] auto predict(ilanta::control::PoseTL const&, Pressure const&)
      -> std::pair<std::optional<Pressure>, float>;

private:
  TFModel model_;
};
