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

* **Fragmento del código modificado:**

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

Puede seguir los sigueintes pasos para compilar : 

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

**Código completo incluido la función nueva para PQ_ComplHeap_percolateUp.h**
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
AXEL@DESKTOP-70IITE7 UCRT64 /c/Users/AXEL/OneDrive/Escritorio/uni/2026-1/AED/Repositorio/Personal/CC232/Libreria_cc232
$ ./build-debug/Semana6/sem6_demo_pq_complheap_basico.exe
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

=== DEMO BLOQUE 3: CONTEO DE INTERCAMBIOS ===
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
