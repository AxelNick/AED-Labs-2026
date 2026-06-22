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

## Bloque 2 - BST como punto de partida

### Archivos revisados :
* `Semana7/include/BST.h`
* `Semana7/include/BinarySearchTree.h`
* `Semana7/demos/demo_compare_with_semana5.cpp`
* `Semana7/demos/demo_bst_deng_vs_avl.cpp`

**1. Define formalmente la propiedad BST.**
Un Árbol Binario de Búsqueda (BST) cumple con un invariante fundamental: para cualquier nodo \(N\), todos los valores en su subárbol izquierdo son estrictamente menores (o iguales, según la implementación) que el valor de \(N\), y todos los valores en su subárbol derecho son estrictamente mayores que el valor de \(N\).

**2. Explica por qué el recorrido inorder de un BST produce una secuencia ordenada.**
El recorrido `inorder` visita los nodos en el orden: Subárbol Izquierdo \(\rightarrow\) Nodo Actual \(\rightarrow\) Subárbol Derecho. Gracias a la propiedad BST, esto garantiza que siempre se visite primero a todos los elementos menores, luego al elemento intermedio, y finalmente a los mayores. Al aplicarse de forma recursiva, el resultado es una lectura secuencial de menor a mayor.

**3. Explica por qué insertar claves ordenadas puede producir un BST degenerado.**
Si se insertan datos que ya están ordenados (de forma ascendente o descendente), cada nuevo nodo será siempre mayor (o siempre menor) que el anterior. Esto provoca que todos los nodos se inserten como hijos derechos (o izquierdos) de forma consecutiva, dejando el otro lado del árbol completamente vacío. La estructura deja de ser un árbol bidimensional y se convierte esencialmente en una lista enlazada.

**4. Construye manualmente el BST resultante de insertar: 10, 20, 30, 40, 50, 60, 70.**
Al insertar la secuencia ordenada, el resultado es una degeneración lineal hacia la derecha:

```text
10
  \
   20
     \
      30
        \
         40
           \
            50
              \
               60
                 \
                  70
```

**5. Indica la altura del árbol anterior si no hay balanceo.**
Asumiendo que la raíz (10) se encuentra en el nivel 0, la altura de este árbol es de **6** (tiene 6 aristas desde la raíz hasta la hoja más profunda).

**6. Explica por qué una búsqueda en ese árbol puede costar $O(n)$ (Explicación del costo).**
En un BST, el costo de las operaciones de búsqueda depende directamente de la altura del árbol. Como en este caso el árbol degeneró en una estructura lineal (su altura es igual a $n-1$), buscar un elemento que está al final (como el 70) o uno que no existe requerirá recorrer secuencialmente todos los $n$ nodos. Por lo tanto, el costo de búsqueda, en el peor de los casos, deja de ser logarítmico y pasa a ser lineal: $O(n)$.

**7. Explica qué problema intenta resolver AVL.**
El árbol AVL resuelve la degeneración lineal imponiendo un invariante de balance por altura. Garantiza que la diferencia de alturas entre el subárbol izquierdo y derecho de cualquier nodo sea como máximo 1. Para mantener esta evidencia, utiliza rotaciones tras cada inserción o eliminación, asegurando de forma estricta que la altura del árbol se mantenga en $O(\log n)$ y las búsquedas sean eficientes.

**8. Explica qué problema intenta resolver Red-Black Tree.**
Al igual que el AVL, busca evitar la degeneración lineal y garantizar búsquedas en $O(\log n)$, pero utilizando un invariante de balance por colores (nodos rojos o negros) y una serie de reglas matemáticas sobre los caminos hacia las hojas nulas. Su balanceo es un poco menos estricto que el AVL (el camino más largo no supera el doble del más corto), lo que a menudo resulta en menos rotaciones al insertar o eliminar, favoreciendo escenarios con muchas modificaciones.

