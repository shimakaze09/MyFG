//
// Created by Admin on 9/03/2025.
//

#pragma once

#include <MyDX12/MyDX12.h>

#include <functional>
#include <unordered_map>
#include <variant>

namespace My::detail::DX12::FG::Rsrc_ {
template <typename T>
void hash_combine(size_t& s, const T& v) {
  std::hash<T> h;
  s ^= h(v) + 0x9e3779b9 + (s << 6) + (s >> 2);
}

template <typename T>
size_t hash_of(const T& v) {
  using U = std::conditional_t<
      alignof(T) == 1, std::uint8_t,
      std::conditional_t<
          alignof(T) == 2, std::uint16_t,
          std::conditional_t<alignof(T) == 4, std::uint32_t, std::uint64_t>>>;

  size_t rst = 0;
  for (size_t i = 0; i < sizeof(T) / sizeof(U); i++)
    hash_combine(rst, reinterpret_cast<const U*>(&v)[i]);

  return rst;
}

template <typename T>
struct always_false : std::false_type {};

template <typename T>
static constexpr bool always_false_v = always_false<T>::value;

template <typename T>
bool bitwise_equal(const T& lhs, const T& rhs) noexcept {
  using U = std::conditional_t<
      alignof(T) == 1, std::uint8_t,
      std::conditional_t<
          alignof(T) == 2, std::uint16_t,
          std::conditional_t<alignof(T) == 4, std::uint32_t, std::uint64_t>>>;

  const U* u_lhs = reinterpret_cast<const U*>(&lhs);
  const U* u_rhs = reinterpret_cast<const U*>(&rhs);
  for (size_t i = 0; i < sizeof(T) / sizeof(U); i++, u_lhs++, u_rhs++) {
    if (*u_lhs != *u_rhs)
      return false;
  }

  return true;
}
}  // namespace My::detail::DX12::FG::Rsrc_

namespace My::DX12::FG {
using Rsrc = ID3D12Resource;
using RsrcPtr = ComPtr<Rsrc>;
using RsrcState = D3D12_RESOURCE_STATES;

struct RsrcType {
  D3D12_CLEAR_VALUE clearValue;
  D3D12_RESOURCE_DESC desc;

  bool operator==(const My::DX12::FG::RsrcType& rhs) const noexcept {
    return My::detail::DX12::FG::Rsrc_::bitwise_equal(*this, rhs);
  }

  static RsrcType RT2D(DXGI_FORMAT format, UINT64 width, UINT height,
                       const float* color) {
    return {CD3DX12_CLEAR_VALUE{format, color},
            My::DX12::Desc::RSRC::RT2D(width, height, format)};
  }
};

struct RsrcImplDesc_SRV_NULL {};

struct RsrcImplDesc_UAV_NULL {};

struct RsrcImplDesc_RTV_Null {};

struct RsrcImplDesc_DSV_Null {};

using RsrcImplDesc = std::variant<
    D3D12_CONSTANT_BUFFER_VIEW_DESC, D3D12_SHADER_RESOURCE_VIEW_DESC,
    D3D12_UNORDERED_ACCESS_VIEW_DESC, D3D12_RENDER_TARGET_VIEW_DESC,
    D3D12_DEPTH_STENCIL_VIEW_DESC, RsrcImplDesc_SRV_NULL, RsrcImplDesc_UAV_NULL,
    RsrcImplDesc_RTV_Null, RsrcImplDesc_DSV_Null>;

struct RsrcImpl {
  ID3D12Resource* resource;
  D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle;
  D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle;
};

using PassRsrcs = std::unordered_map<size_t, RsrcImpl>;

struct SRsrcView {
  Rsrc* pRsrc;
  RsrcState state;
};
}  // namespace My::DX12::FG

inline bool operator==(const D3D12_CONSTANT_BUFFER_VIEW_DESC& lhs,
                       const D3D12_CONSTANT_BUFFER_VIEW_DESC& rhs) noexcept {
  return My::detail::DX12::FG::Rsrc_::bitwise_equal(lhs, rhs);
}

inline bool operator==(const D3D12_SHADER_RESOURCE_VIEW_DESC& lhs,
                       const D3D12_SHADER_RESOURCE_VIEW_DESC& rhs) noexcept {
  return My::detail::DX12::FG::Rsrc_::bitwise_equal(lhs, rhs);
}

inline bool operator==(const D3D12_UNORDERED_ACCESS_VIEW_DESC& lhs,
                       const D3D12_UNORDERED_ACCESS_VIEW_DESC& rhs) noexcept {
  return My::detail::DX12::FG::Rsrc_::bitwise_equal(lhs, rhs);
}

inline bool operator==(const D3D12_RENDER_TARGET_VIEW_DESC& lhs,
                       const D3D12_RENDER_TARGET_VIEW_DESC& rhs) noexcept {
  return My::detail::DX12::FG::Rsrc_::bitwise_equal(lhs, rhs);
}

inline bool operator==(const D3D12_DEPTH_STENCIL_VIEW_DESC& lhs,
                       const D3D12_DEPTH_STENCIL_VIEW_DESC& rhs) noexcept {
  return My::detail::DX12::FG::Rsrc_::bitwise_equal(lhs, rhs);
}

namespace std {
template <>
struct hash<My::DX12::FG::RsrcType> {
  size_t operator()(const My::DX12::FG::RsrcType& type) const noexcept {
    return My::detail::DX12::FG::Rsrc_::hash_of(type);
  }
};

template <>
struct hash<D3D12_CONSTANT_BUFFER_VIEW_DESC> {
  size_t operator()(
      const D3D12_CONSTANT_BUFFER_VIEW_DESC& desc) const noexcept {
    return My::detail::DX12::FG::Rsrc_::hash_of(desc);
  }
};

template <>
struct hash<D3D12_SHADER_RESOURCE_VIEW_DESC> {
  size_t operator()(
      const D3D12_SHADER_RESOURCE_VIEW_DESC& desc) const noexcept {
    return My::detail::DX12::FG::Rsrc_::hash_of(desc);
  }
};

template <>
struct hash<D3D12_UNORDERED_ACCESS_VIEW_DESC> {
  size_t operator()(
      const D3D12_UNORDERED_ACCESS_VIEW_DESC& desc) const noexcept {
    return My::detail::DX12::FG::Rsrc_::hash_of(desc);
  }
};

template <>
struct hash<D3D12_RENDER_TARGET_VIEW_DESC> {
  size_t operator()(const D3D12_RENDER_TARGET_VIEW_DESC& desc) const noexcept {
    return My::detail::DX12::FG::Rsrc_::hash_of(desc);
  }
};

template <>
struct hash<D3D12_DEPTH_STENCIL_VIEW_DESC> {
  size_t operator()(const D3D12_DEPTH_STENCIL_VIEW_DESC& desc) const noexcept {
    return My::detail::DX12::FG::Rsrc_::hash_of(desc);
  }
};
}  // namespace std
