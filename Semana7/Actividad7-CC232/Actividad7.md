# Actividad 7 - CC232

### Estudiante
- **Nombre:** Axel Alberto Reyes Baldeón
- **Código:** 20200485B


## Bloque 1 - Diagnóstico inicial de la Semana 7

### Archivos revisados :
* `Libreria_cc232/Semana7/README.md`
* `Libreria_cc232/Semana7/CMakeLists.txt`
* `Libreria_cc232/Semana7/include/Capitulo7.h`

### Evidencia de ejecución

| Comando ejecutado | Resultado | Error | Interpretación |
| :--- | :--- | :--- | :--- |
| `cmake -S . -B build-debug -DCMAKE_BUILD_TYPE=Debug` | Configuración exitosa. Se generan los archivos de build. | Ninguno | CMake detectó el `CMakeLists.txt` correctamente y preparó el entorno para compilar la Semana 7. |
| `cmake --build build-debug` | Compilación al 100%. Generación de binarios y demos. | Ninguno | El código base proporcionado compila sin errores de sintaxis ni de enlazado. |
| `ctest --test-dir build-debug -R semana7 --output-on-failure` | 100% tests passed. | Ninguno | La implementación de referencia de AVL y Red-Black Tree viene correcta por defecto. Las pruebas públicas e internas pasan exitosamente. |

### Terminal 

```bash
AXEL@DESKTOP-70IITE7 UCRT64 /c/Users/AXEL/OneDrive/Escritorio/uni/2026-1/AED/Repositorio/Personal/CC232/Libreria_cc232
$ cmake -S . -B build-debug -DCMAKE_BUILD_TYPE=Debug
-- Configuring done (0.5s)
-- Generating done (0.3s)
-- Build files have been written to: C:/Users/AXEL/OneDrive/Escritorio/uni/2026-1/AED/Repositorio/Personal/CC232/Libreria_cc232/build-debug
```

```bash
AXEL@DESKTOP-70IITE7 UCRT64 /c/Users/AXEL/OneDrive/Escritorio/uni/2026-1/AED/Repositorio/Personal/CC232/Libreria_cc232
$ cmake --build build-debug --target \
  sem7_demo_avl_deng_core \
  sem7_demo_avl_compact_rotations \
  sem7_demo_bst_deng_vs_avl \
  sem7_demo_redblack_morin \
  sem7_demo_redblack_llrb \
  sem7_demo_compare_avl_vs_redblack \
  sem7_demo_compare_with_semana5 \
  sem7_demo_capitulo7_panorama \
  sem7_test_public \
  sem7_test_internal
[20/20] Linking CXX executable Semana7\sem7_test_internal.exe
```

```bash
AXEL@DESKTOP-70IITE7 UCRT64 /c/Users/AXEL/OneDrive/Escritorio/uni/2026-1/AED/Repositorio/Personal/CC232/Libreria_cc232
$ ctest --test-dir build-debug -R semana7 --output-on-failure
Test project C:/Users/AXEL/OneDrive/Escritorio/uni/2026-1/AED/Repositorio/Personal/CC232/Libreria_cc232/build-debug
    Start 24: semana7_public
1/2 Test #24: semana7_public ...................   Passed    0.10 sec
    Start 25: semana7_internal
2/2 Test #25: semana7_internal .................   Passed    0.10 sec

```

### Preguntas

#### 1. ¿Qué targets de demostración aparecen para Semana 7?
* `sem7_demo_avl_deng_core`
* `sem7_demo_avl_compact_rotations`
* `sem7_demo_bst_deng_vs_avl`
* `sem7_demo_redblack_morin`
* `sem7_demo_redblack_llrb`
* `sem7_demo_compare_avl_vs_redblack`
* `sem7_demo_compare_with_semana5`
* `sem7_demo_capitulo7_panorama`

#### 2. ¿Qué pruebas públicas e internas aparecen?
* **Públicas:** `sem7_test_public` (etiquetado en ctest como `semana7_public`)
* **Internas:** `sem7_test_internal` (etiquetado en ctest como `semana7_internal`)