**9. Relación con la Semana 5.**
La Semana 7 es una extensión directa de la Semana 5. El código de la Semana 5 (`BinarySearchTree.h`) establece la base funcional del BST (búsqueda, inserción, invariante de orden). La Semana 7 reutiliza esa misma interfaz y concepto central, pero añade clases derivadas (AVL, RedBlackTree) que incorporan las rotaciones y los invariantes estructurales que estaban ausentes en la Semana 5, demostrando cómo evolucionar un árbol simple hacia una estructura capaz de auto-balancearse.

## Bloque 3 - AVL: balance por altura

### Archivos revisados :
* `Semana7/include/AVL.h`
* `Semana7/include/BST.h`
* `Semana7/include/BinNode.h`
* `Semana7/demos/demo_avl_deng_core.cpp`

**1. ¿Qué significa que un nodo esté balanceado en un AVL?**
Significa que la diferencia de altura entre su subárbol izquierdo y su subárbol derecho es, como máximo, de 1. Formalmente, en la implementación se define como `-2 < balanceFactor(x) && balanceFactor(x) < 2`.

**2. ¿Cómo se calcula el factor de balance?**
Se calcula restando la altura del subárbol derecho a la del izquierdo: `stature(x->lc) - stature(x->rc)`. La altura de un nodo nulo (`nullptr`) se considera convencionalmente como -1.

**3. ¿Qué información de altura debe mantenerse después de insertar o eliminar?**
Cada nodo (representado por `BinNode`) contiene un atributo `height`. Tras una modificación, es obligatorio actualizar este valor en todos los ancestros afectados desde el punto de cambio hacia la raíz, utilizando la fórmula: $1 + \max(\text{stature}(lc), \text{stature}(rc))$.

**4. ¿Qué representa `_hot` dentro de la implementación estilo Deng?**
La variable `_hot` actúa como un puntero de rastro durante las búsquedas. Almacena la referencia al *padre* del nodo que está siendo evaluado. En una inserción, `_hot` es el nodo padre al cual se enlazará el nuevo elemento. En una eliminación, indica desde dónde se debe empezar a verificar el balance hacia arriba.

**5. ¿Por qué AVL puede heredar de `BST<T, Compare>`?**
Porque un árbol AVL *es* estructuralmente y lógicamente un BST. Hereda toda la lógica de búsqueda, la estructura de nodos y los recorridos. AVL simplemente especializa (hace `override`) de los métodos `insert` y `remove` para inyectar su lógica de verificación de balance y rotaciones justo después de aplicar las operaciones estándar del BST.

**6. ¿Qué operación restaura localmente la forma del árbol?**
El balanceo se restaura mediante rotaciones locales. En la estructura de Deng, esto se abstrae en el método unificado `rotateAt(v)`, que evalúa el tipo de desbalance y utiliza el método `connect34` para reestructurar 3 nodos y 4 subárboles de un solo golpe.

**7. ¿Por qué una rotación no destruye la propiedad BST?**
Porque la reestructuración geométrica (ya sea rotación simple o doble) respeta rigurosamente el orden de las claves. Al realizar `connect34(a, b, c, T0, T1, T2, T3)`, el código asegura explícitamente que se mantenga el orden secuencial $T_0 < a < T_1 < b < T_2 < c < T_3$, preservando así la propiedad subyacente de búsqueda.

**8. Después de insertar, ¿por qué suele bastar reparar el primer ancestro desbalanceado?**
Cuando se inserta un nodo y el árbol se desbalancea, aplicar una rotación en el primer nodo crítico (el ancestro desbalanceado más profundo) hace que la altura total de ese subárbol en particular vuelva a ser la misma que tenía *antes* de la inserción. Como la altura global del subárbol reparado no cambia, los ancestros superiores no perciben el impacto y el balanceo termina prematuramente (`break;` en `AVL::insert`).

**9. Después de eliminar, ¿por qué puede ser necesario seguir revisando hacia la raíz?**
Al eliminar un nodo, una rotación reparadora puede disminuir la altura total del subárbol. Esta contracción puede desencadenar un nuevo desbalance en el nodo padre, lo que obliga al algoritmo a propagar la revisión y ejecutar posibles rotaciones en cascada hasta llegar a la raíz.

