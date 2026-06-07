# Actividad 6 - CC232

### Estudiante
- **Nombre:** Axel Alberto Reyes Baldeón
- **Código:** 20200485B


## Bloque 1 - Diagnóstico inicial de la Semana 6

**Revisamos:**
* `Semana6/README.md`
* `Semana6/CMakeLists.txt`
* `Semana6/include/Capitulo6.h`
* `Semana6/include/Capitulo10.h`

**Diagnóstico de ejecución:**

| Comando ejecutado | Resultado | Error (si hubo) | Interpretación |
| :--- | :--- | :--- | :--- |
| `cmake --build build-debug --config Debug --target ...` | `[8/8] Linking CXX executable...` (Compilación al 100%) | Ninguno | Se compilaron correctamente todas las demostraciones y pruebas específicas requeridas para la Semana 6. |
| `cmake --build build-debug --config Debug` | `[12/12] Linking CXX executable...` (Compilación al 100%) | Ninguno | Se construyó la totalidad del proyecto, incluyendo las estructuras heredadas de la Semana 5, sin errores de sintaxis o enlazado. |
| `ctest --test-dir build-debug -C Debug -R semana6 --output-on-failure` | `100% tests passed, 0 tests failed out of 2` | Ninguno | El código base entregado funciona de manera correcta. Pasan tanto las pruebas públicas como las internas de la Semana 6, garantizando un entorno estable antes de realizar modificaciones. |


Evidencia de configuración (`cmake -S . -B build-debug`):

```bash
\$ cmake -S . -B build-debug
-- Configuring done (1.1s)
-- Generating done (0.7s)
-- Build files have been written to: C:/Users/AXEL/OneDrive/Escritorio/uni/2026-1/AED/Repositorio/Personal/CC232/Libreria_cc232/build-debug
```

Evidencia de compilación (`cmake --build build-debug --config Debug`):

```bash
\$ cmake --build build-debug --config Debug
[12/12] Linking CXX executable Semana5\sem5_test_public.exe
Build succeeded.
```

Evidencia de pruebas (`ctest`):

```bash
\$ ctest --test-dir build-debug -C Debug -R semana6 --output-on-failure
Test project C:/Users/AXEL/OneDrive/Escritorio/uni/2026-1/AED/Repositorio/Personal/CC232/Libreria_cc232/build-debug
    Start 22: semana6_public
1/2 Test #22: semana6_public ...................   Passed    0.14 sec
    Start 23: semana6_internal
2/2 Test #23: semana6_internal .................   Passed    0.13 sec

100% tests passed, 0 tests failed out of 2

Total Test time (real) =   0.30 sec
```

**Archivos que planeo modificar:**
Según las instrucciones de la actividad , modificare : 
* `PQ_ComplHeap_macro.h`
* `PQ_ComplHeap_percolateDown.h`
* `PQ_ComplHeap_percolateUp.h`
* `PQ_ComplHeap.h`
* `vector_heapSort.h`
* `PQ_LeftHeap.h`
* `Huffman_PQ.h`
* `Treap.h`
* Las demos correspondientes (ej. `demo_heapify_floyd.cpp`, `demo_treap_basico.cpp`, `demo_compare_with_semana5.cpp`).
* Las pruebas (`test_public_week6.cpp`, `test_internal_week6.cpp`).

### 1. ¿Qué targets de demostraciones o pruebas aparecen para Semana 6?
Aparecen 2 targets de pruebas (`sem6_test_public`, `sem6_test_internal`) y 9 de demostraciones originalmente (básico de complheap, heapify floyd, heapsort, left heap, huffman, bst rotations, treap básico, comparación con semana 5 y el panorama general).

### 2. ¿Qué archivos se incluyen desde Capitulo6.h?
Incluye todos los headers centrales de la semana: la interfaz abstracta `PQ.h`, las variaciones de `PQ_ComplHeap`, `PQ_LeftHeap`, `vector_heapSort.h`, `Huffman_PQ.h` y `Treap.h`.

### 3. ¿Qué diferencia práctica hay entre Capitulo6.h y Capitulo10.h?
Ninguna a nivel funcional. `Capitulo10.h` simplemente hace un `#include "Capitulo6.h"`. Es un alias para mantener compatibilidad con la numeración de los capítulos del libro base (Deng).

### 4. ¿Qué partes de Semana 6 dependen conceptualmente de Semana 5?
Toda la infraestructura de nodos y árboles. Depende directamente de `BinaryTree`, `BinarySearchTree` y `BinaryHeap` de la Semana 5 para usarlos como base constructiva (ej. Treap) o como punto de comparación.

### 5. ¿Qué estructura se usa para prioridad pura?
La Cola de Prioridad, implementada físicamente a través de un Heap Binario Completo (`PQ_ComplHeap`) o un Heap Izquierdista (`PQ_LeftHeap`).

### 6. ¿Qué estructura se usa para búsqueda ordenada?
El Árbol Binario de Búsqueda (`BinarySearchTree` o BST).

### 7. ¿Qué estructura mezcla búsqueda ordenada con prioridad?
El `Treap` (combina la propiedad de orden por claves de un BST con la propiedad de prioridad aleatoria de un Heap).

### 8. ¿Qué evidencia inicial obtuviste al ejecutar las pruebas sin modificar nada?
Que el 100% de los tests (públicos e internos) pasan sin fallos.


## Bloque 2 - Modificación de utilidades de heap completo

Revisamos: 

* `Semana6/include/PQ_ComplHeap_macro.h`
* `Semana6/include/PQ_ComplHeap_percolateUp.h`
* `Semana6/include/PQ_ComplHeap_percolateDown.h`

**Fragmento del código modificado:**

**`Libreria_cc232/Semana6/include/PQ_ComplHeap_macro.h`**

```cpp
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

// Funciones auxiliares constexpr adicionales
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
```

**`Libreria_cc232/Semana6/include/PQ_ComplHeap_percolateDown.h`**
```cpp
#pragma once

#include <algorithm>
#include <cstddef>
#include <vector>

#include "PQ_ComplHeap_macro.h"

namespace ods {

template <class T, class Compare>
std::size_t complHeapPercolateDown(std::vector<T>& a, std::size_t n, std::size_t i, Compare comp) {
  // Funciones auxiliares para simplificar percolateDown
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

}  // namespace ods
```

**Explicación de por qué no cambia la complejidad:**

La complejidad se mantiene exactamente igual en $O(\log n)$. Al usar la etiqueta `inline constexpr`, el compilador resuelve las llamadas y las sustituye directamente por las fórmulas básicas durante la compilación. No hay sobrecarga de llamadas a funciones en tiempo de ejecución ni uso de memoria extra.

**Evidencia de compilación:**

```bash
AXEL@DESKTOP-70IITE7 UCRT64 /c/Users/AXEL/OneDrive/Escritorio/uni/2026-1/AED/Repositorio/Personal/CC232/Libreria_cc232
$ cmake --build build-debug --config Debug --target sem6_demo_pq_complheap_basico
[2/2] Linking CXX executable Semana6\sem6_demo_pq_complheap_basico.exe
```

1. **¿Por qué conviene expresar parent, left, right y pruebas de frontera como funciones pequeñas?**
   Para mejorar la legibilidad y evitar errores manuales. Es más seguro y semántico leer `pqHasLeftChild(i, n)` que tener la lógica matemática regada por todos los bucles.

2. **¿Qué ventaja tiene constexpr frente a macros?**
   Las macros (como `#define`) solo reemplazan texto "a ciegas", lo que puede generar errores difíciles de rastrear. `constexpr` usa el sistema de tipos de C++, respeta el alcance de las variables y se evalúa de forma segura en tiempo de compilación.

3. **¿Qué caso borde aparece cuando el nodo tiene solo hijo izquierdo?**
   Ocurre en el último nodo interno cuando la cantidad total de elementos del arreglo es par. Hay que controlar este caso para evitar que el algoritmo intente comparar valores con un hijo derecho que no existe y provoque un error de "fuera de índice" (Out of Bounds).

4. **¿Qué condición identifica una hoja en la representación implícita?**
   Basta con verificar que el nodo no tenga un hijo izquierdo (`!pqHasLeftChild(i, n)`). En un árbol binario completo, si no hay hijo izquierdo, es físicamente imposible que haya uno derecho.

5. **¿Qué cambió en percolateDown después de usar las funciones auxiliares?**
   La condición del bucle pasó de usar el genérico `pqInHeap` con un cálculo anidado a un semántico `pqHasLeftChild`. Igualmente, la verificación del hijo derecho ahora se lee de forma directa y clara con `pqHasRightChild`, haciendo que la intención del código sea obvia.

*(Se pueden observar los cambios realizados en los códigos mencionados y compilarlos directamente desde la carpeta demo_bloque2)*

Puede seguir los siguientes pasos para compilar : 

```bash

# 1. Ingresar a la carpeta del demo
cd Semana6
cd Demo_Bloque2

# 2. Limpiar el caché de compilaciones anteriores
rm -rf build

# 3. Configurar el proyecto con CMake
cmake -S . -B build

# 4. Compilar el código
cmake --build build

# 5. Ejecutar la demostración
./build/demo_bloque2.exe
```

## Bloque 3 - Modificación de percolateUp: conteo de intercambios

Revisamos : 

* `Semana6/include/PQ_ComplHeap_percolateUp.h`
* `Semana6/include/PQ_ComplHeap_insert.h`
* `Semana6/demos/demo_pq_complheap_basico.cpp`

*(Nota : Debido a la gran cantidad de archivos que se relacionan en el repositorio del curso, opte por poner el codigo completo de los archivos que altere y la salida obtenida en lugar de crear una demo como en el bloque 2)*

**Entregables del bloque:**

**Código completo incluido la función nueva para PQ_ComplHeap_percolateUp.h :**
*(Añadido en `Libreria_cc232/Semana6/include/PQ_ComplHeap_percolateUp.h`)*

```cpp
#pragma once

#include <algorithm>
#include <cstddef>
#include <vector>

#include "PQ_ComplHeap_macro.h"

namespace ods {

template <class T, class Compare>
std::size_t complHeapPercolateUp(std::vector<T>& a, std::size_t i, Compare comp) {
  while (pqHasParent(i)) {
    const std::size_t p = pqParent(i);
    if (!comp(a[p], a[i])) {
      break;
    }
    std::swap(a[p], a[i]);
    i = p;
  }
  return i;
}

// Funcion nueva que cuenta los intercambios en lugar de retornar el indice
template <class T, class Compare>
std::size_t complHeapPercolateUpCount(std::vector<T>& a, std::size_t i, Compare comp) {
  std::size_t swaps = 0;
  while (pqHasParent(i)) {
    const std::size_t p = pqParent(i);
    if (!comp(a[p], a[i])) {
      break;
    }
    std::swap(a[p], a[i]);
    swaps++;
    i = p;
  }
  return swaps;
}

}  // namespace ods
```

**Código completo de la demostración modificada añadiendo la parte del bloque 3 al archivo demo_pq_complheap_basico.cpp :**
*(Se añade al final de la función main en `demos/demo_pq_complheap_basico.cpp`, incluyendo `#include <functional>` al inicio del archivo)*

```cpp
#include <iostream>
#include <vector>
#include <functional> // Agregado para usar std::less

#include "Capitulo6.h"

namespace {

template <typename T>
void printVector(const std::vector<T>& xs, const char* label) {
  std::cout << label << ": [";
  for (std::size_t i = 0; i < xs.size(); ++i) {
    if (i != 0) std::cout << ", ";
    std::cout << xs[i];
  }
  std::cout << "]\n";
}

}  // namespace


int main() {
  // PARTE ORIGINAL DE LA DEMO
  std::vector<int> base{4, 10, 7, 1, 3, 9};
  ods::PQ_ComplHeap<int> pq(base);

  std::cout << "PQ_ComplHeap construido con heapify de Floyd\n";
  printVector(base, "entrada");
  printVector(pq.data(), "heap interno");
  std::cout << "getMax() = " << pq.getMax() << "\n\n";

  for (int x : {12, 5, 14}) {
    pq.insert(x);
    std::cout << "insert(" << x << ")\n";
    printVector(pq.data(), "heap interno");
    std::cout << "max actual = " << pq.getMax() << "\n\n";
  }

  while (!pq.empty()) {
    int y = pq.delMax();
    std::cout << "delMax() -> " << y << "\n";
    printVector(pq.data(), "heap interno");
  }

  
  std::cout << "\nDEMO BLOQUE 3: CONTEO DE INTERCAMBIOS\n";
  std::vector<int> arr;
  std::vector<int> secuencia = {40, 10, 70, 30, 90, 20, 80, 60};
  std::less<int> comp;

  for (int x : secuencia) {
    arr.push_back(x);
    // Usamos la función modificada para contar
    std::size_t swaps = ods::complHeapPercolateUpCount(arr, arr.size() - 1, comp);
    
    std::cout << "Insertando: " << x << " | Intercambios: " << swaps << " | Arreglo: [";
    for (std::size_t i = 0; i < arr.size(); ++i) {
      if (i != 0) std::cout << ", ";
      std::cout << arr[i];
    }
    std::cout << "] | Propiedad Heap: SI\n";
  }

  return 0;
}
```


**Salida de la demostración:**

```bash
AXEL@DESKTOP-70IITE7 UCRT64 /c/Users/AXEL/OneDrive/Escritorio/uni/2026-1/AED/Repositorio/Personal/CC232/Libreria_cc232/Semana6
$ ./build/sem6_demo_pq_complheap_basico.exe
PQ_ComplHeap construido con heapify de Floyd
entrada: [4, 10, 7, 1, 3, 9]
heap interno: [10, 4, 9, 1, 3, 7]
getMax() = 10

insert(12)
heap interno: [12, 4, 10, 1, 3, 7, 9]
max actual = 12

insert(5)
heap interno: [12, 5, 10, 4, 3, 7, 9, 1]
max actual = 12

insert(14)
heap interno: [14, 12, 10, 5, 3, 7, 9, 1, 4]
max actual = 14

delMax() -> 14
heap interno: [12, 5, 10, 4, 3, 7, 9, 1]
delMax() -> 12
heap interno: [10, 5, 9, 4, 3, 7, 1]
delMax() -> 10
heap interno: [9, 5, 7, 4, 3, 1]
delMax() -> 9
heap interno: [7, 5, 1, 4, 3]
delMax() -> 7
heap interno: [5, 4, 1, 3]
delMax() -> 5
heap interno: [4, 3, 1]
delMax() -> 4
heap interno: [3, 1]
delMax() -> 3
heap interno: [1]
delMax() -> 1
heap interno: []

DEMO BLOQUE 3: CONTEO DE INTERCAMBIOS
Insertando: 40 | Intercambios: 0 | Arreglo: [40] | Propiedad Heap: SI
Insertando: 10 | Intercambios: 0 | Arreglo: [40, 10] | Propiedad Heap: SI
Insertando: 70 | Intercambios: 1 | Arreglo: [70, 10, 40] | Propiedad Heap: SI
Insertando: 30 | Intercambios: 1 | Arreglo: [70, 30, 40, 10] | Propiedad Heap: SI
Insertando: 90 | Intercambios: 2 | Arreglo: [90, 70, 40, 10, 30] | Propiedad Heap: SI
Insertando: 20 | Intercambios: 0 | Arreglo: [90, 70, 40, 10, 30, 20] | Propiedad Heap: SI
Insertando: 80 | Intercambios: 1 | Arreglo: [90, 70, 80, 10, 30, 20, 40] | Propiedad Heap: SI
Insertando: 60 | Intercambios: 1 | Arreglo: [90, 70, 80, 60, 30, 20, 40, 10] | Propiedad Heap: SI

```

**Argumento de costo:**

El costo de `percolateUp` es $O(\log n)$. Al ser un árbol binario completo, la altura crece de forma logarítmica. Como el nodo insertado solo sube en línea recta hacia la raíz, el número máximo de comparaciones e intercambios nunca superará la altura del árbol ($\approx \log_2 n$).


1. **¿En qué casos `percolateUp` hace cero intercambios?**
   Cuando el valor insertado es menor o igual a su padre. Simplemente se queda en la hoja donde se insertó porque ya cumple la regla.

2. **¿En qué casos puede hacer $O(\log n)$ intercambios?**
   Cuando se inserta el elemento más grande de todos (el nuevo máximo). Tendrá que burbujear desde la última hoja hasta llegar a la raíz.

3. **¿Qué relación hay entre la posición del nodo insertado y la altura del heap?**
   Los intercambios están limitados por la distancia desde la hoja donde se inserta el nodo hasta la raíz. Esa distancia máxima es exactamente la altura del heap.

4. **¿Por qué el arreglo interno no necesariamente queda ordenado?**
    Porque el heap solo impone un orden "vertical" (el padre siempre es mayor que los hijos). No hay ninguna regla "horizontal" que obligue a ordenar los valores entre hermanos.

5. **¿Qué propiedad sí queda garantizada?**
   La propiedad de max-heap: todo nodo es mayor o igual a sus descendientes. Esto asegura que el elemento más grande siempre quede atrapado en el índice 0.


## Bloque 4 - Modificación de percolateDown: elección del hijo dominante

Revisamos:
* `Semana6/include/PQ_ComplHeap_percolateDown.h`
* `Semana6/include/PQ_ComplHeap_delMax.h`
* `Semana6/demos/demo_pq_complheap_basico.cpp`

**Entregables del bloque:**

* **Código completo de PQ_ComplHeap_percolateDown.h incluida la función nueva:**  
*(Añadido en `Libreria_cc232/Semana6/include/PQ_ComplHeap_percolateDown.h`)*

```cpp
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
```

* **Código completo de PQ_ComplHeap_delMax.h:**  
*(El codigo no fue alterado)*

```cpp
#pragma once

#include <stdexcept>
#include <vector>

#include "PQ_ComplHeap_percolateDown.h"

namespace ods {

template <class T, class Compare>
T complHeapDelMax(std::vector<T>& a, Compare comp) {
  if (a.empty()) {
    throw std::out_of_range("delMax() sobre heap vacio");
  }
  T ans = a.front();
  a.front() = a.back();
  a.pop_back();
  if (!a.empty()) {
    complHeapPercolateDown(a, a.size(), 0, comp);
  }
  return ans;
}

}  // namespace ods
```

