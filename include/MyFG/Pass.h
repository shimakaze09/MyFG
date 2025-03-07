//
// Created by Admin on 7/03/2025.
//

#pragma once

#include <functional>
#include <vector>

#include "Resource.h"

namespace My::FG {
class Pass {
 public:
  Pass(std::vector<ResourceDecs> inputs, std::vector<ResourceDecs> outputs,
       std::function<void()> func, std::string name)
      : inputs{std::move(inputs)},
        outputs{std::move(outputs)},
        func{std::move(func)},
        name{std::move(name)} {}

  void Execute() { func(); }

  const std::string& Name() const noexcept { return name; }

  const std::vector<ResourceDecs>& Inputs() const noexcept { return inputs; }

  const std::vector<ResourceDecs>& Outputs() const noexcept { return outputs; }

 private:
  std::vector<ResourceDecs> inputs;
  std::vector<ResourceDecs> outputs;
  std::function<void()> func;
  std::string name;
};
}  // namespace My::FG
