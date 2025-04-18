#pragma once

#include <string>
#include <vector>

namespace Smkz::MyFG {
class PassNode {
 public:
  PassNode(std::string name, std::vector<size_t> inputs,
           std::vector<size_t> outputs)
      : name{std::move(name)},
        inputs{std::move(inputs)},
        outputs{std::move(outputs)} {}

  const std::string& Name() const noexcept { return name; }
  const std::vector<size_t>& Inputs() const noexcept { return inputs; }
  const std::vector<size_t>& Outputs() const noexcept { return outputs; }

 private:
  std::string name;
  std::vector<size_t> inputs;
  std::vector<size_t> outputs;
};
}  // namespace Smkz::MyFG
