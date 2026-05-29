#pragma once

#include <algorithm>
#include <cstddef>
#include <vector>

#include "PQ_ComplHeap_macro.h"

namespace ods {

template <class T, class Compare>
std::size_t complHeapPercolateDown(std::vector<T>& a, std::size_t n, std::size_t i, Compare comp) {
  
  // Se reemplazó "pqInHeap(pqLeftChild(i), n)" por la nueva función "pqHasLeftChild(i, n)"
  while (pqHasLeftChild(i, n)) { 
    std::size_t c = pqLeftChild(i);
    
    // Se eliminó la variable temporal "r" que guardaba el hijo derecho.
    
    // Se reemplazó "pqInHeap(r, n)" por "pqHasRightChild(i, n)" y se usa "pqRightChild(i)" directo.
    if (pqHasRightChild(i, n) && comp(a[c], a[pqRightChild(i)])) {
      c = pqRightChild(i); // CAMBIO: Antes era "c = r;"
    }
    
    if (!comp(a[i], a[c])) {
      break;
    }
    
    std::swap(a[i], a[c]);
    i = c;
  }
  return i;
}

}  // namespace ods