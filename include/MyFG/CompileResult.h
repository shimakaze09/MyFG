//
// Created by Admin on 7/03/2025.
//

#pragma once

#include <set>
#include <unordered_map>
#include <vector>
#include <string>

namespace My::FG {
struct CompileResult {
  struct Info {
    // first == writer
    // size_t first; // index in sortedPass
    size_t last;  // index in sortedPass

    std::vector<size_t> readers;
    size_t writer;
  };

  struct PassGraph {
    void Clear() { adjList.clear(); }

    std::tuple<bool, std::vector<size_t>> TopoSort() const;
    std::unordered_map<size_t, std::set<size_t>> adjList;
  };

  void Clear();

  std::unordered_map<std::string, Info> resource2info;
  PassGraph passgraph;
  std::vector<size_t> sortedPasses;
};
}  // namespace My::FG