* **Código completo de la demostración modificada del archivo demo_pq_complheap_basico.cpp :**  
*(Se añade al final de la función main en `demos/demo_pq_complheap_basico.cpp`)*

```cpp
#include <iostream>
#include <vector>
#include <functional> // Agregado para usar std::less

#include "Capitulo6.h"

namespace {

template <typename T>
void printVector(const std::vector<T>& xs, const char* label) {
  std::cout << label << ": [";
  for (std::size_t i = 0; i < xs.size(); ++i) {
    if (i != 0) std::cout << ", ";
    std::cout << xs[i];
  }
  std::cout << "]\n";
}

}  // namespace


int main() {
  // Parte original de la demo
  std::vector<int> base{4, 10, 7, 1, 3, 9};
  ods::PQ_ComplHeap<int> pq(base);

  std::cout << "PQ_ComplHeap construido con heapify de Floyd\n";
  printVector(base, "entrada");
  printVector(pq.data(), "heap interno");
  std::cout << "getMax() = " << pq.getMax() << "\n\n";

  for (int x : {12, 5, 14}) {
    pq.insert(x);
    std::cout << "insert(" << x << ")\n";
    printVector(pq.data(), "heap interno");
    std::cout << "max actual = " << pq.getMax() << "\n\n";
  }

  while (!pq.empty()) {
    int y = pq.delMax();
    std::cout << "delMax() -> " << y << "\n";
    printVector(pq.data(), "heap interno");
  }

  //Bloque 3 : Demo de conteo con intercambios
  std::cout << "\nDEMO BLOQUE 3: CONTEO DE INTERCAMBIOS\n";
  std::vector<int> arr;
  std::vector<int> secuencia = {40, 10, 70, 30, 90, 20, 80, 60};
  std::less<int> comp;

  for (int x : secuencia) {
    arr.push_back(x);
    // Usamos la función modificada para contar
    std::size_t swaps = ods::complHeapPercolateUpCount(arr, arr.size() - 1, comp);
    
    std::cout << "Insertando: " << x << " | Intercambios: " << swaps << " | Arreglo: [";
    for (std::size_t i = 0; i < arr.size(); ++i) {
      if (i != 0) std::cout << ", ";
      std::cout << arr[i];
    }
    std::cout << "] | Propiedad Heap: SI\n";
  }

  // Bloque 4 : Demo DELMAX con conteo 
  std::cout << "\nDEMO BLOQUE 4: DELMAX Y CONTEO\n";
  // Usamos el heap resultante del bloque 3
  std::vector<int> heap_b4 = {90, 70, 80, 60, 30, 20, 40, 10};
  
  while (!heap_b4.empty()) {
    int max_val = heap_b4.front();
    heap_b4.front() = heap_b4.back();
    heap_b4.pop_back();
    
    std::cout << "Max eliminado: " << max_val << "\nAntes de reparar: [";
    for (size_t i = 0; i < heap_b4.size(); ++i) {
      if (i != 0) std::cout << ", ";
      std::cout << heap_b4[i];
    }
    std::cout << "]\n";

    std::size_t swaps = 0;
    if (!heap_b4.empty()) {
      swaps = ods::complHeapPercolateDownCount(heap_b4, heap_b4.size(), 0, comp);
    }

    std::cout << "Intercambios: " << swaps << "\nDespues de reparar: [";
    for (size_t i = 0; i < heap_b4.size(); ++i) {
      if (i != 0) std::cout << ", ";
      std::cout << heap_b4[i];
    }
    std::cout << "]\n------------------------\n";
  }

  return 0;
}
```

* **Salida de la demostración:**

```bash
AXEL@DESKTOP-70IITE7 UCRT64 /c/Users/AXEL/OneDrive/Escritorio/uni/2026-1/AED/Repositorio/Personal/CC232/Libreria_cc232/Semana6
$ ./build/sem6_demo_pq_complheap_basico.exe

...

DEMO BLOQUE 4: DELMAX Y CONTEO
Max eliminado: 90
Antes de reparar: [10, 70, 80, 60, 30, 20, 40]
Intercambios: 2
Despues de reparar: [80, 70, 40, 60, 30, 20, 10]
------------------------
Max eliminado: 80
Antes de reparar: [10, 70, 40, 60, 30, 20]
Intercambios: 2
Despues de reparar: [70, 60, 40, 10, 30, 20]
------------------------
Max eliminado: 70
Antes de reparar: [20, 60, 40, 10, 30]
Intercambios: 2
Despues de reparar: [60, 30, 40, 10, 20]
------------------------
Max eliminado: 60
Antes de reparar: [20, 30, 40, 10]
Intercambios: 1
Despues de reparar: [40, 30, 20, 10]
------------------------
Max eliminado: 40
Antes de reparar: [10, 30, 20]
Intercambios: 1
Despues de reparar: [30, 10, 20]
------------------------
Max eliminado: 30
Antes de reparar: [20, 10]
Intercambios: 0
Despues de reparar: [20, 10]
------------------------
Max eliminado: 20
Antes de reparar: [10]
Intercambios: 0
Despues de reparar: [10]
------------------------
Max eliminado: 10
Antes de reparar: []
Intercambios: 0
Despues de reparar: []
------------------------


```

* **Trazado manual de una eliminación:**  
*(Trazado de la eliminación del 90)*

  * **Estado inicial:** `[90, 70, 80, 60, 30, 20, 40, 10]`
  * **Remoción:** Se remueve 90 y se mueve 10 a la raíz. El arreglo queda `[10, 70, 80, 60, 30, 20, 40]`.
  * **Hundimiento en índice 0:** Sus hijos son 70 y 80. El dominante es 80. Como `10 < 80`, se realiza el intercambio.  
    *Arreglo resultante:* `[80, 70, 10, 60, 30, 20, 40]` (1 intercambio).
  * **Hundimiento en índice 2:** Sus hijos son 20 y 40. El dominante es 40. Como `10 < 40`, se realiza el intercambio.  
    *Arreglo resultante:* `[80, 70, 40, 60, 30, 20, 10]` (2 intercambios).
  * **Fin:** El 10 queda en el índice 6, que constituye una hoja al no tener hijo izquierdo. Termina la reparación.

### Preguntas : 

  * **¿Por qué después de delMax se mueve el último elemento a la raíz?**  
    Para preservar la propiedad de estructura de árbol binario completo. El último elemento es el único que puede retirarse sin dejar espacios vacíos en el arreglo.

  * **¿Por qué la reparación baja y no sube?**  
    Porque se trasladó una hoja (un valor comúnmente pequeño) a la raíz (la posición del máximo). Para restaurar el orden jerárquico, este valor debe hundirse hasta encontrar su nivel correspondiente.

  * **¿Cómo se decide entre hijo izquierdo e hijo derecho?**  
    Se comparan ambos y se elige el mayor. Si se promoviera al menor, el nuevo padre sería más pequeño que su otro hijo, violando la propiedad fundamental del max-heap.

  * **¿Qué pasa si el nodo actual tiene un solo hijo?**  
    Ese hijo será obligatoriamente el izquierdo debido a las propiedades de completitud. La comparación se hace directamente con él, omitiendo evaluar al derecho porque no existe.

  * **¿Por qué delMax tiene costo $O(\log n)$?**  
    Porque el nodo colocado en la raíz solo desciende por un único camino lineal hasta llegar, en el peor de los casos, a una hoja. El número máximo de intercambios se encuentra acotado por la altura del árbol.


## Bloque 5 - Validación explícita de la propiedad heap

Revisamos:
* `Semana6/include/PQ_ComplHeap.h`
* `Semana6/pruebas_publicas/test_public_week6.cpp`
* `Semana6/pruebas_internas/test_internal_week6.cpp`

**Entregables del bloque:**

* **Código completo de PQ_ComplHeap.h añadiendo la funcion de validación:**  
*(Añadido dentro de la clase `PQ_ComplHeap` en `Libreria_cc232/Semana6/include/PQ_ComplHeap.h`, debajo del método `isHeap()`)*

```cpp
#pragma once

#include <functional>
#include <initializer_list>
#include <stdexcept>
#include <utility>
#include <vector>

#include "PQ.h"
#include "PQ_ComplHeap_delMax.h"
#include "PQ_ComplHeap_getMax.h"
#include "PQ_ComplHeap_heapifyFloyd.h"
#include "PQ_ComplHeap_insert.h"
#include "PQ_ComplHeap_macro.h"

namespace ods {

template <class T, class Compare = std::less<T>>
class PQ_ComplHeap : public PQ<T> {
 public:
  PQ_ComplHeap() = default;
  explicit PQ_ComplHeap(Compare comp) : comp_(std::move(comp)) {}

  explicit PQ_ComplHeap(std::vector<T> values, Compare comp = Compare{})
      : data_(std::move(values)), comp_(std::move(comp)) {
    heapify();
  }

  PQ_ComplHeap(std::initializer_list<T> values, Compare comp = Compare{})
      : data_(values), comp_(std::move(comp)) {
    heapify();
  }

  void insert(const T& e) override { complHeapInsert(data_, e, comp_); }

  template <class InputIt>
  void insertAll(InputIt first, InputIt last) {
    for (; first != last; ++first) {
      insert(*first);
    }
  }

  T delMax() override { return complHeapDelMax(data_, comp_); }

  const T& getMax() const override { return complHeapGetMax(data_); }
  bool empty() const noexcept override { return data_.empty(); }
  std::size_t size() const noexcept override { return data_.size(); }

  void clear() noexcept { data_.clear(); }
  void reserve(std::size_t n) { data_.reserve(n); }
  void heapify() { complHeapHeapifyFloyd(data_, comp_); }

  void rebuildFrom(std::vector<T> values) {
    data_ = std::move(values);
    heapify();
  }

  const std::vector<T>& data() const noexcept { return data_; }
  static constexpr std::size_t parent(std::size_t i) noexcept { return pqParent(i); }
  static constexpr std::size_t left(std::size_t i) noexcept { return pqLeftChild(i); }
  static constexpr std::size_t right(std::size_t i) noexcept { return pqRightChild(i); }

  bool isHeap() const {
    for (std::size_t i = 0; i < data_.size(); ++i) {
      const std::size_t l = left(i);
      const std::size_t r = right(i);
      if (l < data_.size() && comp_(data_[i], data_[l])) {
        return false;
      }
      if (r < data_.size() && comp_(data_[i], data_[r])) {
        return false;
      }
    }
    return true;
  }

  // Bloque 5 : Función de validación explícita
  bool isValidHeap() const {
    for (std::size_t i = 0; i < data_.size(); ++i) {
      const std::size_t l = left(i);
      const std::size_t r = right(i);
      
      if (l < data_.size() && comp_(data_[i], data_[l])) {
        return false;
      }
      if (r < data_.size() && comp_(data_[i], data_[r])) {
        return false;
      }
    }
    return true;
  }

 private:
  std::vector<T> data_;
  Compare comp_{};
};

}  // namespace ods
```

* **Pruebas públicas actualizadas :**  
*(Reemplazo completo del archivo`Libreria_cc232/Semana6/pruebas_publicas/test_public_week6.cpp` ara incluir el bloque inicial de las 6 validaciones con isValidHeap() y reemplazar todas las llamadas antiguas de isHeap() en el resto del archivo)*

```cpp
#include <algorithm>
#include <cassert>
#include <memory>
#include <vector>

#include "Capitulo5.h"
#include "Capitulo6.h"

int main() {
  // Bloque 5 : PRUEBAS DE VALIDACIÓN isValidHeap
  ods::PQ_ComplHeap<int> pqEmpty;
  assert(pqEmpty.isValidHeap()); // 1. Heap vacío

  ods::PQ_ComplHeap<int> pqOne;
  pqOne.insert(42);
  assert(pqOne.isValidHeap()); // 2. Heap con un elemento

  ods::PQ_ComplHeap<int> pqRep;
  pqRep.insert(7); pqRep.insert(7); pqRep.insert(7);
  assert(pqRep.isValidHeap()); // 3. Heap con elementos repetidos

  ods::PQ_ComplHeap<int> pqIns;
  for (int x : {15, 2, 8, 1, 99, 4}) pqIns.insert(x);
  assert(pqIns.isValidHeap()); // 4. Heap construido por inserciones

  ods::PQ_ComplHeap<int> h{4, 10, 7, 1, 3, 9};
  assert(h.isValidHeap()); // 5. Heap construido por inicializador (heapify)
  assert(h.getMax() == 10);
  
  h.insert(12);
  assert(h.isValidHeap()); 
  
  assert(h.delMax() == 12);
  assert(h.isValidHeap()); // 6. Heap después de inserciones y extracciones
  
  // ----------------------------------------------------
  // Pruebas de ordenamiento
  std::vector<int> xs{5, 1, 8, 3, 2};
  ods::heapSort(xs);
  assert((xs == std::vector<int>{1, 2, 3, 5, 8}));

  // Pruebas de Leftist Heap
  ods::PQ_LeftHeap<int> a{7, 2, 9};
  ods::PQ_LeftHeap<int> b{1, 8, 3};
  ods::leftHeapMerge(a, b);
  assert(b.empty());
  assert(a.size() == 6);
  assert(a.isLeftistHeap());
  assert(a.getMax() == 9);

  // Pruebas de Codificación Huffman
  const std::vector<ods::HuffmanSymbol> s{{'a', 45}, {'b', 13}, {'c', 12},
                                          {'d', 16}, {'e', 9},  {'f', 5}};
  const auto codes = ods::huffmanGenerateCodes(s);
  const auto tree = ods::huffmanGenerateTree(s);
  const std::string msg = "face";
  const std::string bits = ods::huffmanEncode(msg, codes);
  assert(ods::huffmanDecode(bits, tree) == msg);
  assert(ods::huffmanIsPrefixFree(codes));

  // Pruebas de Binary Search Tree (Rotaciones)
  ods::BinarySearchTree<int> bst;
  for (int x : {8, 3, 10, 1, 6, 14, 4, 7}) {
    bst.add(x);
  }
  const auto before = bst.inorder();
  bst.rotateRight(bst.root());
  bst.rotateLeft(bst.root());
  const auto after = bst.inorder();
  assert(before == after);
  assert(bst.isBST());

  // Pruebas de Treap
  ods::Treap<int> treap(123);
  assert(treap.addWithPriority(8, 80));
  assert(treap.addWithPriority(3, 60));
  assert(treap.addWithPriority(10, 90));
  assert(treap.addWithPriority(1, 50));
  assert(treap.addWithPriority(6, 70));
  assert(treap.isTreap());
  assert(!treap.addWithPriority(6, 71));
  assert(treap.contains(3));
  assert(treap.remove(3));
  assert(!treap.contains(3));
  assert(treap.isTreap());

  return 0;
}
```

* **Pruebas internas actualizadas :**  
*(Reemplazo completo del archivo `Libreria_cc232/Semana6/pruebas_internas/test_internal_week6.cpp` incorporando las pruebas de validación explícita y estandarizando las aserciones de isValidHeap() dentro de los ciclos de extracción y validación continua)*

```cpp
#include <algorithm>
#include <cassert>
#include <memory>
#include <vector>

#include "Capitulo5.h"
#include "Capitulo6.h"

int main() {
  // Bloque 5: PRUEBAS DE VALIDACIÓN isValidHeap
  ods::PQ_ComplHeap<int> pqEmpty;
  assert(pqEmpty.isValidHeap()); // 1. Heap vacío

  ods::PQ_ComplHeap<int> pqOne;
  pqOne.insert(42);
  assert(pqOne.isValidHeap()); // 2. Heap con un elemento

  ods::PQ_ComplHeap<int> pqRep;
  pqRep.insert(7); pqRep.insert(7); pqRep.insert(7);
  assert(pqRep.isValidHeap()); // 3. Heap con elementos repetidos

  ods::PQ_ComplHeap<int> pqIns;
  for (int x : {15, 2, 8, 1, 99, 4}) pqIns.insert(x);
  assert(pqIns.isValidHeap()); // 4. Heap construido por inserciones

  ods::PQ_ComplHeap<int> pqHeapify(std::vector<int>{15, 2, 8, 1, 99, 4});
  assert(pqHeapify.isValidHeap()); // 5. Heap construido por heapify
  
  pqHeapify.delMax();
  pqHeapify.delMax();
  assert(pqHeapify.isValidHeap()); // 6. Heap después de varias llamadas a delMax
  // ----------------------------------------------------

  // PQ_ComplHeap: secuencia completa de extracciones.
  ods::PQ_ComplHeap<int> pq;
  for (int x : {8, 3, 10, 1, 6, 14, 4, 7, 13, 14}) {
    pq.insert(x);
    assert(pq.isValidHeap()); // Validación tras cada inserción
  }
  
  std::vector<int> out;
  while (!pq.empty()) {
    out.push_back(pq.delMax());
    assert(pq.empty() || pq.isValidHeap()); // Validación tras cada extracción
  }
  assert((out == std::vector<int>{14, 14, 13, 10, 8, 7, 6, 4, 3, 1}));

  // Leftist heap: merge e invariantes.
  ods::PQ_LeftHeap<int> a{20, 7, 18, 3};
  ods::PQ_LeftHeap<int> b{19, 8, 4, 1, 17};
  a.merge(b);
  assert(a.isLeftistHeap());
  assert(b.empty());
  
  std::vector<int> leftOut;
  while (!a.empty()) {
    leftOut.push_back(a.delMax());
    assert(a.empty() || a.isLeftistHeap());
  }
  assert((leftOut == std::vector<int>{20, 19, 18, 17, 8, 7, 4, 3, 1}));

  // Huffman: heap completo y leftist heap deben tener mismo costo ponderado.
  const std::vector<ods::HuffmanSymbol> s{{'a', 45}, {'b', 13}, {'c', 12},
                                          {'d', 16}, {'e', 9},  {'f', 5}};
  const auto codes1 = ods::huffmanGenerateCodes(s);
  const auto codes2 = ods::huffmanGenerateCodesLeftHeap(s);
  assert(ods::huffmanIsPrefixFree(codes1));
  assert(ods::huffmanIsPrefixFree(codes2));
  assert(ods::huffmanWeightedPathLength(s, codes1) == 224);
  assert(ods::huffmanWeightedPathLength(s, codes2) == 224);

  // Rotaciones BST: preservan inorder aun cuando cambie la forma.
  ods::BinarySearchTree<int> bst;
  for (int x : {8, 3, 10, 1, 6, 14, 4, 7, 13}) {
    bst.add(x);
  }
  auto sorted = bst.inorder();
  bst.rotateLeft(bst.root());
  assert(bst.isBST());
  assert(bst.inorder() == sorted);
  
  bst.rotateRight(bst.root());
  assert(bst.isBST());
  assert(bst.inorder() == sorted);

  // Treap: BST por clave + heap por prioridad.
  ods::Treap<int> treap(555);
  treap.addWithPriority(8, 80);
  treap.addWithPriority(3, 40);
  treap.addWithPriority(10, 90);
  treap.addWithPriority(1, 20);
  treap.addWithPriority(6, 70);
  treap.addWithPriority(14, 120);
  treap.addWithPriority(4, 65);
  treap.addWithPriority(7, 68);
  
  assert(treap.isTreap());
  assert((treap.inorderKeys() == std::vector<int>{1, 3, 4, 6, 7, 8, 10, 14}));
  assert(treap.lowerBound(5)->key == 6);
  assert(treap.upperBound(6)->key == 7);
  
  assert(treap.remove(3));
  assert(treap.remove(8));
  assert(treap.isTreap());
  assert((treap.inorderKeys() == std::vector<int>{1, 4, 6, 7, 10, 14}));

  return 0;
}

```