### Explicación de los invariantes AVL
El árbol AVL mantiene dos invariantes inquebrantables simultáneamente:
1. **Invariante de Orden (BST):** El hijo izquierdo es estrictamente menor al padre y el derecho es mayor.
2. **Invariante de Estructura (AVL):** Para todo nodo $x$ en el árbol, su factor de balance $h(lc) - h(rc)$ pertenece obligatoriamente al conjunto $\{-1, 0, 1\}$.

### Trazado de inserción con al menos una rotación
Asumamos la inserción consecutiva de `30, 20, 10`:
1. **Insertar 30:** Se convierte en la raíz. Altura 0.
2. **Insertar 20:** Es menor que 30, va a la izquierda. Raíz (30) pasa a altura 1, balance $1 - (-1) = 2$ (Wait, el balance es 1, ya que el hijo derecho es -1. Altura de 20 es 0). Todo está balanceado.
3. **Insertar 10:** Es menor que 20, va a la izquierda de 20. 
   * Nodo 20: altura 1, balance 1.
   * Nodo 30 (raíz): altura 2, su hijo izquierdo (20) tiene altura 1, su derecho (`nullptr`) -1. Su balance es $1 - (-1) = 2$. **¡Desbalance detectado en 30!**
4. **Rotación:** Estamos ante un caso *Izquierda-Izquierda* (LL). Se llama a `rotateAt(10)`. El nodo `20` sube como nueva raíz del subárbol, `10` se queda como su hijo izquierdo y `30` baja a ser el hijo derecho. Las alturas de `10` y `30` quedan en 0, y la de `20` en 1. Balance restaurado.

### Evidencia de salida de `demo_avl_deng_core.cpp`
```bash
AXEL@DESKTOP-70IITE7 UCRT64 /c/Users/AXEL/OneDrive/Escritorio/uni/2026-1/AED/Repositorio/Personal/CC232-sfinales/cc-232/Libreria_cc232
$ g++ -std=c++17 -I Semana7/include Semana7/demos/demo_avl_deng_core.cpp -o demo_avl

AXEL@DESKTOP-70IITE7 UCRT64 /c/Users/AXEL/OneDrive/Escritorio/uni/2026-1/AED/Repositorio/Personal/CC232-sfinales/cc-232/Libreria_cc232
$ ./demo_avl
AVL inorder: 10 20 22 25 27 30 40 50 
AVL level-order: 30 20 40 10 25 50 22 27 
Valido AVL: si
Tras borrar 20 y 40: 10 22 25 27 30 50 
Valido AVL: si
```

## Bloque 4 - Rotaciones AVL: casos LL, RR, LR y RL

### Archivos revisados :
* `Semana7/include/AVLTreeCompact.h`
* `Semana7/demos/demo_avl_compact_rotations.cpp`
* `Semana7/include/AVL.h`

### Tabla de Rotaciones AVL
Para observar los casos, se asume la inserción consecutiva en un árbol inicialmente vacío para generar el desbalance.

| Caso | Secuencia insertada | Nodo desbalanceado (g) | Rotación aplicada | Inorder antes (lógico) | Inorder después | Altura final |
| :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| **LL** | 30, 20, 10 | 30 | Simple a la derecha (`rotateAt(10)`) | 10, 20, 30 | 10, 20, 30 | 1 |
| **RR** | 10, 20, 30 | 10 | Simple a la izquierda (`rotateAt(30)`) | 10, 20, 30 | 10, 20, 30 | 1 |
| **LR** | 30, 10, 20 | 30 | Doble: Izquierda-Derecha (`rotateAt(20)`) | 10, 20, 30 | 10, 20, 30 | 1 |
| **RL** | 10, 30, 20 | 10 | Doble: Derecha-Izquierda (`rotateAt(20)`) | 10, 20, 30 | 10, 20, 30 | 1 |

