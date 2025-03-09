//
// Created by Admin on 9/03/2025.
//

#pragma once

#include "Rsrc.h"

#include "../core/core.h"

#include <functional>

namespace My::DX12::FG {
class RsrcMngr;

class Executor {
 public:
  Executor& RegisterPassFunc(size_t passNodeIdx,
                             std::function<void(const PassRsrcs&)> func) {
    passFuncs[passNodeIdx] = std::move(func);
    return *this;
  }

  void NewFrame() { passFuncs.clear(); }

  void Execute(const My::FG::Compiler::Result& crst, RsrcMngr& rsrcMngr);

 private:
  std::unordered_map<size_t, std::function<void(const PassRsrcs&)>> passFuncs;
};
}  // namespace My::DX12::FG