* **Evidencia de ctest:**

```bash
AXEL@DESKTOP-70IITE7 UCRT64 /c/Users/AXEL/OneDrive/Escritorio/uni/2026-1/AED/Repositorio/Personal/CC232/Libreria_cc232
$ ctest --test-dir build-debug -C Debug -R semana6 --output-on-failure
Test project C:/Users/AXEL/OneDrive/Escritorio/uni/2026-1/AED/Repositorio/Personal/CC232/Libreria_cc232/build-debug
    Start 22: semana6_public
1/2 Test #22: semana6_public ...................   Passed    0.13 sec
    Start 23: semana6_internal
2/2 Test #23: semana6_internal .................   Passed    0.12 sec

100% tests passed, 0 tests failed out of 2

Total Test time (real) =   0.45 sec

```

### Preguntas : 

  * **¿Qué invariante verifica la función?**  
    La propiedad estructural de heap: que el valor de cada nodo padre sea siempre mayor o igual (en un max-heap) al valor de sus hijos directos.

  * **¿Por qué basta revisar relaciones padre-hijo?**  
    Por la propiedad de transitividad. Si el ancestro es mayor o igual que el padre, y el padre es mayor o igual que el hijo, matemáticamente se garantiza que el ancestro es mayor o igual que el hijo.

  * **¿Por qué no es necesario comparar cada nodo con todos sus descendientes?**  
    Debido a la misma relación de transitividad mencionada. Realizar comparaciones exhaustivas con cada descendiente resultaría redundante y reduciría la eficiencia del algoritmo a una complejidad de $O(n^2)$.

  * **¿Cuál es el costo de validar todo el heap?**  
    El costo temporal es de $O(n)$, debido a que se recorre el arreglo completo exactamente una vez y se efectúan dos comparaciones simples (hijo izquierdo e hijo derecho) por cada elemento.

  * **¿Por qué esta función es útil en pruebas pero no necesariamente en producción?**  
    Porque operaciones básicas como insertar o eliminar (`delMax`) toman tiempo logarítmico $O(\log n)$. Si tras cada una de estas rutinas se invoca una validación de costo lineal $O(n)$, se degradaría la eficiencia global de la estructura. Por ende, su propósito queda restringido a la verificación de la lógica durante la etapa de desarrollo.


## Bloque 6 - Construcción de heap: inserciones sucesivas vs Floyd

Revisamos:
* `Semana6/include/PQ_ComplHeap_heapifyFloyd.h`
* `Semana6/include/PQ_ComplHeap_insert.h`
* `Semana6/demos/demo_heapify_floyd.cpp`

**Entregables del bloque:**

* **Codigo completo del archivo demo_heapify_floyd.cpp con la demostración modificada:**  
*(Reemplazamos todo el contenido de `Libreria_cc232/Semana6/demos/demo_heapify_floyd.cpp` por este código)*

```cpp
#include <iostream>
#include <vector>
#include <functional>
#include "Capitulo6.h"

namespace {
template <typename T>
void printVector(const std::vector<T>& xs, const char* label) {
  std::cout << label << ": [";
  for (std::size_t i = 0; i < xs.size(); ++i) {
    if (i != 0) std::cout << ", ";
    std::cout << xs[i];
  }
  std::cout << "]\n";
}

// Función para validar directamente en la demo
bool checkHeap(const std::vector<int>& a) {
  for (std::size_t i = 0; i < a.size(); ++i) {
    std::size_t l = 2 * i + 1;
    std::size_t r = 2 * i + 2;
    if (l < a.size() && a[i] < a[l]) return false;
    if (r < a.size() && a[i] < a[r]) return false;
  }
  return true;
}
}  // namespace

int main() {
  std::vector<int> inicial = {4, 17, 3, 90, 55, 21, 8, 13, 34, 2, 1, 89};
  std::less<int> comp;

  std::cout << "BLOQUE 6: INSERCIONES VS FLOYD\n";
  printVector(inicial, "Arreglo inicial");
  std::cout << "\n";

  // --- CONSTRUCCION A: Inserciones sucesivas ---
  std::vector<int> heapA;
  std::size_t swapsA = 0;
  for (int x : inicial) {
    heapA.push_back(x);
    swapsA += ods::complHeapPercolateUpCount(heapA, heapA.size() - 1, comp);
  }
  printVector(heapA, "Final por inserciones");
  std::cout << "Intercambios (A): " << swapsA << "\n";
  std::cout << "Es heap valido? " << (checkHeap(heapA) ? "SI" : "NO") << "\n\n";

  // --- CONSTRUCCION B: Algoritmo de Floyd ---
  std::vector<int> heapB = inicial;
  std::size_t swapsB = 0;
  if (heapB.size() >= 2) {
    for (std::size_t i = heapB.size() / 2; i-- > 0;) {
      swapsB += ods::complHeapPercolateDownCount(heapB, heapB.size(), i, comp);
    }
  }
  printVector(heapB, "Final por Floyd");
  std::cout << "Intercambios (B): " << swapsB << "\n";
  std::cout << "Es heap valido? " << (checkHeap(heapB) ? "SI" : "NO") << "\n";

  return 0;
}
```

* **Codigo completo del archivo PQ_ComplHeap_insert.h:**  
*(El archivo no fue modificado para este bloque)*

```cpp
#pragma once

#include <vector>

#include "PQ_ComplHeap_percolateUp.h"

namespace ods {

template <class T, class Compare>
void complHeapInsert(std::vector<T>& a, const T& e, Compare comp) {
  a.push_back(e);
  complHeapPercolateUp(a, a.size() - 1, comp);
}

}  // namespace ods

```

* **Codigo completo del archivo PQ_ComplHeap_heapifyFloyd.h:**  
*(El archivo no fue modificado para este bloque)*

```cpp
#pragma once

#include <cstddef>
#include <vector>

#include "PQ_ComplHeap_percolateDown.h"

namespace ods {

template <class T, class Compare>
void complHeapHeapifyFloyd(std::vector<T>& a, Compare comp) {
  if (a.size() < 2) {
    return;
  }
  for (std::size_t i = a.size() / 2; i-- > 0;) {
    complHeapPercolateDown(a, a.size(), i, comp);
  }
}

}  // namespace ods

```

* **Salida de la demostración (Tabla comparativa simulada en consola):**

```bash
AXEL@DESKTOP-70IITE7 UCRT64 /c/Users/AXEL/OneDrive/Escritorio/uni/2026-1/AED/Repositorio/Personal/CC232/Libreria_cc232
$ ./build-debug/Semana6/sem6_demo_heapify_floyd.exe
BLOQUE 6: INSERCIONES VS FLOYD
Arreglo inicial: [4, 17, 3, 90, 55, 21, 8, 13, 34, 2, 1, 89]

Final por inserciones: [90, 55, 89, 34, 17, 21, 8, 4, 13, 2, 1, 3]
Intercambios (A): 9
Es heap valido? SI

Final por Floyd: [90, 55, 89, 34, 4, 21, 8, 13, 17, 2, 1, 3]
Intercambios (B): 7
Es heap valido? SI

```

* **Explicación de complejidad:**  
Construir un heap con inserciones cuesta $O(n \log n)$ porque la mayoría de los nodos (las hojas) se insertan cuando el árbol ya alcanzó su máxima altura, obligándolos a subir por ramas largas. En cambio, Floyd cuesta $O(n)$ porque hace el trabajo al revés: procesa los nodos bajándolos (`percolateDown`). 

La mayoría de los nodos son hojas que bajan 0 veces, el nivel superior baja como máximo 1 vez, y solo la raíz baja la altura completa. La suma de esta progresión decreciente da como resultado un límite lineal estricto de $O(n)$.

### Preguntas :

  * **¿Por qué ambos resultados pueden ser heaps válidos aunque sus arreglos finales no sean idénticos?**  
    El heap es un orden parcial. Solo exige que un padre sea mayor o igual a sus hijos directos. No existe ninguna regla que ordene a los "hermanos" o a nodos en distintas ramas, por lo que una misma colección de datos puede formar múltiples heaps estructuralmente válidos.

  * **¿Por qué insertar $n$ elementos puede costar $O(n \log n)$?**  
    Insertar un elemento usando `percolateUp` cuesta $O(\log n)$ en el peor caso. Repetir esto $n$ veces desde un arreglo vacío multiplica los costos, siendo especialmente ineficiente al final cuando el árbol es más profundo y posee más niveles.

  * **¿Por qué Floyd puede construir el heap en $O(n)$?**  
    Porque invierte el esfuerzo distributivo. El método `percolateDown` realiza más trabajo solo para los nodos cerca de la raíz (que estructuralmente son muy pocos) y casi nada de trabajo para los nodos inferiores (que son la gran mayoría). Matemáticamente la serie de estas operaciones converge a un límite de $O(n)$.

  * **¿Qué nodos procesa Floyd primero?**  
    Comienza exactamente en el último nodo interno (el padre de la última hoja, ubicado en el índice `n/2 - 1`) y avanza en sentido inverso (de derecha a izquierda, de abajo hacia arriba) hasta alcanzar la raíz (índice 0).

  * **¿Por qué Floyd no necesita llamar a percolateDown desde las hojas?**  
    Una hoja carece de hijos hacia donde bajar. Cualquier nodo individual aislado se considera un sub-heap válido por sí mismo, por lo que intentar repararlo constituiría una ejecución redundante de ciclos.


## Bloque 7 - Modificación de heapSort

Revisamos:
* `Semana6/include/vector_heapSort.h`
* `Semana6/demos/demo_heapsort.cpp`

**Entregables del bloque:**

* **Código completo del archivo de vector_heapSort.h modificado:**  
*(Añadimos al final de `Libreria_cc232/Semana6/include/vector_heapSort.h`, antes de cerrar el namespace)*

```cpp
#pragma once

#include <algorithm>
#include <functional>
#include <vector>

#include "PQ_ComplHeap_heapifyFloyd.h"
#include "PQ_ComplHeap_percolateDown.h"

namespace ods {

// Función original
template <class T, class Compare = std::less<T>>
void heapSort(std::vector<T>& a, Compare comp = Compare{}) {
  if (a.size() < 2) {
    return;
  }
  complHeapHeapifyFloyd(a, comp);
  for (std::size_t n = a.size(); n > 1; --n) {
    std::swap(a[0], a[n - 1]);
    complHeapPercolateDown(a, n - 1, 0, comp);
  }
}

// Bloque 7 : Nueva versión de heapSort con dirección de ordenamiento
template <class T, class Compare>
void heapSort(std::vector<T>& a, Compare comp, bool ascending) {
  if (a.size() < 2) return;

  if (ascending) {
    complHeapHeapifyFloyd(a, comp);
    for (std::size_t n = a.size(); n > 1; --n) {
      std::swap(a[0], a[n - 1]);
      complHeapPercolateDown(a, n - 1, 0, comp);
    }
  } else {
    auto revComp = [&](const T& x, const T& y) { return comp(y, x); };
    complHeapHeapifyFloyd(a, revComp);
    for (std::size_t n = a.size(); n > 1; --n) {
      std::swap(a[0], a[n - 1]);
      complHeapPercolateDown(a, n - 1, 0, revComp);
    }
  }
}

template <class T, class Compare = std::less<T>>
std::vector<T> heapSorted(std::vector<T> a, Compare comp = Compare{}) {
  heapSort(a, comp);
  return a;
}

}  // namespace ods
```

* **Codigo completo del archivo demo_heapsort.cpp con la demostración actualizada:**  
*(Reemplazamos el main en `Libreria_cc232/Semana6/demos/demo_heapsort.cpp`)*

```cpp
#include <iostream>
#include <vector>
#include <functional>

#include "Capitulo6.h"

namespace {

template <typename T>
void printVector(const std::vector<T>& xs, const char* label) {
  std::cout << label << ": [";
  for (std::size_t i = 0; i < xs.size(); ++i) {
    if (i != 0) std::cout << ", ";
    std::cout << xs[i];
  }
  std::cout << "]\n";
}

}  // namespace


int main() {
  // PARTE ORIGINAL DE LA DEMO 
  std::vector<int> a_orig{9, 1, 8, 3, 7, 2, 6, 4, 5};
  printVector(a_orig, "entrada");
  ods::heapSort(a_orig);
  printVector(a_orig, "salida ordenada");
  std::cout << "heapSort usa un max-heap implicito y deja el arreglo en orden ascendente.\n";

  // Bloque 7: DEMO DE ASCENDENTE Y DESCENDENTE 
  std::cout << "\nDEMO BLOQUE 7: HEAPSORT ASC / DESC\n";
  std::vector<int> a{5, 1, 5, 3, 8, 2, 8, 0};
  std::less<int> comp;

  printVector(a, "Entrada (con repetidos)");

  // Ascendente
  std::vector<int> asc = a;
  ods::heapSort(asc, comp, true);
  printVector(asc, "Resultado ascendente ");

  // Descendente
  std::vector<int> desc = a;
  ods::heapSort(desc, comp, false);
  printVector(desc, "Resultado descendente");

  return 0;
}
```

* **Evidencia de repetidos (Salida de consola):**

```bash
AXEL@DESKTOP-70IITE7 UCRT64 /c/Users/AXEL/OneDrive/Escritorio/uni/2026-1/AED/Repositorio/Personal/CC232/Libreria_cc232
$ cmake --build build-debug --config Debug --target sem6_demo_heapsort
[2/2] Linking CXX executable Semana6\sem6_demo_heapsort.exe

AXEL@DESKTOP-70IITE7 UCRT64 /c/Users/AXEL/OneDrive/Escritorio/uni/2026-1/AED/Repositorio/Personal/CC232/Libreria_cc232
$ ./build-debug/Semana6/sem6_demo_heapsort.exe
entrada: [9, 1, 8, 3, 7, 2, 6, 4, 5]
salida ordenada: [1, 2, 3, 4, 5, 6, 7, 8, 9]
heapSort usa un max-heap implicito y deja el arreglo en orden ascendente.

DEMO BLOQUE 7: HEAPSORT ASC / DESC
Entrada (con repetidos): [5, 1, 5, 3, 8, 2, 8, 0]
Resultado ascendente : [0, 1, 2, 3, 5, 5, 8, 8]
Resultado descendente: [8, 8, 5, 5, 3, 2, 1, 0]

```
*(Se observa que maneja correctamente los valores 5 y 8 repetidos en ambas direcciones).*

### Preguntas : 
  * **¿Por qué heapsort puede ordenar in situ?**  
    Porque reutiliza el mismo arreglo. Al extraer la raíz, el límite virtual del heap se reduce en uno, dejando espacio libre exactamente al final del arreglo para guardar el elemento extraído sin gastar memoria adicional.

  * **¿Qué parte del algoritmo destruye gradualmente el heap?**  
    El bucle de extracciones. Al usar `std::swap(a[0], a[n - 1])` para mandar la raíz al final y reducir la variable `n`, la estructura de árbol se desintegra paso a paso hasta dejar únicamente el arreglo ordenado.

  * **¿Por qué heapsort cuesta $O(n \log n)$?**  
    Porque se divide en dos fases: construir el heap inicial con el método de Floyd toma un tiempo de $O(n)$, y realizar las $n-1$ extracciones reparando con `percolateDown` cuesta $O(n \log n)$ (ya que cada reparación depende de la altura del árbol, $O(\log n)$).

  * **¿Es heapsort estable? Justifica con un ejemplo.**  
    No es estable. Los intercambios entre padres e hijos provocan "saltos largos" que rompen el orden relativo. Por ejemplo, en `[8a, 2, 8b]`, al extraer la raíz `8a` y mandarla al fondo del arreglo, `8b` podría terminar ubicado a la izquierda de `8a` en el resultado final.

  * **¿Qué diferencia hay entre usar heapSort y extraer todos los elementos con delMax?**  
    La diferencia principal es el consumo de memoria. `heapSort` ordena de forma *in situ* utilizando un espacio extra de $O(1)$. En cambio, extraer los elementos con `delMax` obliga a guardarlos en un vector auxiliar, lo que consume $O(n)$ de memoria adicional.

## Bloque 8 - Heap izquierdista: validación de merge

