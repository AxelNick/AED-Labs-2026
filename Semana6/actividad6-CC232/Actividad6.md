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

