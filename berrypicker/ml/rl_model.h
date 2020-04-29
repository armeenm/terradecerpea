#pragma once

#include "berrypicker/pressure.h"

#include <ilanta/control/pose.hpp>
#include <optional>
#include <string>
#include <string_view>
#include <torch/script.h>
#include <utility>

class RLModel {
public:
  [[nodiscard]] RLModel(std::string_view model_file);

  RLModel(RLModel const&) = default;
  RLModel(RLModel&&) noexcept = default;

  auto operator=(RLModel const&) -> RLModel& = default;
  auto operator=(RLModel&&) noexcept -> RLModel& = default;

  ~RLModel() = default;

  [[nodiscard]] auto model_file() const noexcept -> std::string_view;

  [[nodiscard]] auto predict(ilanta::PoseTL<float> const&, Pressure const&)
      -> std::pair<std::optional<Pressure>, float>;

private:
  std::string model_file_;
  torch::jit::script::Module module_;
};
