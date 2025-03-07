//
// Created by Admin on 7/03/2025.
//

#pragma once

#include <unordered_map>

#include "Resource.h"

namespace My::FG {
class ResourceMngr {
 public:
  Resource Request(const void* type, std::string name);

  void Recycle(const Resource& resource);

 protected:
  virtual void* Create(const void* type) const = 0;

 private:
  std::unordered_map<const void*, std::vector<void*>> frees;
};
}  // namespace My::FG
