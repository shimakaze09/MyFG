//
// Created by Admin on 7/03/2025.
//

#include <MyFG/ResourceMngr.h>

using namespace My;
using namespace My::FG;
using namespace std;

Resource ResourceMngr::Request(const void* type, size_t state) {
  auto& ptrs = frees[type];

  void* ptr;

  if (ptrs.empty())
    ptr = Create(type, state);
  else {
    ptr = ptrs.back();
    ptrs.pop_back();
    Init(type, ptr, state);
  }

  return {type, ptr, state};
}

void ResourceMngr::Recycle(const Resource& resource) {
  frees[resource.type].push_back(resource.ptr);
}