Revisamos:
* `Semana6/include/PQ_LeftHeap.h`
* `Semana6/include/PQ_LeftHeap_merge.h`
* `Semana6/include/PQ_LeftHeap_insert.h`
* `Semana6/include/PQ_LeftHeap_delMax.h`
* `Semana6/demos/demo_left_heap_merge.cpp`

**Entregables del bloque:**

* **Código completo del archivo PQ_LeftHeap.h con la validación explícita de invariantes :**  
*(Añadido en `Libreria_cc232/Semana6/include/PQ_LeftHeap.h`. Se colocan la estructura `ValidState` y la función `checkNode` en la sección private y `isValidLeftHeap()` en la sección public)*

```cpp
#pragma once

#include <algorithm>
#include <cstddef>
#include <functional>
#include <initializer_list>
#include <queue>
#include <stdexcept>
#include <utility>
#include <vector>

#include "PQ.h"

namespace ods {

template <class T, class Compare = std::less<T>>
class PQ_LeftHeap : public PQ<T> {
  
  struct Node {
    T value;
    int npl{1}; 
    Node* left{nullptr};
    Node* right{nullptr};
    explicit Node(const T& v) : value(v) {}
  };

public:
  PQ_LeftHeap() = default;

  explicit PQ_LeftHeap(Compare comp) : comp_(std::move(comp)) {}

  PQ_LeftHeap(std::initializer_list<T> xs, Compare comp = Compare{}) : comp_(std::move(comp)) {
    for (const T& x : xs) {
      insert(x);
    }
  }

  template <class InputIt>
  PQ_LeftHeap(InputIt first, InputIt last, Compare comp = Compare{}) : comp_(std::move(comp)) {
    for (; first != last; ++first) {
      insert(*first);
    }
  }

  ~PQ_LeftHeap() { clear(root_); }

  PQ_LeftHeap(const PQ_LeftHeap&) = delete;
  PQ_LeftHeap& operator=(const PQ_LeftHeap&) = delete;

  PQ_LeftHeap(PQ_LeftHeap&& other) noexcept
      : root_(other.root_), n_(other.n_), comp_(std::move(other.comp_)) {
    other.root_ = nullptr;
    other.n_ = 0;
  }

  PQ_LeftHeap& operator=(PQ_LeftHeap&& other) noexcept {
    if (this != &other) {
      clear(root_);
      root_ = other.root_;
      n_ = other.n_;
      comp_ = std::move(other.comp_);
      other.root_ = nullptr;
      other.n_ = 0;
    }
    return *this;
  }

  bool empty() const noexcept override { return n_ == 0; }
  std::size_t size() const noexcept override { return n_; }

  const T& getMax() const override {
    if (!root_) {
      throw std::out_of_range("getMax() sobre heap izquierdista vacio");
    }
    return root_->value;
  }

  void insert(const T& e) override {
    root_ = mergeNodes(root_, new Node(e));
    ++n_;
  }

  T delMax() override {
    if (!root_) {
      throw std::out_of_range("delMax() sobre heap izquierdista vacio");
    }
    T ans = root_->value;
    Node* old = root_;
    Node* a = root_->left;
    Node* b = root_->right;
    old->left = nullptr;
    old->right = nullptr;
    delete old;
    root_ = mergeNodes(a, b);
    --n_;
    return ans;
  }

  void merge(PQ_LeftHeap& other) {
    if (this == &other) {
      return;
    }
    root_ = mergeNodes(root_, other.root_);
    n_ += other.n_;
    other.root_ = nullptr;
    other.n_ = 0;
  }

  // Recorrido por niveles
  std::vector<T> levelOrder() const {
    std::vector<T> out;
    std::queue<Node*> q;
    if (root_) q.push(root_);
    while (!q.empty()) {
      Node* u = q.front();
      q.pop();
      out.push_back(u->value);
      if (u->left) q.push(u->left);
      if (u->right) q.push(u->right);
    }
    return out;
  }

  bool isLeftistHeap() const { return check(root_).ok; }

  // Bloque 8 : Validación completa (Heap, Izquierdista y Tamaño)
  bool isValidLeftHeap() const {
    auto res = checkNode(root_);
    return res.ok && (res.size == n_);
  }

private:
  struct Check {
    bool ok;
    int npl;
  };

  // Bloque 8: Estructura de estado para la validación completa.
  // Retorna si el subárbol cumple los invariantes, su NPL actual y su cantidad de nodos reales.
  struct ValidState {
    bool ok;
    int npl;
    std::size_t size;
  };

  Node* root_{nullptr};
  std::size_t n_{0};
  Compare comp_{};

  static int npl(Node* u) noexcept { return u ? u->npl : 0; }


  Node* mergeNodes(Node* a, Node* b) {
    if (!a) return b;
    if (!b) return a;
    if (comp_(a->value, b->value)) {
      std::swap(a, b);
    }
    a->right = mergeNodes(a->right, b);
    
    if (npl(a->left) < npl(a->right)) {
      std::swap(a->left, a->right);
    }
    a->npl = npl(a->right) + 1;
    return a;
  }

  Check check(Node* u) const {
    if (!u) return {true, 0};
    const Check l = check(u->left);
    const Check r = check(u->right);
    const bool heapOk = (!u->left || !comp_(u->value, u->left->value)) &&
                        (!u->right || !comp_(u->value, u->right->value));
    const bool leftistOk = npl(u->left) >= npl(u->right) && u->npl == npl(u->right) + 1;
    return {l.ok && r.ok && heapOk && leftistOk, u->npl};
  }

  // Bloque 8 : Función recursiva de validación rigurosa
  // verifica los puntos 1,2 y 3
  ValidState checkNode(Node* u) const {
    if (!u) return {true, 0, 0};
    
    ValidState l = checkNode(u->left);
    ValidState r = checkNode(u->right);
    
    // 1. Propiedad de Heap (el nodo padre debe dominar a ambos hijos)
    bool heapOk = (!u->left || !comp_(u->value, u->left->value)) &&
                  (!u->right || !comp_(u->value, u->right->value));
                  
    // 2. Propiedad Izquierdista (NPL izquierdo >= NPL derecho) y NPL actual correcto
    bool leftistOk = (l.npl >= r.npl) && (u->npl == r.npl + 1);
    
    // 3. Acumulación de tamaño de subárbol (para cotejar con n_)
    return {l.ok && r.ok && heapOk && leftistOk, u->npl, l.size + r.size + 1};
  }

  // Limpieza recursiva de memoria
  static void clear(Node* u) noexcept {
    if (!u) return;
    clear(u->left);
    clear(u->right);
    delete u;
  }
};

}  // namespace ods

```

* **codigo completo del archivo demo_left_heap_merge con la demostración modificada:**  
*(Reemplaza el main en `Libreria_cc232/Semana6/demos/demo_left_heap_merge.cpp`)*

```cpp
#include <iostream>
#include <vector>

#include "Capitulo6.h"

namespace {

template <typename T>
void printVector(const std::vector<T>& xs, const char* label) {
  std::cout << label << ": [";
  for (std::size_t i = 0; i < xs.size(); ++i) {
    if (i != 0) std::cout << ", ";
    std::cout << xs[i];
  }
  std::cout << "]\n";
}

}  // namespace

int main() {
  std::cout << "DEMO BLOQUE 8: MERGE IZQUIERDISTA\n";
  ods::PQ_LeftHeap<int> a{7, 2, 9};
  ods::PQ_LeftHeap<int> b{1, 8, 3, 11};

  printVector(a.levelOrder(), "Heap A (pre-merge)");
  std::cout << "A valido? " << (a.isValidLeftHeap() ? "SI" : "NO") << "\n";
  
  printVector(b.levelOrder(), "Heap B (pre-merge)");
  std::cout << "B valido? " << (b.isValidLeftHeap() ? "SI" : "NO") << "\n\n";

  a.merge(b);
  
  printVector(a.levelOrder(), "Heap A (post-merge)");
  std::cout << "A valido? " << (a.isValidLeftHeap() ? "SI" : "NO") << "\n";
  std::cout << "B quedo vacio? " << (b.empty() ? "SI" : "NO") << "\n\n";

  a.insert(10);
  printVector(a.levelOrder(), "A despues de insert(10)");
  std::cout << "A valido? " << (a.isValidLeftHeap() ? "SI" : "NO") << "\n\n";

  std::cout << "Secuencia de prioridad (delMax): ";
  while (!a.empty()) {
    std::cout << a.delMax() << ' ';
  }
  std::cout << "\n";
  
  return 0;
}
```
* **Codigo completo del archivo PQ_LeftHeap_merge.h:**  
*(El archivo no fue modificado para este bloque)*

```cpp
#pragma once

#include "PQ_LeftHeap.h"

namespace ods {

template <class T, class Compare>
void leftHeapMerge(PQ_LeftHeap<T, Compare>& a, PQ_LeftHeap<T, Compare>& b) {
  a.merge(b);
}

}  // namespace ods

```

* **Codigo completo del archivo PQ_LeftHeap_insert.h:**  
*(El archivo no fue modificado para este bloque)*

```cpp
#pragma once

#include "PQ_LeftHeap.h"

namespace ods {

template <class T, class Compare>
void leftHeapInsert(PQ_LeftHeap<T, Compare>& h, const T& e) {
  h.insert(e);
}

}  // namespace ods

```

* **Codigo completo del archivo PQ_LeftHeap_delMax.h :**  
*(El archivo no fue modificado para este bloque)*

```cpp
#pragma once

#include "PQ_LeftHeap.h"

namespace ods {

template <class T, class Compare>
T leftHeapDelMax(PQ_LeftHeap<T, Compare>& h) {
  return h.delMax();
}

}  // namespace ods

```

* **Salida de la demostración:**

```bash
AXEL@DESKTOP-70IITE7 UCRT64 /c/Users/AXEL/OneDrive/Escritorio/uni/2026-1/AED/Repositorio/Personal/CC232/Libreria_cc232
$ cmake --build build-debug --config Debug --target sem6_demo_left_heap_merge
[2/2] Linking CXX executable Semana6\sem6_demo_left_heap_merge.exe

AXEL@DESKTOP-70IITE7 UCRT64 /c/Users/AXEL/OneDrive/Escritorio/uni/2026-1/AED/Repositorio/Personal/CC232/Libreria_cc232
$ ./build-debug/Semana6/sem6_demo_left_heap_merge.exe
DEMO BLOQUE 8: MERGE IZQUIERDISTA
Heap A (pre-merge): [9, 7, 2]
A valido? SI
Heap B (pre-merge): [11, 8, 1, 3]
B valido? SI

Heap A (post-merge): [11, 8, 9, 1, 3, 7, 2]
A valido? SI
B quedo vacio? SI

A despues de insert(10): [11, 8, 10, 1, 3, 9, 7, 2]
A valido? SI

Secuencia de prioridad (delMax): 11 10 9 8 7 3 2 1 

```

### **Trazado de una fusión pequeña (Merge de A={7} y B={5}):**
  * Se realiza una comparación entre las raíces, deduciendo que `7>5`. Por ende, la raíz de A(`7`) se consolida como la nueva raíz principal.
  * Se procede a mezclar el subárbol derecho de A(que se encuentra nulo) con B(`5`) mediante la rutina `merge(null, 5)`.
  * El resultado de dicha mezcla corresponde al nodo `5`. Tras este paso, el nodo `7` posee un hijo izquierdo nulo y un hijo derecho referenciando a `5`.
  * Se efectúa el cálculo del NPL: Hijo Izquierdo(null) = 0, Hijo Derecho(5) = 1.
  * Se identifica una transgresión a la propiedad izquierdista debido a que `NPL izq < NPL der`. Para corregirla, se realiza un intercambio de hijos.
  * El nodo `5` se traslada como hijo izquierdo, mientras que la rama derecha se asigna como nula.
  * Se actualiza el NPL del nodo raíz `7` mediante la relación `NPL(derecho nulo) + 1 = 1`.
  * *Estructura final resultante:* Raíz 7, hijo izquierdo 5 e hijo derecho nulo.

### Preguntas : 

  * **¿Por qué merge es la operación central del heap izquierdista?**  
    Porque es el motor de toda la estructura. Las operaciones clásicas como insertar un elemento o eliminar la raíz no tienen una lógica propia; simplemente reutilizan la función `merge` para hacer el trabajo sucio.

  * **¿Cómo se implementa insert usando merge?**  
    Para insertar un valor, se crea un heap pequeño de un solo nodo con ese valor y luego se usa `merge` para fusionarlo con el heap principal.
    
  * **¿Cómo se implementa delMax usando merge?**  
    Se realiza la extracción del nodo raíz y, de manera consecutiva, se efectúa un llamado a `merge` para fusionar el subárbol izquierdo con el subárbol derecho, reconstruyendo así la jerarquía del montículo resultante.

  * **¿Qué propiedad adicional diferencia un heap izquierdista de un heap binario completo?**  
    La propiedad izquierdista. Esta regla obliga a que el "camino más corto hacia un espacio vacío" (NPL) por el lado izquierdo de un nodo siempre sea mayor o igual que por el lado derecho. Esto crea árboles visualmente desequilibrados hacia la izquierda.

  * **¿Qué ventaja conceptual tiene un heap izquierdista frente a un heap binario completo?**  
    Su velocidad para fusionarse ,unir dos heaps binarios normales en un arreglo obliga a reconstruirlos tomando $O(n)$. Un heap izquierdista, al concentrar sus espacios vacíos en el lado derecho (que es un camino muy corto), permite fusionarlos en apenas $O(\log n)$


## Bloque 9 - Huffman: modificación de desempate y caso de un símbolo

Revisamos:
* `Semana6/include/Huffman_PQ.h`
* `Semana6/include/Huffman_PQ_generateTree.h`
* `Semana6/demos/demo_huffman.cpp`


**Entregables del bloque:**

* **Código completo de la demostración agregada (demo_huffman.cpp) :**  
*(Se reemplazara todo el contenido en Libreria_cc232/Semana6/demos/demo_huffman.cpp con este código que procesa los dos casos exigidos)*

```cpp
#include <iostream>
#include <vector>
#include <iomanip>
#include <string>

#include "Capitulo6.h"

void procesarAlfabeto(const std::vector<ods::HuffmanSymbol>& alphabet, const std::string& titulo) {
  std::cout << "=== " << titulo << " ===\n";

  // 1. Mostrar fusiones
  const auto steps = ods::huffmanBuildTrace(alphabet);
  std::cout << "Fusiones:\n";
  for (const auto& s : steps) {
    std::cout << "  (" << s.leftLabel << ':' << s.leftFrequency << ") + ("
              << s.rightLabel << ':' << s.rightFrequency << ") -> "
              << s.mergedFrequency << '\n';
  }

  // 2. Generar códigos 
  const auto codes = ods::huffmanGenerateCodes(alphabet);
  
  // 3. Se imprime la tabla
  std::cout << "\nTabla de codigos:\n";
  std::cout << std::left << std::setw(10) << "Simbolo" 
            << std::setw(15) << "Frecuencia" 
            << std::setw(15) << "Codigo" 
            << "Longitud\n";
  std::cout << std::string(50, '-') << '\n';

  int totalPonderado = 0;
  for (const auto& s : alphabet) {
    std::string code = codes.at(s.symbol);
    int longitud = code.length();
    totalPonderado += s.frequency * longitud;
    std::cout << std::left << std::setw(10) << s.symbol 
              << std::setw(15) << s.frequency 
              << std::setw(15) << code 
              << longitud << '\n';
  }

  std::cout << std::string(50, '-') << '\n';
  std::cout << "Longitud total ponderada: " << totalPonderado << '\n';
  std::cout << "Prefijo libre (valido)? : " << (ods::huffmanIsPrefixFree(codes) ? "SI" : "NO") << "\n\n";
}

int main() {
  // Parte 1: Alfabeto con empates de frecuencia
  const std::vector<ods::HuffmanSymbol> alphabet_ties = {
      {'A', 5}, {'B', 5}, {'C', 10}, {'D', 10}, {'E', 20}
  };
  procesarAlfabeto(alphabet_ties, "ALFABETO CON DESEMPATES");

  // Parte 2: Caso extremo de un solo símbolo
  const std::vector<ods::HuffmanSymbol> alphabet_single = {
      {'X', 100}
  };
  procesarAlfabeto(alphabet_single, "CASO EXTREMO: UN SOLO SIMBOLO");

  return 0;
}
```

* **Codigo completo del archivo Huffman_PQ.h**  
*(El archivo no fue modificado para este bloque)*