*Nota: "Inorder antes" se refiere al estado lógico momentáneo justo después de insertar el nodo y antes de que la función `rotateAt` reestructure los punteros.*

### Dibujos pequeños de las rotaciones

**Caso LL (Izquierda-Izquierda)**
```text
Antes:        Después (Rotación Derecha):
    30             20
   /              /  \
  20    -->     10    30
 /
10
```

**Caso RR (Derecha-Derecha)**
```text
Antes:        Después (Rotación Izquierda):
10                 20
  \               /  \
   20   -->     10    30
     \
      30
```

**Caso LR (Izquierda-Derecha)**
```text
Antes:        Intermedio (Izq en 10):    Después (Der en 30):
    30                30                      20
   /                 /                       /  \
  10    -->         20          -->        10    30
    \              /
     20          10
```

**Caso RL (Derecha-Izquierda)**
```text
Antes:        Intermedio (Der en 30):    Después (Izq en 10):
10                10                          20
  \                 \                        /  \
   30   -->          20         -->        10    30
  /                   \
 20                    30
```

### Preguntas

**1. ¿Qué diferencia hay entre una rotación simple y una rotación doble?**

* **Rotación Simple**: Se realiza un único reajuste de punteros en una sola dirección (izquierda o derecha). Se utiliza cuando el camino de inserción o desbalance sigue una línea recta (todo a la izquierda o todo a la derecha).

* **Rotación Doble**: Requiere dos reajustes de punteros en direcciones opuestas. Se utiliza cuando el camino del desbalance forma un "zig-zag" (hijo izquierdo y luego hijo derecho, o viceversa). Internamente, primero convierte el zig-zag en una línea recta y luego aplica la rotación simple. 

**2. ¿Por qué LL y RR se corrigen con una sola rotación?**
Porque el exceso de peso está concentrado en un solo lado de forma lineal. En el caso LL, el subárbol izquierdo está muy pesado hacia la izquierda; simplemente girando el nodo intermedio hacia arriba (a la derecha) se redistribuye el peso de manera uniforme, convirtiendo al nodo intermedio en la nueva raíz de ese subárbol.

**3. ¿Por qué LR y RL requieren dos pasos?**
Porque el peso está "atrapado" en el interior del subárbol. En un caso LR, el nodo desbalanceado izquierdo tiene un hijo derecho pesado. Si hiciéramos una rotación simple, ese peso interno no se movería al lado opuesto del desbalance. Se necesita un primer paso para "sacar" ese peso hacia el exterior (alinearlo en LL) y un segundo paso para elevarlo a la raíz del subárbol.

**4. ¿Qué parte del árbol cambia y qué parte permanece igual?**

* **Cambia**: La jerarquía local y las alturas de los 3 nodos involucrados directamente en el desbalance (el nodo desbalanceado, su hijo alto y su nieto alto). También cambian los enlaces entre estos 3 nodos y sus subárboles adyacentes inmediatos.

* **Permanece igual**: Todos los subárboles que cuelgan de esos 3 nodos (los subárboles $T_0, T_1, T_2, T_3$ en el modelo de Deng). Estos subárboles se mueven "en bloque", manteniendo intacta su estructura interna y el resto del árbol por encima del nodo desbalanceado (si el balance se restauró sin afectar la altura total).

**5. ¿Por qué el inorder debe ser el mismo antes y después de reestructurar? (Argumento de preservación del orden BST)**
El recorrido inorder representa la secuencia lógica de menor a mayor en el árbol. La rotación es únicamente un cambio de la geometría y profundidad de los nodos, no un cambio en su valor o relación de orden.

Por ejemplo, si la relación lógica es $10 < 20 < 30$, no importa si el 20 es hijo de 30 (como en el desbalance LL) o si el 30 es hijo de 20 (después de la rotación); el árbol sigue respetando que todo a la izquierda es menor y todo a la derecha es mayor. Por diseño, la reasignación de los subárboles respeta la propiedad de búsqueda, garantizando que el inorder permanezca inalterado.


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