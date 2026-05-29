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