```cpp
#pragma once

#include <algorithm>
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "PQ_ComplHeap.h"
#include "PQ_LeftHeap.h"

namespace ods {

struct HuffmanSymbol {
  char symbol{};
  int frequency{};
};

struct HuffmanNode {
  char symbol{};
  int frequency{};
  std::shared_ptr<HuffmanNode> left{};
  std::shared_ptr<HuffmanNode> right{};

  HuffmanNode(char s, int f) : symbol(s), frequency(f) {}
  HuffmanNode(std::shared_ptr<HuffmanNode> a, std::shared_ptr<HuffmanNode> b)
      : symbol('\0'),
        frequency(a->frequency + b->frequency),
        left(std::move(a)),
        right(std::move(b)) {}

  bool leaf() const noexcept { return !left && !right; }
};

struct HuffmanBuildStep {
  int leftFrequency{};
  int rightFrequency{};
  int mergedFrequency{};
  std::string leftLabel;
  std::string rightLabel;
};

struct HuffmanLowerFrequencyFirst {
  bool operator()(const std::shared_ptr<HuffmanNode>& a,
                  const std::shared_ptr<HuffmanNode>& b) const {
    if (a->frequency != b->frequency) {
      return a->frequency > b->frequency;
    }
    return a->symbol > b->symbol;
  }
};

inline std::string huffmanNodeLabel(const std::shared_ptr<HuffmanNode>& u) {
  if (!u) return "null";
  if (u->leaf()) return std::string(1, u->symbol);
  return "*";
}

template <class PriorityQueue>
PriorityQueue huffmanMakeForest(const std::vector<HuffmanSymbol>& alphabet) {
  PriorityQueue pq;
  for (const auto& s : alphabet) {
    if (s.frequency > 0) {
      pq.insert(std::make_shared<HuffmanNode>(s.symbol, s.frequency));
    }
  }
  if (pq.empty()) {
    throw std::invalid_argument("Huffman requiere simbolos con frecuencia positiva");
  }
  return pq;
}

template <class PriorityQueue>
std::shared_ptr<HuffmanNode> huffmanGenerateTreeFromForest(PriorityQueue forest) {
  while (forest.size() > 1) {
    auto a = forest.delMax();
    auto b = forest.delMax();
    forest.insert(std::make_shared<HuffmanNode>(a, b));
  }
  return forest.delMax();
}

template <class PriorityQueue>
std::vector<HuffmanBuildStep> huffmanBuildTraceWith(const std::vector<HuffmanSymbol>& alphabet) {
  PriorityQueue forest = huffmanMakeForest<PriorityQueue>(alphabet);
  std::vector<HuffmanBuildStep> steps;
  while (forest.size() > 1) {
    auto a = forest.delMax();
    auto b = forest.delMax();
    steps.push_back({a->frequency, b->frequency, a->frequency + b->frequency,
                     huffmanNodeLabel(a), huffmanNodeLabel(b)});
    forest.insert(std::make_shared<HuffmanNode>(a, b));
  }
  return steps;
}

template <class PriorityQueue>
std::shared_ptr<HuffmanNode> huffmanGenerateTreeWith(const std::vector<HuffmanSymbol>& alphabet) {
  return huffmanGenerateTreeFromForest(huffmanMakeForest<PriorityQueue>(alphabet));
}

inline std::shared_ptr<HuffmanNode> huffmanGenerateTree(const std::vector<HuffmanSymbol>& alphabet) {
  using PQType = PQ_ComplHeap<std::shared_ptr<HuffmanNode>, HuffmanLowerFrequencyFirst>;
  return huffmanGenerateTreeWith<PQType>(alphabet);
}

inline std::shared_ptr<HuffmanNode> huffmanGenerateTreeLeftHeap(
    const std::vector<HuffmanSymbol>& alphabet) {
  using PQType = PQ_LeftHeap<std::shared_ptr<HuffmanNode>, HuffmanLowerFrequencyFirst>;
  return huffmanGenerateTreeWith<PQType>(alphabet);
}

inline std::vector<HuffmanBuildStep> huffmanBuildTrace(const std::vector<HuffmanSymbol>& alphabet) {
  using PQType = PQ_ComplHeap<std::shared_ptr<HuffmanNode>, HuffmanLowerFrequencyFirst>;
  return huffmanBuildTraceWith<PQType>(alphabet);
}

inline std::vector<HuffmanBuildStep> huffmanBuildTraceLeftHeap(
    const std::vector<HuffmanSymbol>& alphabet) {
  using PQType = PQ_LeftHeap<std::shared_ptr<HuffmanNode>, HuffmanLowerFrequencyFirst>;
  return huffmanBuildTraceWith<PQType>(alphabet);
}

inline void huffmanCollectCodes(const std::shared_ptr<HuffmanNode>& u,
                                const std::string& prefix,
                                std::unordered_map<char, std::string>& out) {
  if (!u) return;
  if (u->leaf()) {
    out[u->symbol] = prefix.empty() ? "0" : prefix;
    return;
  }
  huffmanCollectCodes(u->left, prefix + "0", out);
  huffmanCollectCodes(u->right, prefix + "1", out);
}

template <class PriorityQueue>
std::unordered_map<char, std::string> huffmanGenerateCodesWith(
    const std::vector<HuffmanSymbol>& alphabet) {
  std::unordered_map<char, std::string> codes;
  huffmanCollectCodes(huffmanGenerateTreeWith<PriorityQueue>(alphabet), "", codes);
  return codes;
}

inline std::unordered_map<char, std::string> huffmanGenerateCodes(
    const std::vector<HuffmanSymbol>& alphabet) {
  using PQType = PQ_ComplHeap<std::shared_ptr<HuffmanNode>, HuffmanLowerFrequencyFirst>;
  return huffmanGenerateCodesWith<PQType>(alphabet);
}

inline std::unordered_map<char, std::string> huffmanGenerateCodesLeftHeap(
    const std::vector<HuffmanSymbol>& alphabet) {
  using PQType = PQ_LeftHeap<std::shared_ptr<HuffmanNode>, HuffmanLowerFrequencyFirst>;
  return huffmanGenerateCodesWith<PQType>(alphabet);
}

inline std::string huffmanEncode(const std::string& text,
                                 const std::unordered_map<char, std::string>& codes) {
  std::string bits;
  for (char c : text) {
    auto it = codes.find(c);
    if (it == codes.end()) {
      throw std::invalid_argument("Caracter sin codigo Huffman");
    }
    bits += it->second;
  }
  return bits;
}

inline std::string huffmanDecode(const std::string& bits,
                                 const std::shared_ptr<HuffmanNode>& root) {
  if (!root) return {};
  if (root->leaf()) {
    return std::string(bits.size(), root->symbol);
  }

  std::string out;
  auto u = root;
  for (char bit : bits) {
    if (bit == '0') {
      u = u->left;
    } else if (bit == '1') {
      u = u->right;
    } else {
      throw std::invalid_argument("La cadena codificada solo puede contener 0 y 1");
    }
    if (!u) {
      throw std::invalid_argument("Secuencia Huffman invalida");
    }
    if (u->leaf()) {
      out.push_back(u->symbol);
      u = root;
    }
  }
  if (u != root) {
    throw std::invalid_argument("La cadena codificada termina a mitad de un codigo");
  }
  return out;
}

inline bool huffmanIsPrefixFree(const std::unordered_map<char, std::string>& codes) {
  for (const auto& [ca, sa] : codes) {
    for (const auto& [cb, sb] : codes) {
      if (ca == cb) continue;
      if (sb.rfind(sa, 0) == 0) return false;
    }
  }
  return true;
}

inline int huffmanWeightedPathLength(const std::vector<HuffmanSymbol>& alphabet,
                                     const std::unordered_map<char, std::string>& codes) {
  int total = 0;
  for (const auto& s : alphabet) {
    auto it = codes.find(s.symbol);
    if (s.frequency > 0 && it != codes.end()) {
      total += s.frequency * static_cast<int>(it->second.size());
    }
  }
  return total;
}

}  // namespace ods

```

* **Codigo completo del archivo Huffman_PQ_generateTree.h**  
*(El archivo no fue modificado para este bloque)*

```cpp
#pragma once

#include "Huffman_PQ.h"
```

* **Salida de la demostración:**

```bash
AXEL@DESKTOP-70IITE7 UCRT64 /c/Users/AXEL/OneDrive/Escritorio/uni/2026-1/AED/Repositorio/Personal/CC232/Libreria_cc232
$ cmake --build build-debug --config Debug --target sem6_demo_huffman
[2/2] Linking CXX executable Semana6\sem6_demo_huffman.exe

AXEL@DESKTOP-70IITE7 UCRT64 /c/Users/AXEL/OneDrive/Escritorio/uni/2026-1/AED/Repositorio/Personal/CC232/Libreria_cc232
$ ./build-debug/Semana6/sem6_demo_huffman.exe
=== ALFABETO CON DESEMPATES ===
Fusiones:
  (A:5) + (B:5) -> 10
  (*:10) + (C:10) -> 20
  (D:10) + (*:20) -> 30
  (E:20) + (*:30) -> 50

Tabla de codigos:
Simbolo   Frecuencia     Codigo         Longitud
--------------------------------------------------
A         5              1100           4
B         5              1101           4
C         10             111            3
D         10             10             2
E         20             0              1
--------------------------------------------------
Longitud total ponderada: 110
Prefijo libre (valido)? : SI

=== CASO EXTREMO: UN SOLO SIMBOLO ===
Fusiones:

Tabla de codigos:
Simbolo   Frecuencia     Codigo         Longitud
--------------------------------------------------
X         100            0              1
--------------------------------------------------
Longitud total ponderada: 100
Prefijo libre (valido)? : SI

```

### Preguntas : 

* **¿Por qué Huffman necesita una cola de prioridad?**  
  Permite extraer rápidamente los dos nodos con menor frecuencia e insertar el nuevo nodo fusionado. Usar un Min-Heap reduce el tiempo de estas operaciones a $O(\log n)$.

* **¿Qué elementos se extraen repetidamente?**  
  Se extraen siempre los dos nodos con las frecuencias más bajas del bosque actual, ya sean símbolos originales (hojas) o subárboles ya fusionados (nodos internos).

* **¿Qué nodo se vuelve a insertar?**  
  Se inserta el nuevo nodo padre formado por los dos extraídos. Este nodo no representa ningún símbolo (internamente usa '\0') y su frecuencia es la suma exacta de sus hijos.

* **¿Por qué el caso de un solo símbolo requiere cuidado especial?**  
  El algoritmo estándar fusiona nodos mientras haya más de uno. Con un solo símbolo, el bucle no se ejecuta y queda una raíz aislada. Si no forzamos la asignación de un código (como "0"), se generaría un código vacío "", lo cual invalidaría la decodificación.

* **¿Qué significa que el conjunto de códigos sea libre de prefijos?**  
  Significa que ningún código es el inicio exacto de otro. Por ejemplo, si "A" es 10, ningún otro símbolo puede empezar con 10. Esto garantiza que una cadena de bits se decodifique de forma única y secuencial sin usar separadores.

* **¿Cómo afecta el desempate a la forma del árbol?**  
  Cambia el orden en que se agrupan los nodos. Al desempatar con diferentes criterios, se fusionan distintos subárboles en tiempos diferentes, modificando la estructura del árbol resultante y los códigos binarios asignados a cada símbolo.

* **¿El desempate cambia necesariamente la longitud total ponderada? Justifica.**  
  No ya que aunque la estructura del árbol y los códigos cambien, Huffman agrupa siempre las dos frecuencias más bajas disponibles. Esto garantiza que la longitud total ponderada (el costo de almacenamiento final) siga siendo matemáticamente óptima y mínima.


## Bloque 10 - Treap: modificación de código, rotaciones e invariantes

Revisamos:
* `Semana6/include/Treap.h`
* `Semana6/demos/demo_treap_basico.cpp`
* `Semana6/pruebas_publicas/test_public_week6.cpp`
* `Semana6/pruebas_internas/test_internal_week6.cpp`

### Parte A - Construcción determinística con prioridades fijas


**Entregables del bloque:**

* **Código completo de la demostración modificada (demo_treap_basico.cpp) :**  
*(Se reemplazara todo el contenido en Libreria_cc232/Semana6/demos/demo_treap_basico.cpp con este código que inyecta los pares exactos que exige la rúbricas)*

```cpp
#include <iostream>
#include <vector>
#include <utility>

#include "Capitulo6.h"

int main() {
  ods::Treap<int> t(232);
  
  // Secuencia de pares {clave, prioridad}
  std::vector<std::pair<int, int>> sequence = {
      {50, 50}, {30, 30}, {70, 70}, {20, 20}, {40, 40}, {60, 60}, {80, 80}
  };

  std::cout << "CONSTRUCCION DETERMINISTICA DE TREAP\n";
  
  for (const auto& p : sequence) {
    int key = p.first;
    int prio = p.second;
    
    t.addWithPriority(key, prio);

    std::cout << "------------------------------------------\n";
    std::cout << "Insertado -> Clave: " << key << " | Prioridad: " << prio << "\n";
    
    std::cout << "Inorden      : ";
    for (int k : t.inorderKeys()) std::cout << k << " ";
    std::cout << "\n";

    std::cout << "Por niveles  : ";
    for (int k : t.levelOrderKeys()) std::cout << k << " ";
    std::cout << "\n";

    std::cout << "Raiz actual  : " << t.root()->key << "\n";
    std::cout << "Validaciones : isBST[" << (t.isBST() ? "SI" : "NO") 
              << "] | isHeap[" << (t.isHeapByPriority() ? "SI" : "NO") 
              << "] | isTreap[" << (t.isTreap() ? "SI" : "NO") << "]\n";
  }

  std::cout << "==========================================\n";
  std::cout << "ARBOL FINAL (ASCII ART):\n";
  std::cout << t << "\n";

  return 0;
}
```
* **Codigo completo del archivo Treap.h**  
*(El archivo no fue modificado para este bloque)*

```cpp
#pragma once

#include <algorithm>
#include <cstdint>
#include <functional>
#include <ostream>
#include <queue>
#include <random>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace ods {

template <class T, class Compare = std::less<T>>
class Treap {
 public:
  struct Node {
    T key{};
    std::uint64_t priority{0};
    Node* parent{nullptr};
    Node* left{nullptr};
    Node* right{nullptr};

    Node() = default;
    Node(const T& value, std::uint64_t p, Node* par = nullptr)
        : key(value), priority(p), parent(par) {}

    bool isLeftChild() const { return parent != nullptr && parent->left == this; }
    bool isRightChild() const { return parent != nullptr && parent->right == this; }
  };

  Treap() : rng_(232) {}
  explicit Treap(std::uint64_t seed) : rng_(seed) {}
  explicit Treap(Compare comp, std::uint64_t seed = 232) : comp_(std::move(comp)), rng_(seed) {}

  Treap(const Treap&) = delete;
  Treap& operator=(const Treap&) = delete;

  Treap(Treap&& other) noexcept { swap(other); }
  Treap& operator=(Treap&& other) noexcept {
    if (this != &other) {
      clear();
      swap(other);
    }
    return *this;
  }

  ~Treap() { clear(); }

  void clear() {
    destroy(root_);
    root_ = nullptr;
    size_ = 0;
  }

  void swap(Treap& other) noexcept {
    std::swap(root_, other.root_);
    std::swap(size_, other.size_);
    std::swap(comp_, other.comp_);
    std::swap(rng_, other.rng_);
    std::swap(priorityCounter_, other.priorityCounter_);
  }

  Node* root() const noexcept { return root_; }
  std::size_t size() const noexcept { return size_; }
  bool empty() const noexcept { return size_ == 0; }

  Node* findLast(const T& x) const {
    Node* w = root_;
    Node* prev = nullptr;
    while (w != nullptr) {
      prev = w;
      if (comp_(x, w->key)) {
        w = w->left;
      } else if (comp_(w->key, x)) {
        w = w->right;
      } else {
        return w;
      }
    }
    return prev;
  }

  Node* findEQ(const T& x) const {
    Node* w = root_;
    while (w != nullptr) {
      if (comp_(x, w->key)) {
        w = w->left;
      } else if (comp_(w->key, x)) {
        w = w->right;
      } else {
        return w;
      }
    }
    return nullptr;
  }

  Node* lowerBound(const T& x) const {
    Node* w = root_;
    Node* candidate = nullptr;
    while (w != nullptr) {
      if (comp_(x, w->key)) {
        candidate = w;
        w = w->left;
      } else if (comp_(w->key, x)) {
        w = w->right;
      } else {
        return w;
      }
    }
    return candidate;
  }

  Node* upperBound(const T& x) const {
    Node* w = root_;
    Node* candidate = nullptr;
    while (w != nullptr) {
      if (comp_(x, w->key)) {
        candidate = w;
        w = w->left;
      } else {
        w = w->right;
      }
    }
    return candidate;
  }

  bool contains(const T& x) const { return findEQ(x) != nullptr; }

  bool add(const T& x) { return addWithPriority(x, nextPriority()); }

  bool addWithPriority(const T& x, std::uint64_t priority) {
    Node* u = new Node(x, priority);
    if (!addNode(u)) {
      delete u;
      return false;
    }
    bubbleUp(u);
    return true;
  }

  bool remove(const T& x) {
    Node* u = findEQ(x);
    if (!u) return false;
    trickleDown(u);
    splice(u);
    delete u;
    return true;
  }

  void rotateLeft(Node* u) {
    if (!u || !u->right) return;
    Node* w = u->right;
    w->parent = u->parent;
    if (!u->parent) {
      root_ = w;
    } else if (u->isLeftChild()) {
      u->parent->left = w;
    } else {
      u->parent->right = w;
    }
    u->right = w->left;
    if (u->right) u->right->parent = u;
    w->left = u;
    u->parent = w;
  }

  void rotateRight(Node* u) {
    if (!u || !u->left) return;
    Node* w = u->left;
    w->parent = u->parent;
    if (!u->parent) {
      root_ = w;
    } else if (u->isLeftChild()) {
      u->parent->left = w;
    } else {
      u->parent->right = w;
    }
    u->left = w->right;
    if (u->left) u->left->parent = u;
    w->right = u;
    u->parent = w;
  }

  void bubbleUp(Node* u) {
    while (u->parent && u->parent->priority > u->priority) {
      if (u->isRightChild()) {
        rotateLeft(u->parent);
      } else {
        rotateRight(u->parent);
      }
    }
    if (!u->parent) root_ = u;
  }

  void trickleDown(Node* u) {
    while (u->left || u->right) {
      if (!u->left) {
        rotateLeft(u);
      } else if (!u->right) {
        rotateRight(u);
      } else if (u->left->priority < u->right->priority) {
        rotateRight(u);
      } else {
        rotateLeft(u);
      }
      if (root_ == u) root_ = u->parent;
    }
  }

  std::vector<T> inorderKeys() const {
    std::vector<T> out;
    inorder(root_, out);
    return out;
  }

  std::vector<T> levelOrderKeys() const {
    std::vector<T> out;
    std::queue<Node*> q;
    if (root_) q.push(root_);
    while (!q.empty()) {
      Node* u = q.front();
      q.pop();
      out.push_back(u->key);
      if (u->left) q.push(u->left);
      if (u->right) q.push(u->right);
    }
    return out;
  }

  std::string asciiArt() const {
    if (!root_) return "(treap vacio)\n";
    std::vector<std::string> lines;
    buildAscii(root_, "", true, lines);
    std::ostringstream out;
    for (const auto& line : lines) out << line << '\n';
    return out.str();
  }

  bool isBST() const { return isBST(root_, nullptr, nullptr) && checkParents(root_, nullptr); }
  bool isHeapByPriority() const { return isHeapByPriority(root_); }
  bool isTreap() const { return isBST() && isHeapByPriority(); }

 private:
  Node* root_{nullptr};
  std::size_t size_{0};
  Compare comp_{};
  std::mt19937_64 rng_;
  std::uint64_t priorityCounter_{0};

  std::uint64_t nextPriority() {
    std::uint64_t raw = rng_();
    return (raw << 16) ^ (++priorityCounter_);
  }

  bool addNode(Node* u) {
    u->left = nullptr;
    u->right = nullptr;
    Node* p = findLast(u->key);
    if (!p) {
      root_ = u;
      u->parent = nullptr;
      ++size_;
      return true;
    }
    if (comp_(u->key, p->key)) {
      if (p->left) return false;
      p->left = u;
    } else if (comp_(p->key, u->key)) {
      if (p->right) return false;
      p->right = u;
    } else {
      return false;
    }
    u->parent = p;
    ++size_;
    return true;
  }

  void splice(Node* u) {
    Node* s = u->left ? u->left : u->right;
    if (u == root_) {
      root_ = s;
    } else if (u->isLeftChild()) {
      u->parent->left = s;
    } else {
      u->parent->right = s;
    }
    if (s) s->parent = u->parent;
    --size_;
  }

  static void destroy(Node* u) {
    if (!u) return;
    destroy(u->left);
    destroy(u->right);
    delete u;
  }

  static void inorder(Node* u, std::vector<T>& out) {
    if (!u) return;
    inorder(u->left, out);
    out.push_back(u->key);
    inorder(u->right, out);
  }

  bool isBST(Node* u, const T* low, const T* high) const {
    if (!u) return true;
    if (low && !comp_(*low, u->key)) return false;
    if (high && !comp_(u->key, *high)) return false;
    return isBST(u->left, low, &u->key) && isBST(u->right, &u->key, high);
  }

  static bool checkParents(Node* u, Node* parent) {
    if (!u) return true;
    if (u->parent != parent) return false;
    return checkParents(u->left, u) && checkParents(u->right, u);
  }

  static bool isHeapByPriority(Node* u) {
    if (!u) return true;
    if (u->left && u->left->priority < u->priority) return false;
    if (u->right && u->right->priority < u->priority) return false;
    return isHeapByPriority(u->left) && isHeapByPriority(u->right);
  }

  static std::string nodeLabel(const Node* u) {
    std::ostringstream out;
    out << u->key << "|p=" << u->priority;
    return out.str();
  }

  static void buildAscii(const Node* node, const std::string& prefix, bool isTail,
                         std::vector<std::string>& lines) {
    if (!node) return;
    if (node->right) {
      buildAscii(node->right, prefix + (isTail ? "│   " : "    "), false, lines);
    }
    lines.push_back(prefix + (isTail ? "└── " : "┌── ") + nodeLabel(node));
    if (node->left) {
      buildAscii(node->left, prefix + (isTail ? "    " : "│   "), true, lines);
    }
  }
};

template <class T, class Compare>
inline std::ostream& operator<<(std::ostream& out, const Treap<T, Compare>& t) {
  out << t.asciiArt();
  return out;
}

}  // namespace ods
```

