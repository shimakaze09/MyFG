//
// Created by Admin on 7/03/2025.
//

#pragma once

#include <string>

namespace My::MyFG {
class ResourceNode {
 public:
  ResourceNode(std::string name) : name{std::move(name)} {}

  const std::string& Name() const noexcept { return name; }

 private:
  std::string name;
};
}  // namespace My::MyFG
