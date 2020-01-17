#pragma once

#include "TFModel.h"
#include "dataclasses.h"

#include <optional>
#include <utility>

class RLModel {
public:
  RLModel(std::string_view model_dir);

  RLModel(RLModel const&) = default;
  RLModel(RLModel&&) noexcept = default;

  auto operator=(RLModel const&) -> RLModel& = default;
  auto operator=(RLModel &&) -> RLModel& = default;

  ~RLModel() = default;

  [[nodiscard]] auto predict(Pose const&, Pressure const&) -> std::pair<std::optional<Pressure>, float>;

private:
  TFModel model_;
};