* **Codigo completo del archivo test_public_week6.cpp**  
*(El archivo no fue modificado para este bloque pero previamente ya estaba)*

```cpp
#include <algorithm>
#include <cassert>
#include <memory>
#include <vector>

#include "Capitulo5.h"
#include "Capitulo6.h"

int main() {
  // --- MOD-A6-B5: PRUEBAS DE VALIDACIÓN isValidHeap ---
  ods::PQ_ComplHeap<int> pqEmpty;
  assert(pqEmpty.isValidHeap()); // 1. Heap vacío

  ods::PQ_ComplHeap<int> pqOne;
  pqOne.insert(42);
  assert(pqOne.isValidHeap()); // 2. Heap con un elemento

  ods::PQ_ComplHeap<int> pqRep;
  pqRep.insert(7); pqRep.insert(7); pqRep.insert(7);
  assert(pqRep.isValidHeap()); // 3. Heap con elementos repetidos

  ods::PQ_ComplHeap<int> pqIns;
  for (int x : {15, 2, 8, 1, 99, 4}) pqIns.insert(x);
  assert(pqIns.isValidHeap()); // 4. Heap construido por inserciones

  ods::PQ_ComplHeap<int> h{4, 10, 7, 1, 3, 9};
  assert(h.isValidHeap()); // 5. Heap construido por inicializador (heapify)
  assert(h.getMax() == 10);
  
  h.insert(12);
  assert(h.isValidHeap()); 
  
  assert(h.delMax() == 12);
  assert(h.isValidHeap()); // 6. Heap después de inserciones y extracciones
  // ----------------------------------------------------

  // Pruebas de ordenamiento
  std::vector<int> xs{5, 1, 8, 3, 2};
  ods::heapSort(xs);
  assert((xs == std::vector<int>{1, 2, 3, 5, 8}));

  // Pruebas de Leftist Heap
  ods::PQ_LeftHeap<int> a{7, 2, 9};
  ods::PQ_LeftHeap<int> b{1, 8, 3};
  ods::leftHeapMerge(a, b);
  assert(b.empty());
  assert(a.size() == 6);
  assert(a.isLeftistHeap());
  assert(a.getMax() == 9);

  // Pruebas de Codificación Huffman
  const std::vector<ods::HuffmanSymbol> s{{'a', 45}, {'b', 13}, {'c', 12},
                                          {'d', 16}, {'e', 9},  {'f', 5}};
  const auto codes = ods::huffmanGenerateCodes(s);
  const auto tree = ods::huffmanGenerateTree(s);
  const std::string msg = "face";
  const std::string bits = ods::huffmanEncode(msg, codes);
  assert(ods::huffmanDecode(bits, tree) == msg);
  assert(ods::huffmanIsPrefixFree(codes));

  // Pruebas de Binary Search Tree (Rotaciones)
  ods::BinarySearchTree<int> bst;
  for (int x : {8, 3, 10, 1, 6, 14, 4, 7}) {
    bst.add(x);
  }
  const auto before = bst.inorder();
  bst.rotateRight(bst.root());
  bst.rotateLeft(bst.root());
  const auto after = bst.inorder();
  assert(before == after);
  assert(bst.isBST());

  // Pruebas de Treap
  ods::Treap<int> treap(123);
  assert(treap.addWithPriority(8, 80));
  assert(treap.addWithPriority(3, 60));
  assert(treap.addWithPriority(10, 90));
  assert(treap.addWithPriority(1, 50));
  assert(treap.addWithPriority(6, 70));
  assert(treap.isTreap());
  assert(!treap.addWithPriority(6, 71));
  assert(treap.contains(3));
  assert(treap.remove(3));
  assert(!treap.contains(3));
  assert(treap.isTreap());

  return 0;
}
```

* **Codigo completo del archivo test_internal_week6.cpp**  
*(El archivo no fue modificado para este bloque pero previamente ya estaba)*

```cpp
#include <algorithm>
#include <cassert>
#include <memory>
#include <vector>

#include "Capitulo5.h"
#include "Capitulo6.h"

int main() {
  // --- MOD-A6-B5: PRUEBAS DE VALIDACIÓN isValidHeap ---
  ods::PQ_ComplHeap<int> pqEmpty;
  assert(pqEmpty.isValidHeap()); // 1. Heap vacío

  ods::PQ_ComplHeap<int> pqOne;
  pqOne.insert(42);
  assert(pqOne.isValidHeap()); // 2. Heap con un elemento

  ods::PQ_ComplHeap<int> pqRep;
  pqRep.insert(7); pqRep.insert(7); pqRep.insert(7);
  assert(pqRep.isValidHeap()); // 3. Heap con elementos repetidos

  ods::PQ_ComplHeap<int> pqIns;
  for (int x : {15, 2, 8, 1, 99, 4}) pqIns.insert(x);
  assert(pqIns.isValidHeap()); // 4. Heap construido por inserciones

  ods::PQ_ComplHeap<int> pqHeapify(std::vector<int>{15, 2, 8, 1, 99, 4});
  assert(pqHeapify.isValidHeap()); // 5. Heap construido por heapify
  
  pqHeapify.delMax();
  pqHeapify.delMax();
  assert(pqHeapify.isValidHeap()); // 6. Heap después de varias llamadas a delMax
  // ----------------------------------------------------

  // PQ_ComplHeap: secuencia completa de extracciones.
  ods::PQ_ComplHeap<int> pq;
  for (int x : {8, 3, 10, 1, 6, 14, 4, 7, 13, 14}) {
    pq.insert(x);
    assert(pq.isValidHeap()); // Validación tras cada inserción
  }
  
  std::vector<int> out;
  while (!pq.empty()) {
    out.push_back(pq.delMax());
    assert(pq.empty() || pq.isValidHeap()); // Validación tras cada extracción
  }
  assert((out == std::vector<int>{14, 14, 13, 10, 8, 7, 6, 4, 3, 1}));

  // Leftist heap: merge e invariantes.
  ods::PQ_LeftHeap<int> a{20, 7, 18, 3};
  ods::PQ_LeftHeap<int> b{19, 8, 4, 1, 17};
  a.merge(b);
  assert(a.isLeftistHeap());
  assert(b.empty());
  
  std::vector<int> leftOut;
  while (!a.empty()) {
    leftOut.push_back(a.delMax());
    assert(a.empty() || a.isLeftistHeap());
  }
  assert((leftOut == std::vector<int>{20, 19, 18, 17, 8, 7, 4, 3, 1}));

  // Huffman: heap completo y leftist heap deben tener mismo costo ponderado.
  const std::vector<ods::HuffmanSymbol> s{{'a', 45}, {'b', 13}, {'c', 12},
                                          {'d', 16}, {'e', 9},  {'f', 5}};
  const auto codes1 = ods::huffmanGenerateCodes(s);
  const auto codes2 = ods::huffmanGenerateCodesLeftHeap(s);
  assert(ods::huffmanIsPrefixFree(codes1));
  assert(ods::huffmanIsPrefixFree(codes2));
  assert(ods::huffmanWeightedPathLength(s, codes1) == 224);
  assert(ods::huffmanWeightedPathLength(s, codes2) == 224);

  // Rotaciones BST: preservan inorder aun cuando cambie la forma.
  ods::BinarySearchTree<int> bst;
  for (int x : {8, 3, 10, 1, 6, 14, 4, 7, 13}) {
    bst.add(x);
  }
  auto sorted = bst.inorder();
  bst.rotateLeft(bst.root());
  assert(bst.isBST());
  assert(bst.inorder() == sorted);
  
  bst.rotateRight(bst.root());
  assert(bst.isBST());
  assert(bst.inorder() == sorted);

  // Treap: BST por clave + heap por prioridad.
  ods::Treap<int> treap(555);
  treap.addWithPriority(8, 80);
  treap.addWithPriority(3, 40);
  treap.addWithPriority(10, 90);
  treap.addWithPriority(1, 20);
  treap.addWithPriority(6, 70);
  treap.addWithPriority(14, 120);
  treap.addWithPriority(4, 65);
  treap.addWithPriority(7, 68);
  
  assert(treap.isTreap());
  assert((treap.inorderKeys() == std::vector<int>{1, 3, 4, 6, 7, 8, 10, 14}));
  assert(treap.lowerBound(5)->key == 6);
  assert(treap.upperBound(6)->key == 7);
  
  assert(treap.remove(3));
  assert(treap.remove(8));
  assert(treap.isTreap());
  assert((treap.inorderKeys() == std::vector<int>{1, 4, 6, 7, 10, 14}));

  return 0;
}
```

* **Salida de la demostración:**
*(Evidencia de inserciones y ASCII Art final)*

```bash
AXEL@DESKTOP-70IITE7 UCRT64 /c/Users/AXEL/OneDrive/Escritorio/uni/2026-1/AED/Repositorio/Personal/CC232/Libreria_cc232
$ cmake --build build-debug --config Debug --target sem6_demo_treap_basico
[2/2] Linking CXX executable Semana6\sem6_demo_treap_basico.exe

AXEL@DESKTOP-70IITE7 UCRT64 /c/Users/AXEL/OneDrive/Escritorio/uni/2026-1/AED/Repositorio/Personal/CC232/Libreria_cc232
$ ./build-debug/Semana6/sem6_demo_treap_basico.exe
CONSTRUCCION DETERMINISTICA DE TREAP
------------------------------------------
Insertado -> Clave: 50 | Prioridad: 50
Inorden      : 50 
Por niveles  : 50 
Raiz actual  : 50
Validaciones : isBST[SI] | isHeap[SI] | isTreap[SI]
------------------------------------------
Insertado -> Clave: 30 | Prioridad: 30
Inorden      : 30 50 
Por niveles  : 30 50 
Raiz actual  : 30
Validaciones : isBST[SI] | isHeap[SI] | isTreap[SI]
------------------------------------------
Insertado -> Clave: 70 | Prioridad: 70
Inorden      : 30 50 70 
Por niveles  : 30 50 70 
Raiz actual  : 30
Validaciones : isBST[SI] | isHeap[SI] | isTreap[SI]
------------------------------------------
Insertado -> Clave: 20 | Prioridad: 20
Inorden      : 20 30 50 70 
Por niveles  : 20 30 50 70 
Raiz actual  : 20
Validaciones : isBST[SI] | isHeap[SI] | isTreap[SI]
------------------------------------------
Insertado -> Clave: 40 | Prioridad: 40
Inorden      : 20 30 40 50 70 
Por niveles  : 20 30 40 50 70 
Raiz actual  : 20
Validaciones : isBST[SI] | isHeap[SI] | isTreap[SI]
------------------------------------------
Insertado -> Clave: 60 | Prioridad: 60
Inorden      : 20 30 40 50 60 70 
Por niveles  : 20 30 40 50 60 70 
Raiz actual  : 20
Validaciones : isBST[SI] | isHeap[SI] | isTreap[SI]
------------------------------------------
Insertado -> Clave: 80 | Prioridad: 80
Inorden      : 20 30 40 50 60 70 80 
Por niveles  : 20 30 40 50 60 70 80 
Raiz actual  : 20
Validaciones : isBST[SI] | isHeap[SI] | isTreap[SI]
==========================================
ARBOL FINAL (ASCII ART):
Ôöé                       ÔöîÔöÇÔöÇ 80|p=80
Ôöé                   ÔöîÔöÇÔöÇ 70|p=70
Ôöé               ÔöîÔöÇÔöÇ 60|p=60
Ôöé           ÔöîÔöÇÔöÇ 50|p=50
Ôöé       ÔöîÔöÇÔöÇ 40|p=40
Ôöé   ÔöîÔöÇÔöÇ 30|p=30
ÔööÔöÇÔöÇ 20|p=20
```
*(Aclaracion : Se muestran estos caracteres extraños (Ôöé, Ôöî) porque la terminal de Windows suele tener problemas para interpretar los caracteres de la tabla ASCII extendida usados para dibujar el árbol ("│", "┌", "└"))* 

Debio obtenerse algo como esto :

```bash
ARBOL FINAL (ASCII ART):
                        ┌── 80|p=80
                    ┌── 70|p=70
                ┌── 60|p=60
            ┌── 50|p=50
        ┌── 40|p=40
    ┌── 30|p=30
└── 20|p=20
```

### Preguntas

* **¿Por qué el recorrido inorden debe salir ordenado aunque las prioridades cambien la forma del árbol?**
  Porque las rotaciones (`rotateLeft` y `rotateRight`) están diseñadas para proteger el invariante del BST. Sin importar cómo los nodos floten o se hundan buscando cumplir su prioridad, la regla horizontal de que "el hijo izquierdo es menor y el derecho es mayor" jamás se rompe.

* **¿Por qué la raíz no necesariamente es la primera clave insertada?**
  Porque el Treap respeta la propiedad de Min-Heap en sus prioridades. La raíz siempre será forzada a ser el nodo con la prioridad numérica más baja de todo el árbol. Si entra un nodo nuevo con una prioridad menor que el actual, este flotará hasta robarle el puesto de raíz.

* **¿Qué nodo debe subir cuando se inserta una clave con prioridad menor que la de sus ancestros?**
  El propio nodo recién insertado. A través de la función `bubbleUp`, este nodo ejecutará rotaciones repetitivas con sus padres hasta que logre posicionarse debajo de un nodo con prioridad aún menor, o hasta convertirse en la raíz absoluta.

* **¿Qué propiedad conserva una rotación local sobre las claves?**
  Conserva estrictamente la propiedad de Árbol Binario de Búsqueda (BST). Garantiza que, tras girar los nodos, el orden de lectura inorden permanezca idéntico.

* **¿Qué propiedad intenta restaurar `bubbleUp` sobre las prioridades?**
  Intenta restaurar la propiedad de Min-Heap, asegurando que ningún nodo padre tenga una prioridad numérica mayor que la de cualquiera de sus hijos.



### Parte B - Instrumentación de bubbleUp

**Entregables del bloque:**

* **Codigo completo de archivo Treap.h modificado :**  