#### 3. ¿Qué archivos incluye Capitulo7.h?
Incluye la base de nodos y árboles (`Entry.h`, `BinNode.h`, `BinTree.h`, `BinaryTree.h`, `BinarySearchTree.h`, `BST.h`) y las estructuras balanceadas (`AVL.h`, `RedBlackTree.h`, `AVLTreeCompact.h`, `RedBlackTreeLLRB.h`).

#### 4. ¿Qué relación conceptual hay entre Semana 5, Semana 6 y Semana 7?
Es una relación progresiva:
* **Semana 5:** Base de árboles binarios y de búsqueda (BST).
* **Semana 6:** Añade prioridades (Heaps) e introduce rotaciones con Treaps.
* **Semana 7:** Aplica las rotaciones vistas en la S6 al BST de la S5 para crear árboles que se autobalancean (AVL por altura, Red-Black por color) y evitar la degeneración lineal.

#### 5. ¿Por qué no es correcto decir que una carpeta "hereda" de otra carpeta?
Porque la herencia es un concepto estricto de Programación Orientada a Objetos que se aplica a clases, no a la estructura de directorios del sistema operativo. Una carpeta "continúa" o "reutiliza" código de otra, pero no hereda.

#### 6. ¿Qué clases sí usan herencia dentro del código?
* El AVL hereda del BST: `AVL<T, Compare> : public BST<T, Compare>`
* El Red-Black Tree hereda del BST genérico: `RedBlackTree<Node, T> : public BinarySearchTree<Node, T>`

#### 7. ¿Qué evidencia inicial obtuviste al ejecutar las pruebas sin modificar nada?
Que la implementación base entregada para los árboles AVL y Red-Black es correcta. El `ctest` reporta un 100% de éxito en `semana7_public` y `semana7_internal`, lo que indica que el código ya cumple con los invariantes antes de empezar a experimentar.


## Bloque 5 - Red-Black Tree: balance por colores

### Archivos revisados :
* `Semana7/include/RedBlackTree.h`
* `Semana7/include/BinarySearchTree.h`
* `Semana7/include/BinaryTree.cpp`
* `Semana7/demos/demo_redblack_morin.cpp`

**1. ¿Qué propiedad BST mantiene Red-Black Tree?**
Al heredar de `BinarySearchTree`, mantiene la propiedad de orden clásica: todos los elementos en el subárbol izquierdo son menores al nodo actual, y los del subárbol derecho son mayores (o viceversa según el comparador). Esto garantiza que el recorrido `inorder` devuelva los elementos ordenados.

**2. ¿Qué propiedades de color debe cumplir un Red-Black Tree?**
Según la validación de su método `verify()`, debe cumplir las siguientes reglas:
* Todo nodo es rojo (0) o negro (1).
* La raíz siempre es negra.
* Las hojas nulas / nodos centinela (`nil`) son negros.
* Si un nodo es rojo, sus dos hijos son obligatoriamente negros (no hay rojos consecutivos).
* Todos los caminos desde un nodo hasta sus hojas nulas contienen exactamente la misma cantidad de nodos negros.

**3. ¿Por qué la raíz debe terminar negra?**
Es una regla ancla para garantizar los límites matemáticos de la altura y simplificar las rotaciones. Al forzar que la raíz sea negra (como se ve en `addFixup` con `if (u == r) u->colour = black;`), se evita arrastrar una cascada de violaciones de color hacia arriba y se asegura que el conteo de la "altura negra" sea consistente.

**4. ¿Qué significa que no pueda haber dos nodos rojos consecutivos?**
Significa que un padre rojo no puede tener un hijo rojo (`u->left->colour == black && u->right->colour == black`). Este es el núcleo del balanceo: al intercalar obligatoriamente nodos negros, se impide que una rama crezca de forma degenerada (como una lista). Esto garantiza que el camino más largo del árbol nunca sea más del doble que el camino más corto.

**5. ¿Qué representa la altura negra?**
Representa la cantidad exacta de nodos negros que existen en el trayecto desde un nodo dado hasta cualquiera de sus descendientes nulos (`nil`). El código suma recursivamente los nodos negros y verifica que las ramas izquierda y derecha coincidan (`assert(dl == dr)`), confirmando así que el árbol está estructuralmente balanceado.