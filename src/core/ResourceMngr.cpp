//
// Created by Admin on 7/03/2025.
//

#include <MyFG/ResourceMngr.h>

using namespace My;
using namespace My::FG;
using namespace std;

Resource ResourceMngr::Request(const void* type, string name) {
  auto& ptrs = frees[type];

  void* ptr;

  if (ptrs.empty())
    ptr = Create(type);
  else {
    ptr = ptrs.back();
    ptrs.pop_back();
  }

  return {type, ptr, std::move(name)};
}

void ResourceMngr::Recycle(const Resource& resource) {
  frees[resource.GetType()].push_back(resource.GetPtr());
}