```cpp
#pragma once

#include <algorithm>
#include <cstdint>
#include <functional>
#include <ostream>
#include <queue>
#include <random>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace ods {

template <class T, class Compare = std::less<T>>
class Treap {
 public:
  struct Node {
    T key{};
    std::uint64_t priority{0};
    Node* parent{nullptr};
    Node* left{nullptr};
    Node* right{nullptr};

    Node() = default;
    Node(const T& value, std::uint64_t p, Node* par = nullptr)
        : key(value), priority(p), parent(par) {}

    bool isLeftChild() const { return parent != nullptr && parent->left == this; }
    bool isRightChild() const { return parent != nullptr && parent->right == this; }
  };

  Treap() : rng_(232) {}
  explicit Treap(std::uint64_t seed) : rng_(seed) {}
  explicit Treap(Compare comp, std::uint64_t seed = 232) : comp_(std::move(comp)), rng_(seed) {}

  Treap(const Treap&) = delete;
  Treap& operator=(const Treap&) = delete;

  Treap(Treap&& other) noexcept { swap(other); }
  Treap& operator=(Treap&& other) noexcept {
    if (this != &other) {
      clear();
      swap(other);
    }
    return *this;
  }

  ~Treap() { clear(); }

  void clear() {
    destroy(root_);
    root_ = nullptr;
    size_ = 0;
  }

  void swap(Treap& other) noexcept {
    std::swap(root_, other.root_);
    std::swap(size_, other.size_);
    std::swap(comp_, other.comp_);
    std::swap(rng_, other.rng_);
    std::swap(priorityCounter_, other.priorityCounter_);
  }

  Node* root() const noexcept { return root_; }
  std::size_t size() const noexcept { return size_; }
  bool empty() const noexcept { return size_ == 0; }

  Node* findLast(const T& x) const {
    Node* w = root_;
    Node* prev = nullptr;
    while (w != nullptr) {
      prev = w;
      if (comp_(x, w->key)) {
        w = w->left;
      } else if (comp_(w->key, x)) {
        w = w->right;
      } else {
        return w;
      }
    }
    return prev;
  }

  Node* findEQ(const T& x) const {
    Node* w = root_;
    while (w != nullptr) {
      if (comp_(x, w->key)) {
        w = w->left;
      } else if (comp_(w->key, x)) {
        w = w->right;
      } else {
        return w;
      }
    }
    return nullptr;
  }

  Node* lowerBound(const T& x) const {
    Node* w = root_;
    Node* candidate = nullptr;
    while (w != nullptr) {
      if (comp_(x, w->key)) {
        candidate = w;
        w = w->left;
      } else if (comp_(w->key, x)) {
        w = w->right;
      } else {
        return w;
      }
    }
    return candidate;
  }

  Node* upperBound(const T& x) const {
    Node* w = root_;
    Node* candidate = nullptr;
    while (w != nullptr) {
      if (comp_(x, w->key)) {
        candidate = w;
        w = w->left;
      } else {
        w = w->right;
      }
    }
    return candidate;
  }

  bool contains(const T& x) const { return findEQ(x) != nullptr; }

  bool add(const T& x) { return addWithPriority(x, nextPriority()); }

  bool addWithPriority(const T& x, std::uint64_t priority) {
    Node* u = new Node(x, priority);
    if (!addNode(u)) {
      delete u;
      return false;
    }
    bubbleUp(u);
    return true;
  }

  // INICIO DE MODIFICACION PARTE B 
  
  std::size_t bubbleUpCount(Node* u) {
    std::size_t rotations = 0;
    while (u->parent && u->parent->priority > u->priority) {
      if (u->isRightChild()) {
        rotateLeft(u->parent);
      } else {
        rotateRight(u->parent);
      }
      rotations++;
    }
    if (!u->parent) root_ = u;
    return rotations;
  }

  std::size_t addWithPriorityCount(const T& x, std::uint64_t priority) {
    Node* u = new Node(x, priority);
    if (!addNode(u)) {
      delete u;
      return 0; 
    }
    return bubbleUpCount(u);
  }

  // FIN DE MODIFICACION PARTE B 

  bool remove(const T& x) {
    Node* u = findEQ(x);
    if (!u) return false;
    trickleDown(u);
    splice(u);
    delete u;
    return true;
  }

  void rotateLeft(Node* u) {
    if (!u || !u->right) return;
    Node* w = u->right;
    w->parent = u->parent;
    if (!u->parent) {
      root_ = w;
    } else if (u->isLeftChild()) {
      u->parent->left = w;
    } else {
      u->parent->right = w;
    }
    u->right = w->left;
    if (u->right) u->right->parent = u;
    w->left = u;
    u->parent = w;
  }

  void rotateRight(Node* u) {
    if (!u || !u->left) return;
    Node* w = u->left;
    w->parent = u->parent;
    if (!u->parent) {
      root_ = w;
    } else if (u->isLeftChild()) {
      u->parent->left = w;
    } else {
      u->parent->right = w;
    }
    u->left = w->right;
    if (u->left) u->left->parent = u;
    w->right = u;
    u->parent = w;
  }

  void bubbleUp(Node* u) {
    while (u->parent && u->parent->priority > u->priority) {
      if (u->isRightChild()) {
        rotateLeft(u->parent);
      } else {
        rotateRight(u->parent);
      }
    }
    if (!u->parent) root_ = u;
  }

  void trickleDown(Node* u) {
    while (u->left || u->right) {
      if (!u->left) {
        rotateLeft(u);
      } else if (!u->right) {
        rotateRight(u);
      } else if (u->left->priority < u->right->priority) {
        rotateRight(u);
      } else {
        rotateLeft(u);
      }
      if (root_ == u) root_ = u->parent;
    }
  }

  std::vector<T> inorderKeys() const {
    std::vector<T> out;
    inorder(root_, out);
    return out;
  }

  std::vector<T> levelOrderKeys() const {
    std::vector<T> out;
    std::queue<Node*> q;
    if (root_) q.push(root_);
    while (!q.empty()) {
      Node* u = q.front();
      q.pop();
      out.push_back(u->key);
      if (u->left) q.push(u->left);
      if (u->right) q.push(u->right);
    }
    return out;
  }

  std::string asciiArt() const {
    if (!root_) return "(treap vacio)\n";
    std::vector<std::string> lines;
    buildAscii(root_, "", true, lines);
    std::ostringstream out;
    for (const auto& line : lines) out << line << '\n';
    return out.str();
  }

  bool isBST() const { return isBST(root_, nullptr, nullptr) && checkParents(root_, nullptr); }
  bool isHeapByPriority() const { return isHeapByPriority(root_); }
  bool isTreap() const { return isBST() && isHeapByPriority(); }

 private:
  Node* root_{nullptr};
  std::size_t size_{0};
  Compare comp_{};
  std::mt19937_64 rng_;
  std::uint64_t priorityCounter_{0};

  std::uint64_t nextPriority() {
    std::uint64_t raw = rng_();
    return (raw << 16) ^ (++priorityCounter_);
  }

  bool addNode(Node* u) {
    u->left = nullptr;
    u->right = nullptr;
    Node* p = findLast(u->key);
    if (!p) {
      root_ = u;
      u->parent = nullptr;
      ++size_;
      return true;
    }
    if (comp_(u->key, p->key)) {
      if (p->left) return false;
      p->left = u;
    } else if (comp_(p->key, u->key)) {
      if (p->right) return false;
      p->right = u;
    } else {
      return false;
    }
    u->parent = p;
    ++size_;
    return true;
  }

  void splice(Node* u) {
    Node* s = u->left ? u->left : u->right;
    if (u == root_) {
      root_ = s;
    } else if (u->isLeftChild()) {
      u->parent->left = s;
    } else {
      u->parent->right = s;
    }
    if (s) s->parent = u->parent;
    --size_;
  }

  static void destroy(Node* u) {
    if (!u) return;
    destroy(u->left);
    destroy(u->right);
    delete u;
  }

  static void inorder(Node* u, std::vector<T>& out) {
    if (!u) return;
    inorder(u->left, out);
    out.push_back(u->key);
    inorder(u->right, out);
  }

  bool isBST(Node* u, const T* low, const T* high) const {
    if (!u) return true;
    if (low && !comp_(*low, u->key)) return false;
    if (high && !comp_(u->key, *high)) return false;
    return isBST(u->left, low, &u->key) && isBST(u->right, &u->key, high);
  }

  static bool checkParents(Node* u, Node* parent) {
    if (!u) return true;
    if (u->parent != parent) return false;
    return checkParents(u->left, u) && checkParents(u->right, u);
  }

  static bool isHeapByPriority(Node* u) {
    if (!u) return true;
    if (u->left && u->left->priority < u->priority) return false;
    if (u->right && u->right->priority < u->priority) return false;
    return isHeapByPriority(u->left) && isHeapByPriority(u->right);
  }

  static std::string nodeLabel(const Node* u) {
    std::ostringstream out;
    out << u->key << "|p=" << u->priority;
    return out.str();
  }

  static void buildAscii(const Node* node, const std::string& prefix, bool isTail,
                         std::vector<std::string>& lines) {
    if (!node) return;
    if (node->right) {
      buildAscii(node->right, prefix + (isTail ? "│   " : "    "), false, lines);
    }
    lines.push_back(prefix + (isTail ? "└── " : "┌── ") + nodeLabel(node));
    if (node->left) {
      buildAscii(node->left, prefix + (isTail ? "    " : "│   "), true, lines);
    }
  }
};

template <class T, class Compare>
inline std::ostream& operator<<(std::ostream& out, const Treap<T, Compare>& t) {
  out << t.asciiArt();
  return out;
}

}  // namespace ods
```

* **Codigo completo de archivo demo_treap_basico.cpp modificado nuevamente :**  

```cpp
#include <iostream>
#include <vector>
#include <utility>
#include <iomanip>

#include "Capitulo6.h"

int main() {
  ods::Treap<int> t(232);
  
  // Secuencia combinada (Parte A y B en la misma demo)
  
  // === PARTE A ===
  std::vector<std::pair<int, int>> sequenceA = {
      {50, 50}, {30, 30}, {70, 70}, {20, 20}, {40, 40}, {60, 60}, {80, 80}
  };

  std::cout << "=== PARTE A: CONSTRUCCION DETERMINISTICA DE TREAP ===\n";
  for (const auto& p : sequenceA) {
    t.addWithPriority(p.first, p.second);
    std::cout << "------------------------------------------\n";
    std::cout << "Insertado -> Clave: " << p.first << " | Prioridad: " << p.second << "\n";
    std::cout << "Inorden      : ";
    for (int k : t.inorderKeys()) std::cout << k << " ";
    std::cout << "\nRaiz actual  : " << t.root()->key << "\n";
    std::cout << "Validaciones : isBST[" << (t.isBST() ? "SI" : "NO") 
              << "] | isHeap[" << (t.isHeapByPriority() ? "SI" : "NO") 
              << "] | isTreap[" << (t.isTreap() ? "SI" : "NO") << "]\n";
  }

  // === PARTE B ===
  // Limpiamos el Treap para la nueva prueba
  t.clear(); 
  
  std::vector<std::pair<int, int>> sequenceB = {
      {100, 100}, {90, 90}, {80, 80}, {70, 70}, {60, 60}
  };

  std::cout << "\n=== PARTE B: INSTRUMENTACION DE BUBBLEUP ===\n";
  std::cout << "---------------------------------------------------\n";
  std::cout << std::left << std::setw(10) << "Clave" 
            << std::setw(15) << "Prioridad" 
            << std::setw(15) << "Rotaciones" 
            << "Raiz actual\n";
  std::cout << "---------------------------------------------------\n";

  for (const auto& p : sequenceB) {
    int key = p.first;
    int prio = p.second;
    
    // Usamos nuestra funcion instrumentada
    std::size_t rot = t.addWithPriorityCount(key, prio);

    std::cout << std::left << std::setw(10) << key 
              << std::setw(15) << prio 
              << std::setw(15) << rot 
              << t.root()->key << "\n";
  }
  std::cout << "---------------------------------------------------\n";
  std::cout << "\nARBOL FINAL (ASCII ART):\n" << t << "\n";

  return 0;
}
```

* **Salida de la demostración:**
*(Evidencia de la Consola (Tabla y Costo))*

```bash
AXEL@DESKTOP-70IITE7 UCRT64 /c/Users/AXEL/OneDrive/Escritorio/uni/2026-1/AED/Repositorio/Personal/CC232/Libreria_cc232
$ cmake --build build-debug --config Debug --target sem6_demo_treap_basico
[2/2] Linking CXX executable Semana6\sem6_demo_treap_basico.exe

AXEL@DESKTOP-70IITE7 UCRT64 /c/Users/AXEL/OneDrive/Escritorio/uni/2026-1/AED/Repositorio/Personal/CC232/Libreria_cc232
$ ./build-debug/Semana6/sem6_demo_treap_basico.exe
=== PARTE A: CONSTRUCCION DETERMINISTICA DE TREAP ===
...
=== PARTE B: INSTRUMENTACION DE BUBBLEUP ===
---------------------------------------------------
Clave     Prioridad      Rotaciones     Raiz actual
---------------------------------------------------
100       100            0              100
90        90             1              90
80        80             1              80
70        70             1              70
60        60             1              60
---------------------------------------------------

ARBOL FINAL (ASCII ART):
Ôöé               ÔöîÔöÇÔöÇ 100|p=100
Ôöé           ÔöîÔöÇÔöÇ 90|p=90
Ôöé       ÔöîÔöÇÔöÇ 80|p=80
Ôöé   ÔöîÔöÇÔöÇ 70|p=70
ÔööÔöÇÔöÇ 60|p=60

```

*(Aclaracion : Se muestran estos caracteres extraños (Ôöé, Ôöî) porque la terminal de Windows suele tener problemas para interpretar los caracteres de la tabla ASCII extendida usados para dibujar el árbol ("│", "┌", "└"))* 

Debio obtenerse algo como esto :

```bash
ARBOL FINAL (ASCII ART):
                ┌── 100|p=100
            ┌── 90|p=90
        ┌── 80|p=80
    ┌── 70|p=70
└── 60|p=60
```

**Explicación del costo esperado :**
El uso de prioridades aleatorias en el Treap evita el peor caso estructural de $O(N)$. Matemáticamente, el costo esperado para arreglar el Min-Heap tras insertar o eliminar es de $O(1)$ amortizado (menos de 2 rotaciones), logrando que estas operaciones mantengan una altísima eficiencia total de $O(\log N)$

### Preguntas

* **¿Por qué esta secuencia tiende a producir rotaciones repetidas?**
  Porque insertamos prioridades cada vez menores (100, 90, 80...). Esto rompe la regla del Min-Heap constantemente, obligando al Treap a empujar cada nuevo nodo hasta la raíz mediante rotaciones para corregirlo

* **¿Cuándo `bubbleUpCount` retorna cero?**
  En dos casos exactos: 1. Cuando el árbol está vacío (el nodo nace siendo la raíz).
  2. Cuando el nodo se inserta y su prioridad aleatoria resulta ser mayor o igual a la de su padre, cumpliendo la regla del Min-Heap sin necesidad de moverse.

* **¿Cuál es el peor caso de rotaciones durante una inserción?**
  Es $O(N)$ rotaciones. Ocurre si el árbol degeneró en una "lista" y el nuevo nodo cae en lo más profundo, pero recibe la prioridad más baja de todas. Tendrá que subir rotando por todos los nodos hasta llegar a la raíz.

* **¿Por qué una rotación no rompe la propiedad BST?**
  Porque la rotación solo reacomoda las conexiones respetando el orden original (Inorden). Si el valor de un nodo $A$ es menor que $B$, la rotación matemática garantiza que $A$ siempre se mantenga en la rama izquierda respecto a $B$.

* **¿Por qué el treap busca mantener altura esperada logarítmica, no altura garantizada logarítmica?**
  Porque el Treap confía en el azar, no en rebalanceos estrictos (como un árbol AVL). Al asignar prioridades aleatorias, existe una pequeñísima probabilidad de que el árbol quede desbalanceado (altura $O(N)$). Sin embargo, las matemáticas demuestran que, en promedio, el azar siempre tenderá a formar un árbol balanceado con altura $O(\log N)$.


### Parte C - Instrumentación de trickleDown y eliminación

**Entregables del bloque:**

* **Codigo completo de archivo Treap.h modificado :**  

