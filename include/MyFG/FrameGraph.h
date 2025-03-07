//
// Created by Admin on 7/03/2025.
//

#pragma once

#include "Pass.h"
#include "Resource.h"

namespace My::FG {
class FrameGraph {
 public:
  FrameGraph();
  ~FrameGraph();

  void AddPass(Pass pass) { passes.emplace_back(std::move(pass)); }

  const std::vector<Pass>& GetPasses() const noexcept { return passes; }

  void Compile();
  // void Execute();
 private:
  struct CompileResult;
  CompileResult* compileResult;
  std::vector<Pass> passes;
};
}  // namespace My::FG
