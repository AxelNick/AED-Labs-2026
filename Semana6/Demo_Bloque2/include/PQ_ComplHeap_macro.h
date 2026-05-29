#pragma once

#include <cstddef>

namespace ods {

inline constexpr std::size_t pqParent(std::size_t i) noexcept { return (i - 1) / 2; }
inline constexpr std::size_t pqLeftChild(std::size_t i) noexcept { return 2 * i + 1; }
inline constexpr std::size_t pqRightChild(std::size_t i) noexcept { return 2 * i + 2; }
inline constexpr bool pqInHeap(std::size_t i, std::size_t n) noexcept { return i < n; }
inline constexpr bool pqHasParent(std::size_t i) noexcept { return i > 0; }
inline constexpr std::size_t pqLastInternal(std::size_t n) noexcept {
  return n == 0 ? 0 : pqParent(n - 1);
}

// Funciones auxiliares agregadas
inline constexpr bool pqHasLeftChild(std::size_t i, std::size_t n) noexcept {
  return pqLeftChild(i) < n;
}

inline constexpr bool pqHasRightChild(std::size_t i, std::size_t n) noexcept {
  return pqRightChild(i) < n;
}

inline constexpr bool pqIsLeaf(std::size_t i, std::size_t n) noexcept {
  return !pqHasLeftChild(i, n);
}

inline constexpr bool pqIsInternal(std::size_t i, std::size_t n) noexcept {
  return pqHasLeftChild(i, n);
}

}  // namespace ods