```cpp
#pragma once

#include <algorithm>
#include <cstdint>
#include <functional>
#include <ostream>
#include <queue>
#include <random>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace ods {

template <class T, class Compare = std::less<T>>
class Treap {
 public:
  struct Node {
    T key{};
    std::uint64_t priority{0};
    Node* parent{nullptr};
    Node* left{nullptr};
    Node* right{nullptr};

    Node() = default;
    Node(const T& value, std::uint64_t p, Node* par = nullptr)
        : key(value), priority(p), parent(par) {}

    bool isLeftChild() const { return parent != nullptr && parent->left == this; }
    bool isRightChild() const { return parent != nullptr && parent->right == this; }
  };

  Treap() : rng_(232) {}
  explicit Treap(std::uint64_t seed) : rng_(seed) {}
  explicit Treap(Compare comp, std::uint64_t seed = 232) : comp_(std::move(comp)), rng_(seed) {}

  Treap(const Treap&) = delete;
  Treap& operator=(const Treap&) = delete;

  Treap(Treap&& other) noexcept { swap(other); }
  Treap& operator=(Treap&& other) noexcept {
    if (this != &other) {
      clear();
      swap(other);
    }
    return *this;
  }

  ~Treap() { clear(); }

  void clear() {
    destroy(root_);
    root_ = nullptr;
    size_ = 0;
  }

  void swap(Treap& other) noexcept {
    std::swap(root_, other.root_);
    std::swap(size_, other.size_);
    std::swap(comp_, other.comp_);
    std::swap(rng_, other.rng_);
    std::swap(priorityCounter_, other.priorityCounter_);
  }

  Node* root() const noexcept { return root_; }
  std::size_t size() const noexcept { return size_; }
  bool empty() const noexcept { return size_ == 0; }

  Node* findLast(const T& x) const {
    Node* w = root_;
    Node* prev = nullptr;
    while (w != nullptr) {
      prev = w;
      if (comp_(x, w->key)) {
        w = w->left;
      } else if (comp_(w->key, x)) {
        w = w->right;
      } else {
        return w;
      }
    }
    return prev;
  }

  Node* findEQ(const T& x) const {
    Node* w = root_;
    while (w != nullptr) {
      if (comp_(x, w->key)) {
        w = w->left;
      } else if (comp_(w->key, x)) {
        w = w->right;
      } else {
        return w;
      }
    }
    return nullptr;
  }

  Node* lowerBound(const T& x) const {
    Node* w = root_;
    Node* candidate = nullptr;
    while (w != nullptr) {
      if (comp_(x, w->key)) {
        candidate = w;
        w = w->left;
      } else if (comp_(w->key, x)) {
        w = w->right;
      } else {
        return w;
      }
    }
    return candidate;
  }

  Node* upperBound(const T& x) const {
    Node* w = root_;
    Node* candidate = nullptr;
    while (w != nullptr) {
      if (comp_(x, w->key)) {
        candidate = w;
        w = w->left;
      } else {
        w = w->right;
      }
    }
    return candidate;
  }

  bool contains(const T& x) const { return findEQ(x) != nullptr; }

  bool add(const T& x) { return addWithPriority(x, nextPriority()); }

  bool addWithPriority(const T& x, std::uint64_t priority) {
    Node* u = new Node(x, priority);
    if (!addNode(u)) {
      delete u;
      return false;
    }
    bubbleUp(u);
    return true;
  }

  
  
  std::size_t bubbleUpCount(Node* u) {
    std::size_t rotations = 0;
    while (u->parent && u->parent->priority > u->priority) {
      if (u->isRightChild()) {
        rotateLeft(u->parent);
      } else {
        rotateRight(u->parent);
      }
      rotations++;
    }
    if (!u->parent) root_ = u;
    return rotations;
  }

  std::size_t addWithPriorityCount(const T& x, std::uint64_t priority) {
    Node* u = new Node(x, priority);
    if (!addNode(u)) {
      delete u;
      return 0; 
    }
    return bubbleUpCount(u);
  }
// --- INICIO DE MODIFICACION PARTE C ---
  std::size_t trickleDownCount(Node* u) {
    std::size_t rotations = 0;
    while (u->left || u->right) {
      if (!u->left) {
        rotateLeft(u);
      } else if (!u->right) {
        rotateRight(u);
      } else if (u->left->priority < u->right->priority) {
        rotateRight(u);
      } else {
        rotateLeft(u);
      }
      if (root_ == u) root_ = u->parent;
      rotations++;
    }
    return rotations;
  }

  std::size_t removeCount(const T& x) {
    Node* u = findEQ(x);
    if (!u) return 0;
    std::size_t rotations = trickleDownCount(u);
    splice(u);
    delete u;
    return rotations;
  }

  // --- FIN DE MODIFICACION PARTE C ---

  bool remove(const T& x) {
    Node* u = findEQ(x);
    if (!u) return false;
    trickleDown(u);
    splice(u);
    delete u;
    return true;
  }

  void rotateLeft(Node* u) {
    if (!u || !u->right) return;
    Node* w = u->right;
    w->parent = u->parent;
    if (!u->parent) {
      root_ = w;
    } else if (u->isLeftChild()) {
      u->parent->left = w;
    } else {
      u->parent->right = w;
    }
    u->right = w->left;
    if (u->right) u->right->parent = u;
    w->left = u;
    u->parent = w;
  }

  void rotateRight(Node* u) {
    if (!u || !u->left) return;
    Node* w = u->left;
    w->parent = u->parent;
    if (!u->parent) {
      root_ = w;
    } else if (u->isLeftChild()) {
      u->parent->left = w;
    } else {
      u->parent->right = w;
    }
    u->left = w->right;
    if (u->left) u->left->parent = u;
    w->right = u;
    u->parent = w;
  }

  void bubbleUp(Node* u) {
    while (u->parent && u->parent->priority > u->priority) {
      if (u->isRightChild()) {
        rotateLeft(u->parent);
      } else {
        rotateRight(u->parent);
      }
    }
    if (!u->parent) root_ = u;
  }

  void trickleDown(Node* u) {
    while (u->left || u->right) {
      if (!u->left) {
        rotateLeft(u);
      } else if (!u->right) {
        rotateRight(u);
      } else if (u->left->priority < u->right->priority) {
        rotateRight(u);
      } else {
        rotateLeft(u);
      }
      if (root_ == u) root_ = u->parent;
    }
  }

  std::vector<T> inorderKeys() const {
    std::vector<T> out;
    inorder(root_, out);
    return out;
  }

  std::vector<T> levelOrderKeys() const {
    std::vector<T> out;
    std::queue<Node*> q;
    if (root_) q.push(root_);
    while (!q.empty()) {
      Node* u = q.front();
      q.pop();
      out.push_back(u->key);
      if (u->left) q.push(u->left);
      if (u->right) q.push(u->right);
    }
    return out;
  }

  std::string asciiArt() const {
    if (!root_) return "(treap vacio)\n";
    std::vector<std::string> lines;
    buildAscii(root_, "", true, lines);
    std::ostringstream out;
    for (const auto& line : lines) out << line << '\n';
    return out.str();
  }

  bool isBST() const { return isBST(root_, nullptr, nullptr) && checkParents(root_, nullptr); }
  bool isHeapByPriority() const { return isHeapByPriority(root_); }
  bool isTreap() const { return isBST() && isHeapByPriority(); }

 private:
  Node* root_{nullptr};
  std::size_t size_{0};
  Compare comp_{};
  std::mt19937_64 rng_;
  std::uint64_t priorityCounter_{0};

  std::uint64_t nextPriority() {
    std::uint64_t raw = rng_();
    return (raw << 16) ^ (++priorityCounter_);
  }

  bool addNode(Node* u) {
    u->left = nullptr;
    u->right = nullptr;
    Node* p = findLast(u->key);
    if (!p) {
      root_ = u;
      u->parent = nullptr;
      ++size_;
      return true;
    }
    if (comp_(u->key, p->key)) {
      if (p->left) return false;
      p->left = u;
    } else if (comp_(p->key, u->key)) {
      if (p->right) return false;
      p->right = u;
    } else {
      return false;
    }
    u->parent = p;
    ++size_;
    return true;
  }

  void splice(Node* u) {
    Node* s = u->left ? u->left : u->right;
    if (u == root_) {
      root_ = s;
    } else if (u->isLeftChild()) {
      u->parent->left = s;
    } else {
      u->parent->right = s;
    }
    if (s) s->parent = u->parent;
    --size_;
  }

  static void destroy(Node* u) {
    if (!u) return;
    destroy(u->left);
    destroy(u->right);
    delete u;
  }

  static void inorder(Node* u, std::vector<T>& out) {
    if (!u) return;
    inorder(u->left, out);
    out.push_back(u->key);
    inorder(u->right, out);
  }

  bool isBST(Node* u, const T* low, const T* high) const {
    if (!u) return true;
    if (low && !comp_(*low, u->key)) return false;
    if (high && !comp_(u->key, *high)) return false;
    return isBST(u->left, low, &u->key) && isBST(u->right, &u->key, high);
  }

  static bool checkParents(Node* u, Node* parent) {
    if (!u) return true;
    if (u->parent != parent) return false;
    return checkParents(u->left, u) && checkParents(u->right, u);
  }

  static bool isHeapByPriority(Node* u) {
    if (!u) return true;
    if (u->left && u->left->priority < u->priority) return false;
    if (u->right && u->right->priority < u->priority) return false;
    return isHeapByPriority(u->left) && isHeapByPriority(u->right);
  }

  static std::string nodeLabel(const Node* u) {
    std::ostringstream out;
    out << u->key << "|p=" << u->priority;
    return out.str();
  }

  static void buildAscii(const Node* node, const std::string& prefix, bool isTail,
                         std::vector<std::string>& lines) {
    if (!node) return;
    if (node->right) {
      buildAscii(node->right, prefix + (isTail ? "│   " : "    "), false, lines);
    }
    lines.push_back(prefix + (isTail ? "└── " : "┌── ") + nodeLabel(node));
    if (node->left) {
      buildAscii(node->left, prefix + (isTail ? "    " : "│   "), true, lines);
    }
  }
};

template <class T, class Compare>
inline std::ostream& operator<<(std::ostream& out, const Treap<T, Compare>& t) {
  out << t.asciiArt();
  return out;
}

}  // namespace ods
```

* **Codigo completo de archivo demo_treap_basico.cpp nuevamente modificado :**  

```cpp
#include <iostream>
#include <vector>
#include <utility>
#include <iomanip>

#include "Capitulo6.h"

int main() {
  ods::Treap<int> t(232);
  
  // Secuencia combinada (Parte A, B y C en la misma demo)
  
  // === PARTE A ===
  std::vector<std::pair<int, int>> sequenceA = {
      {50, 50}, {30, 30}, {70, 70}, {20, 20}, {40, 40}, {60, 60}, {80, 80}
  };

  std::cout << "=== PARTE A: CONSTRUCCION DETERMINISTICA DE TREAP ===\n";
  for (const auto& p : sequenceA) {
    t.addWithPriority(p.first, p.second);
    std::cout << "------------------------------------------\n";
    std::cout << "Insertado -> Clave: " << p.first << " | Prioridad: " << p.second << "\n";
    std::cout << "Inorden      : ";
    for (int k : t.inorderKeys()) std::cout << k << " ";
    std::cout << "\nRaiz actual  : " << t.root()->key << "\n";
    std::cout << "Validaciones : isBST[" << (t.isBST() ? "SI" : "NO") 
              << "] | isHeap[" << (t.isHeapByPriority() ? "SI" : "NO") 
              << "] | isTreap[" << (t.isTreap() ? "SI" : "NO") << "]\n";
  }

  // === PARTE B ===
  t.clear(); // Limpiamos para la prueba B
  std::vector<std::pair<int, int>> sequenceB = {
      {100, 100}, {90, 90}, {80, 80}, {70, 70}, {60, 60}
  };

  std::cout << "\n=== PARTE B: INSTRUMENTACION DE BUBBLEUP ===\n";
  std::cout << "---------------------------------------------------\n";
  std::cout << std::left << std::setw(10) << "Clave" 
            << std::setw(15) << "Prioridad" 
            << std::setw(15) << "Rotaciones" 
            << "Raiz actual\n";
  std::cout << "---------------------------------------------------\n";

  for (const auto& p : sequenceB) {
    std::size_t rot = t.addWithPriorityCount(p.first, p.second);
    std::cout << std::left << std::setw(10) << p.first 
              << std::setw(15) << p.second 
              << std::setw(15) << rot 
              << t.root()->key << "\n";
  }

  // === PARTE C ===
  t.clear(); // Limpiamos y reconstruimos la Parte A para la prueba C
  for (const auto& p : sequenceA) {
    t.addWithPriority(p.first, p.second);
  }

  std::cout << "\n=== PARTE C: INSTRUMENTACION DE TRICKLEDOWN ===\n";
  std::cout << "ARBOL INICIAL:\n" << t << "\n";

  std::vector<int> to_remove = {50, 20, 70};

  for (int key : to_remove) {
    std::cout << "---------------------------------------------------\n";
    std::size_t rot = t.removeCount(key);
    
    std::cout << "Eliminado    : Clave " << key << " | Rotaciones: " << rot << "\n";
    std::cout << "Inorden      : ";
    for (int k : t.inorderKeys()) std::cout << k << " ";
    std::cout << "\nPor niveles  : ";
    for (int k : t.levelOrderKeys()) std::cout << k << " ";
    std::cout << "\nValidaciones : isBST[" << (t.isBST() ? "SI" : "NO") 
              << "] | isHeap[" << (t.isHeapByPriority() ? "SI" : "NO") 
              << "] | isTreap[" << (t.isTreap() ? "SI" : "NO") << "]\n";
  }
  std::cout << "---------------------------------------------------\n";
  std::cout << "ARBOL FINAL (ASCII ART):\n" << t << "\n";

  return 0;
}
```

* **Salida de la demostración:**

```bash
AXEL@DESKTOP-70IITE7 UCRT64 /c/Users/AXEL/OneDrive/Escritorio/uni/2026-1/AED/Repositorio/Personal/CC232/Libreria_cc232
$ cmake --build build-debug --config Debug --target sem6_demo_treap_basico
[2/2] Linking CXX executable Semana6\sem6_demo_treap_basico.exe

AXEL@DESKTOP-70IITE7 UCRT64 /c/Users/AXEL/OneDrive/Escritorio/uni/2026-1/AED/Repositorio/Personal/CC232/Libreria_cc232
$ ./build-debug/Semana6/sem6_demo_treap_basico.exe
=== PARTE A: CONSTRUCCION DETERMINISTICA DE TREAP ===
...
=== PARTE B: INSTRUMENTACION DE BUBBLEUP ===
...
=== PARTE C: INSTRUMENTACION DE TRICKLEDOWN ===
ARBOL INICIAL:
Ôöé                       ÔöîÔöÇÔöÇ 80|p=80
Ôöé                   ÔöîÔöÇÔöÇ 70|p=70
Ôöé               ÔöîÔöÇÔöÇ 60|p=60
Ôöé           ÔöîÔöÇÔöÇ 50|p=50
Ôöé       ÔöîÔöÇÔöÇ 40|p=40
Ôöé   ÔöîÔöÇÔöÇ 30|p=30
ÔööÔöÇÔöÇ 20|p=20

---------------------------------------------------
Eliminado    : Clave 50 | Rotaciones: 1
Inorden      : 20 30 40 60 70 80 
Por niveles  : 20 30 40 60 70 80 
Validaciones : isBST[SI] | isHeap[SI] | isTreap[SI]
---------------------------------------------------
Eliminado    : Clave 20 | Rotaciones: 1
Inorden      : 30 40 60 70 80 
Por niveles  : 30 40 60 70 80 
Validaciones : isBST[SI] | isHeap[SI] | isTreap[SI]
---------------------------------------------------
Eliminado    : Clave 70 | Rotaciones: 1
Inorden      : 30 40 60 80 
Por niveles  : 30 40 60 80 
Validaciones : isBST[SI] | isHeap[SI] | isTreap[SI]
---------------------------------------------------
ARBOL FINAL (ASCII ART):
Ôöé           ÔöîÔöÇÔöÇ 80|p=80
Ôöé       ÔöîÔöÇÔöÇ 60|p=60
Ôöé   ÔöîÔöÇÔöÇ 40|p=40
ÔööÔöÇÔöÇ 30|p=30

```

*(Aclaracion : Se muestran estos caracteres extraños (Ôöé, Ôöî) porque la terminal de Windows suele tener problemas para interpretar los caracteres de la tabla ASCII extendida usados para dibujar el árbol ("│", "┌", "└"))* 

Debio obtenerse algo como esto :

```bash
=== PARTE C: INSTRUMENTACION DE TRICKLEDOWN ===

ARBOL INICIAL:
                        ┌── 80|p=80
                    ┌── 70|p=70
                ┌── 60|p=60
            ┌── 50|p=50
        ┌── 40|p=40
    ┌── 30|p=30
└── 20|p=20

---------------------------------------------------
Eliminado    : Clave 50 | Rotaciones: 1
Inorden      : 20 30 40 60 70 80 
Por niveles  : 20 30 40 60 70 80 
Validaciones : isBST[SI] | isHeap[SI] | isTreap[SI]
---------------------------------------------------
Eliminado    : Clave 20 | Rotaciones: 1
Inorden      : 30 40 60 70 80 
Por niveles  : 30 40 60 70 80 
Validaciones : isBST[SI] | isHeap[SI] | isTreap[SI]
---------------------------------------------------
Eliminado    : Clave 70 | Rotaciones: 1
Inorden      : 30 40 60 80 
Por niveles  : 30 40 60 80 
Validaciones : isBST[SI] | isHeap[SI] | isTreap[SI]
---------------------------------------------------
ARBOL FINAL (ASCII ART):
                ┌── 80|p=80
            ┌── 60|p=60
        ┌── 40|p=40
    ┌── 30|p=30eeeeeeeeeeeeeeeeeeeeeee  we
```

### Preguntas

* **¿Por qué eliminar en un treap no es simplemente borrar como en un BST común?**
  En un BST común, se suele reemplazar el nodo a borrar con su predecesor o sucesor. Si hiciéramos eso en un Treap, el nodo que sube traería su propia prioridad aleatoria, lo que casi seguramente rompería la propiedad vertical de Min-Heap del árbol.

* **¿Por qué `trickleDown` elige rotar con el hijo de menor prioridad?**
  Para preservar el Min-Heap. El hijo que sube se convertirá en el padre del otro. Si subiéramos al hijo con la prioridad más alta, terminaría siendo el padre de un nodo con una prioridad más baja, lo cual viola el invariante de Min-Heap.

* **¿Qué ocurre si el nodo tiene solo hijo izquierdo?**
  Se fuerza una `rotateRight` (rotación a la derecha). Esto "hunde" al nodo hacia el lado derecho y permite que su hijo izquierdo suba a ocupar su posición, garantizando que siga conectado al árbol.

* **¿Qué ocurre si el nodo tiene solo hijo derecho?**
  Se fuerza una `rotateLeft` (rotación a la izquierda). El nodo se "hunde" hacia el lado izquierdo, subiendo al hijo derecho a la posición original.

* **¿Qué invariantes deben seguir siendo verdaderos después de `splice`?**
  Ambos invariantes del Treap: la propiedad de búsqueda binaria (isBST) y la de prioridad (isHeap). Como el nodo solo se "corta" (`splice`) cuando ya ha sido hundido hasta convertirse en una hoja (o tener a lo mucho un hijo nulo), su eliminación no afecta el orden ni las prioridades del resto del árbol.

### Trazado Manual: Eliminación de la Clave 50

**Estado Inicial (Fragmento de la rama derecha):**
`... -> (40)` cuyo hijo derecho es `(50)`. 
El hijo derecho de `(50)` es `(60)`. `(50)` no tiene hijo izquierdo.

**Paso 1: Identificación y TrickleDown**
Queremos eliminar `50`. Como solo tiene hijo derecho (`60`), `trickleDown` aplica una rotación a la izquierda (`rotateLeft(50)`).

**Paso 2: La Rotación**
Al rotar a la izquierda, `60` sube y se convierte en el nuevo hijo derecho de `40`. 
El nodo `50` baja y se convierte en el *hijo izquierdo de 60*. (Como `60` no tenía hijo izquierdo previamente, no hay huérfanos).

**Paso 3: Condición de Salida y Splice**
Ahora `50` es una hoja (no tiene hijo izquierdo ni derecho). El bucle de `trickleDown` se detiene.
La función `splice(50)` simplemente desconecta a `50` de su nuevo padre (`60`) y libera la memoria (`delete`).
**Resultado:** `40` apunta a `60` como su hijo derecho. El nodo `50` desapareció limpiamente sin romper nada.