#pragma once

#include <algorithm>
#include <cstddef>
#include <vector>

#include "PQ_ComplHeap_macro.h"

namespace ods {

template <class T, class Compare>
std::size_t complHeapPercolateDown(std::vector<T>& a, std::size_t n, std::size_t i, Compare comp) {
  // Bloque 2: Uso de funciones auxiliares para simplificar percolateDown
  while (pqHasLeftChild(i, n)) {
    std::size_t c = pqLeftChild(i);
    
    if (pqHasRightChild(i, n) && comp(a[c], a[pqRightChild(i)])) {
      c = pqRightChild(i);
    }
    
    if (!comp(a[i], a[c])) {
      break;
    }
    
    std::swap(a[i], a[c]);
    i = c;
  }
  return i;
}

// Bloque 4 : Función que cuenta los intercambios al bajar
template <class T, class Compare>
std::size_t complHeapPercolateDownCount(std::vector<T>& a, std::size_t n, std::size_t i, Compare comp) {
  std::size_t swaps = 0;
  while (pqHasLeftChild(i, n)) {
    std::size_t c = pqLeftChild(i);
    
    // Elegir el hijo dominante (el mayor en un max-heap)
    if (pqHasRightChild(i, n) && comp(a[c], a[pqRightChild(i)])) {
      c = pqRightChild(i);
    }
    
    if (!comp(a[i], a[c])) {
      break;
    }
    
    std::swap(a[i], a[c]);
    swaps++;
    i = c;
  }
  return swaps;
}

}  // namespace ods