//
// Created by Admin on 7/03/2025.
//

#pragma once

#include "FrameGraph.h"

#include <set>
#include <unordered_map>

namespace My::FG {
class Compiler {
 public:
  struct Result {
    struct RsrcInfo {
      size_t first; // index in sortedPass
      size_t last;  // index in sortedPass

      std::vector<size_t> readers;
      size_t writer;
    };

    struct PassInfo {
      std::vector<size_t> constructRsrcs;
      std::vector<size_t> destructRsrcs;
    };

    struct PassGraph {
      void Clear() { adjList.clear(); }

      std::tuple<bool, std::vector<size_t>> TopoSort() const;
      std::unordered_map<size_t, std::set<size_t>> adjList;
    };

    std::unordered_map<size_t, RsrcInfo> rsrc2info;
    PassGraph passgraph;
    std::vector<size_t> sortedPasses;
    std::unordered_map<size_t, PassInfo> idx2info;  // pass index to pass info
  };

  std::tuple<bool, Result> Compile(const FrameGraph& fg);
};
}  // namespace My::FG
