//
// Created by Admin on 7/03/2025.
//

#pragma once

#include "Pass.h"
#include "Resource.h"
#include "CompileResult.h"

namespace My::FG {
class FrameGraph {
 public:
  void AddPass(Pass pass) { passes.emplace_back(std::move(pass)); }

  const std::vector<Pass>& GetPasses() const noexcept { return passes; }

  const CompileResult& Compile();
  // void Execute();
 private:
  CompileResult compileResult;
  std::vector<Pass> passes;
};
}  // namespace My::FG
