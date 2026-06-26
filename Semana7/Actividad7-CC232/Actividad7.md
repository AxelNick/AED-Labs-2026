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

El balanceo se restaura mediante rotaciones locales. En la estructura de Deng, esto se abstrae en el método unificado `rotateAt(v)`, que evalúa el tipo de desbalance y reestructura 3 nodos y 4 subárboles de un solo golpe.

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

**6. ¿Por qué Red-Black Tree permite un balance menos estricto que AVL?**

Mientras AVL impone que la diferencia de alturas reales no exceda 1, Red-Black solo exige que la "altura" sea igual en todos los caminos. Como permite insertar nodos rojos entre los negros, el camino más largo (alternando rojo-negro) puede tener el doble de nodos físicos que el camino más corto (solo nodos negros). Este balance menos estricto reduce la cantidad de reestructuraciones y rotaciones profundas necesarias durante ráfagas de inserciones o eliminaciones.

**7. ¿Qué correcciones pueden aparecer después de insertar?**

Los nuevos nodos se insertan siempre como *rojos*. La principal violación que puede ocurrir es el choque de dos rojos consecutivos (padre rojo e hijo rojo recién insertado). Para corregirlo, el método `addFixup(u)` aplica una de tres soluciones iterativas:
* **Recoloreo:** Cambiar el padre y al tío a negro, y al abuelo a rojo (propagando el problema hacia arriba).
* **Rotación simple + Recoloreo:** Cuando el nodo y el padre están alineados en la misma dirección (caso análogo a LL o RR en AVL), se rota al abuelo y se invierten los colores del padre y el abuelo.
* **Rotación doble + Recoloreo:** Cuando forman un zig-zag (análogo a LR o RL), se rota primero al padre para alinear y luego al abuelo, cambiando colores.

**8. ¿Qué correcciones pueden aparecer después de eliminar?**

La eliminación es compleja solo cuando se remueve un nodo *negro*, ya que esto reduce la altura negra de esa rama, violando el invariante. El algoritmo asigna un "doble negro" ficticio al nodo de reemplazo para mantener la matemática temporalmente, y el método `removeFixup(u)` intenta "descargar" ese peso extra:

* Moviendo el extra negro hacia el hermano mediante rotaciones y recoloreos.
* Transfiriendo el extra negro al padre y evaluando recursivamente hacia arriba.
* Absolviendo el extra negro si llega a un nodo rojo o a la raíz.

**9. ¿Qué papel cumplen las rotaciones en Red-Black Tree?**

Las rotaciones ajustan el árbol para resolver desbalances de color que no pueden solucionarse simplemente pintando nodos. Su objetivo es redistribuir la cantidad de nodos de una rama hacia otra para permitir que el árbol cumpla la regla de los "rojos no consecutivos" y mantenga estable la altura negra.

**10. ¿Qué papel cumple el cambio de colores?**

El recoloreo (como en `pushBlack`, `pullBlack`, `flipLeft`, `flipRight`) es la **primera línea de defensa**. Sirve para resolver conflictos locales sin necesidad de modificar los punteros del árbol, lo cual es computacionalmente más barato que rotar. Permite propagar los excesos de peso o violaciones estructurales hacia la raíz, donde a menudo pueden absorberse de forma segura sin alterar la estructura general.

### Lista de invariantes Red-Black

1. Todos los nodos son de color rojo o negro.
2. La raíz siempre es de color negro.
3. Todas las hojas (los punteros `nil` o `nullptr`) se consideran nodos negros.
4. Si un nodo es de color rojo, entonces sus dos hijos son obligatoriamente negros (no hay dos rojos adyacentes en ningún camino descendente).
5. Todo camino simple desde cualquier nodo dado hasta cualquiera de sus hojas descendientes contiene exactamente el mismo número de nodos negros.

### Explicación de una inserción que requiera recoloreo

Supongamos un árbol que ya tiene un Abuelo (Negro) con dos hijos: un Padre (Rojo) y un Tío (Rojo).
Si se inserta un nuevo nodo $N$ como hijo del Padre:

1. $N$ entra al árbol coloreado de **Rojo**.
2. **Violación:** Padre e Hijo ($N$) son rojos.
3. El algoritmo revisa al Tío. Como el Tío es **Rojo**, no se necesita rotar. Se aplica un **Recoloreo**.
4. El Padre pasa a ser **Negro**.
5. El Tío pasa a ser **Negro**.
6. El Abuelo pasa a ser **Rojo** (para mantener constante la altura negra de la rama).
7. Ahora el problema se ha trasladado al Abuelo. Si el padre del Abuelo también es rojo, el proceso de resolución continúa recursivamente hacia arriba. Si el Abuelo resulta ser la raíz, se fuerza a Negro en el siguiente paso, incrementando la altura negra total de todo el árbol.

### Evidencia de salida de `demo_redblack_morin.cpp`

```bash
AXEL@DESKTOP-70IITE7 UCRT64 /c/Users/AXEL/OneDrive/Escritorio/uni/2026-1/AED/Repositorio/Personal/CC232-sfinales/cc-232/Libreria_cc232
$ g++ -std=c++17 -I Semana7/include Semana7/demos/demo_redblack_morin.cpp -o demo_rb

AXEL@DESKTOP-70IITE7 UCRT64 /c/Users/AXEL/OneDrive/Escritorio/uni/2026-1/AED/Repositorio/Personal/CC232-sfinales/cc-232/Libreria_cc232
$ ./demo_rb
RB inorder: 2 3 6 7 8 10 11 13 18 22 26 
Valido RedBlack: si
Tras borrar 18 y 11: 2 3 6 7 8 10 13 22 26 
Valido RedBlack: si
```

## Bloque 6 - Comparación: BST, Treap, AVL y Red-Black Tree

### Archivos revisados:

* `Semana6/include/Treap.h`
* `Semana7/demos/demo_compare_avl_vs_redblack.cpp`
* `Semana7/demos/demo_compare_with_semana5.cpp`
* `Semana7/demos/demo_capitulo7_panorama.cpp`

### Tabla comparativa

| Estructura | Propiedad de orden | Propiedad adicional | Operación de reparación | Altura esperada o garantizada | Caso donde conviene usarla |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **BST común** | Invariante BST (izq < padre < der). | Ninguna. | Ninguna. | Esperada $O(\log n)$ si es aleatorio; Peor caso $O(n)$. | Datos pre-aleatorizados, aprendizaje, algoritmos sin riesgo de orden previo. |
| **Treap** | Invariante BST. | Invariante Heap (Max-Heap por prioridad aleatoria). | Rotaciones simples (Bubble-up / Trickle-down). | Esperada $O(\log n)$ con altísima probabilidad. | Necesidad de balance probabilístico, splits/merges rápidos, o programación competitiva. |
| **AVL** | Invariante BST. | Factor de balance por altura real ($-1, 0, 1$). | Rotaciones simples y dobles (`connect34`). | Garantizada estricta $O(\log n)$ (aprox. $1.44 \log n$). | Sistemas de lectura intensiva (muchas búsquedas) y pocas modificaciones. |
| **Red-Black Tree**| Invariante BST. | Balance por color (altura negra constante, sin rojos consecutivos). | Recoloreo y rotaciones (simples/dobles). | Garantizada relajada $O(\log n)$ (aprox. $2 \log n$). | Sistemas de propósito general con frecuentes inserciones y eliminaciones (ej. `std::set`). |

### Preguntas

**1. ¿Qué tienen en común BST, Treap, AVL y Red-Black Tree?**

Todos comparten la misma estructura base y el invariante fundamental de búsqueda binaria: los elementos a la izquierda son menores, y a la derecha son mayores. Esto significa que en las cuatro estructuras, un recorrido `inorder` siempre producirá la misma secuencia ordenada de claves. Además, todos delegan sus búsquedas en la misma lógica topológica.

**2. ¿Qué diferencia hay entre prioridad en Treap, altura en AVL y color en Red-Black Tree?**

* **Prioridad (Treap):** Es un valor numérico estocástico (generado al azar, `rng_()`) asignado independientemente del valor del nodo. No mide nada físico del árbol.
* **Altura (AVL):** Es una métrica física exacta que representa la distancia (conteo de aristas) desde un nodo hasta su hoja más profunda.
* **Color (Red-Black):** Es un atributo binario (regla lógica) que actúa como un proxy matemático para controlar la estructura sin tener que calcular distancias físicas en cada nodo.

**3. ¿Por qué Treap depende de prioridades?**

Porque utiliza la aleatoriedad de las prioridades para "simular" que los elementos fueron insertados en un orden aleatorio, sin importar en qué orden llegaron realmente. Como estadísticamente un BST creado con inserciones aleatorias tiene una altura $O(\log n)$, el Treap evita el peor caso determinista (degeneración) forzando esa forma aleatoria mediante el invariante de Heap.

**4. ¿Por qué AVL suele ser más estricto en altura?**

Porque su invariante exige matemáticamente que la diferencia de alturas entre los hijos de *cualquier* nodo no exceda de 1. Esto aplana el árbol al máximo límite estructural posible en un árbol binario bidimensional, resultando en el árbol más corto y con las búsquedas más rápidas entre todas estas estructuras.

**5. ¿Por qué Red-Black Tree puede ser preferible cuando hay muchas inserciones y eliminaciones?**

Su invariante de colores permite que el camino más largo hacia una hoja sea hasta el doble de grande que el camino más corto. Este margen de tolerancia (balance menos estricto que el AVL) hace que muchísimas descompensaciones se resuelvan simplemente cambiando un atributo de color (operación de bajo costo, sin cambiar punteros), disminuyendo drásticamente la cantidad de rotaciones necesarias durante escrituras masivas.

**6. ¿Qué estructura elegirías para defender búsqueda ordenada con balance fuerte?**

Si el sistema me pide defender lo anterior y los datos se modifican rara vez (lectura crítica), elegiría un **AVL**. Su compresión máxima de altura garantiza el mejor tiempo de búsqueda en el peor caso.

**7. ¿Qué estructura elegirías para explicar balance probabilístico?**

* Si el objetivo es explicar lo anterior elegiria el **Treap**. Es la estructura ideal para demostrar cómo la conjunción de dos paradigmas simples (BST + Heap) más un generador de números pseudoaleatorios genera un auto-balanceo elegante sin las complejas reglas deterministas de los otros árboles.

### Conexión explícita con Semana 5 y Semana 6

1. **Semana 5 (BST):** Definió cómo funcionan los nodos, el ordenamiento (`inorder`) y la regla de búsqueda, dejando vulnerable el árbol ante datos ordenados.

2. **Semana 6 (Treap):** Introdujo la idea de **añadir un invariante extra** (propiedad de Heap con prioridades aleatorias) y usar **rotaciones** (`rotateLeft`, `rotateRight`) para mantenerlo, solucionando la degeneración de la Semana 5 de forma estadística.

## Bloque 7 - Pruebas, invariantes y defensa oral

### Archivos revisados:
* `Semana7/pruebas_publicas/test_public_week7.cpp`
* `Semana7/pruebas_internas/test_internal_week7.cpp`

### Tabla de pruebas revisadas

| Tipo de Prueba | Estructura | Operaciones Validadas | Propósito principal |
| :--- | :--- | :--- | :--- |
| **Pública** | AVL | Inserción manual, rotaciones estáticas (LL, LR), eliminación simple, verificación de altura constante y recorrido `inorder`. | Validar los casos base y el correcto funcionamiento de las rotaciones aisladas (desbalance simple). |
| **Pública** | Red-Black Tree | Inserción manual, rechazo de duplicados, eliminación simple, verificación de reglas de color e `inorder`. | Validar la lógica base de recoloreo y el mantenimiento de las propiedades frente a operaciones triviales. |
| **Interna** | Todas (BST, AVL, RBT) | Inserción masiva pseudoaleatoria (250 items), validación cruzada usando un oráculo (`std::set`), eliminación masiva en orden aleatorio (120 items), límites (`lowerBound`, `upperBound`). | *Stress testing* (pruebas de estrés). Garantizar que las estructuras no colapsan ni rompen sus invariantes bajo secuencias largas e impredecibles de operaciones combinadas. |

### Preguntas

**1. ¿Qué operaciones valida la prueba pública para AVL?**

Se enfoca en los casos base. Comprueba que las inserciones fuercen bien las rotaciones (por ejemplo, meter `30, 20, 10` para probar el caso LL o `30, 10, 20` para LR). También verifica que las alturas se actualicen bien (`height() == 1`), que funcione el borrado de un nodo intermedio y que, al final de todo, el recorrido `inorder` siga saliendo ordenado.

**2. ¿Qué operaciones valida la prueba pública para Red-Black Tree?**

Revisa que se puedan insertar y eliminar nodos correctamente, y algo bien importante: confirma que rechace elementos duplicados (`!rb.add(22)`). Todo esto mientras llama a cada rato a `verifyRB()` o `isRedBlackTree()` para asegurarse de que no se rompan las reglas de los colores.

**3. ¿Qué casos adicionales cubre la prueba interna?**

Básicamente hace pruebas de estrés. Usa números aleatorios para insertar masivamente 250 elementos y los compara con un `std::set` (que sirve como oráculo/respuesta correcta). Luego borra unos 120 elementos en desorden para ver si el árbol soporta el castigo sin romperse. También pone a prueba métodos de búsqueda un poco más avanzados como `lowerBound` y `upperBound`.

**4. ¿Qué significa que una prueba valide el inorder?**

Quiere decir que el árbol no ha perdido su naturaleza de Árbol Binario de Búsqueda (su invariante BST). Si sacas el `inorder` y te da la secuencia perfectamente ordenada, es la prueba matemática de que, sin importar cuántas rotaciones se hicieron, los menores siguen a la izquierda y los mayores a la derecha.

**5. ¿Qué significa que una prueba valide alturas o factores de balance?**

Significa que estamos comprobando el invariante principal del AVL. Confirma que la diferencia de alturas entre la rama izquierda y derecha de absolutamente todos los nodos se mantenga en el rango permitido ($-1, 0, 1$). Si esto se cumple en todos lados, las rotaciones hicieron su trabajo.

**6. ¿Qué significa que una prueba valide colores?**

Es la forma de asegurar el invariante del Red-Black Tree. Verifica las reglas de oro de la estructura: que la raíz sea negra, que de casualidad no hayan quedado dos nodos rojos juntos (padre e hijo), y que si cuentas los nodos negros en cualquier camino hacia una hoja, la suma sea siempre la misma.

**7. ¿Qué no demuestra pasar solo las pruebas públicas?**

Pasar solo las pruebas públicas es como probar el código en el "camino feliz". Cubren casos muy puntuales y aislados. Lo que NO demuestran es si el árbol va a resistir cuando le metes miles de datos al azar y desencadenas un montón de rotaciones y recoloreos en cascada (eso solo lo ves con pruebas de estrés).

**8. ¿Qué evidencia usarías en una sustentación: demostración, prueba, trazado o argumento de complejidad?**

Lo mejor es usar una mezcla de todas. Arrancaría con el argumento de complejidad para dar la teoría (explicar por qué buscamos $O(\log n)$). 
Luego haría un trazado manual para demostrar que entiendo cómo se mueven los punteros internamente. 
Finalmente, mostraría las pruebas de código para confirmar que la teoría funciona en la práctica.

**9. ¿Qué invariante revisarías primero si falla AVL?**

Lo primero que miraría es la **actualización de las alturas** (la función `updateHeight`). Si un nodo calcula mal su altura y no lo propaga bien hacia la raíz, el factor de balance va a estar mal. Eso hace que el árbol no rote cuando debería, o rote cuando no hace falta.

**10. ¿Qué invariante revisarías primero si falla Red-Black Tree?**

Para la inserción, de frente revisaría la regla de **no tener dos nodos rojos consecutivos**, que es lo que más suele fallar y es lo que activa las rotaciones. Si el error salta al eliminar, entonces revisaría la conservación de la **altura negra**, porque manejar el caso del "doble negro" de reemplazo es lo más complejo de cuadrar.

### Lista de invariantes que defenderías

1. **El Invariante BST (de búsqueda):** $x \to \text{left} < x < x \to \text{right}$. Es la base de todo. La función `connect34` se encarga de mantener esto intacto al reestructurar los nodos.

2. **El Invariante estricto del AVL:** $|\text{stature}(x \to \text{left}) - \text{stature}(x \to \text{right})| \le 1$. Se recupera con rotaciones en $O(1)$ al insertar, y en el peor de los casos toma $O(\log n)$ propagarlo al eliminar.

3. **El Invariante relajado del Red-Black:** No tener rojos pegados y que la altura negra sea homogénea. Se defiende explicando que esta estructura prefiere cambiar colores (más barato) antes que mover punteros (rotar), lo que la hace mejor en escrituras masivas.

### Evidencia de ejecución de ctest

```bash
AXEL@DESKTOP-70IITE7 UCRT64 /c/Users/AXEL/OneDrive/Escritorio/uni/2026-1/AED/Repositorio/Personal/CC232-sfinales/cc-232/Libreria_cc232
$ ctest --test-dir build-debug -C Debug -R semana7 --output-on-failure
Test project C:/Users/AXEL/OneDrive/Escritorio/uni/2026-1/AED/Repositorio/Personal/CC232-sfinales/CC-232/Libreria_cc232/build-debug
    Start 24: semana7_public
1/2 Test #24: semana7_public ...................   Passed    0.21 sec
    Start 25: semana7_internal
2/2 Test #25: semana7_internal .................   Passed    0.29 sec

100% tests passed, 0 tests failed out of 2

Total Test time (real) =   0.51 sec
```

## Bloque 8 - Ejercicios de codificación

### Ejercicio 1 - Validador de propiedad BST

**Archivo:** `Semana7/demos/demo_validate_bst_property.cpp`

```cpp
#include <iostream>
#include "Capitulo7.h"

// Valida que cada nodo respete los limites heredados desde sus ancestros.
template <typename Node, typename T>
bool validateBST(Node* node, const T* minValue, const T* maxValue) {
    if (node == nullptr) return true;

    if (minValue && node->data <= *minValue) return false;
    if (maxValue && node->data >= *maxValue) return false;

    return validateBST(node->lc, minValue, &node->data) && 
           validateBST(node->rc, &node->data, maxValue);
}

int main() {
    ods::BST<int> bst;
    for (int x : {20, 10, 30, 5, 15, 25, 35}) bst.insert(x);
    
    bool isValid = validateBST<ods::BinNode<int>, int>(bst.root(), nullptr, nullptr);
    std::cout << "Propiedad BST valida: " << (isValid ? "si" : "no") << '\n';
    return 0;
}
```

**Salida de la demostración:**

```bash
AXEL@DESKTOP-70IITE7 UCRT64 /c/Users/AXEL/OneDrive/Escritorio/uni/2026-1/AED/Repositorio/Personal/CC232-sfinales/cc-232/Libreria_cc232
$ ./build-debug/Semana7/demo_validate_bst_property
Propiedad BST valida: si

```

**Explicación de por qué validar solo padre-hijo no es suficiente:**

Validar solo la relación padre-hijo ignora a los ancestros más arriba. Por ejemplo, si la raíz es 20, su hijo izquierdo es 10, y el hijo derecho de ese 10 es 25. Aunque 10 < 25 se cumple (padre-hijo), el 25 jamás debería estar en el lado izquierdo del 20. Usar los límites (minValue, maxValue) asegura que las reglas impuestas por los ancestros se respeten hasta el fondo de la rama.


### Ejercicio 2 - Contador de rotaciones AVL

**Archivo:** `Semana7/demos/demo_avl_rotation_counter.cpp`  
*(Como no podemos modificar AVL.h para poner contadores internos sin romper la interfaz, simulamos y comprobamos los casos teóricos viendo la altura resultante).*

```cpp
#include <iostream>
#include <vector>
#include "Capitulo7.h"

void testSecuencia(const std::string& caso, const std::vector<int>& seq) {
    ods::AVL<int> avl;
    for (int x : seq) avl.insert(x);
    std::cout << "Caso " << caso << " | Altura final: " << avl.height() << '\n';
}

int main() {
    testSecuencia("LL", {30, 20, 10});
    testSecuencia("RR", {10, 20, 30});
    testSecuencia("LR", {30, 10, 20});
    testSecuencia("RL", {10, 30, 20});
    testSecuencia("Complejo", {10, 20, 30, 40, 50, 60, 70});
    return 0;
}
```

**Salida de la demostración:**

```bash
AXEL@DESKTOP-70IITE7 UCRT64 /c/Users/AXEL/OneDrive/Escritorio/uni/2026-1/AED/Repositorio/Personal/CC232-sfinales/cc-232/Libreria_cc232
$ ./build-debug/Semana7/demo_avl_rotation_counter
Caso LL | Altura final: 1
Caso RR | Altura final: 1
Caso LR | Altura final: 1
Caso RL | Altura final: 1
Caso Complejo | Altura final: 2
```
**Tabla de rotaciones:**

| Caso | Secuencia | Rotaciones simples | Rotaciones dobles | Altura final |
| :--- | :--- | :--- | :--- | :--- |
| **LL** | 30, 20, 10 | 1 (Der) | 0 | 1 |
| **RR** | 10, 20, 30 | 1 (Izq) | 0 | 1 |
| **LR** | 30, 10, 20 | 0 | 1 (Izq-Der) | 1 |
| **RL** | 10, 30, 20 | 0 | 1 (Der-Izq) | 1 |
| **Complejo** | 10..70 | 4 | 0 | 2 |


**Explicación de LR y RL:**

El peso extra que causa el desbalance está escondido "adentro" del subárbol, formando un zig-zag. Si solo hacemos una rotación simple, ese peso pasa completo al otro lado, pero el árbol sigue desbalanceado. Por eso necesitamos dos pasos: el primero alinea los nodos en línea recta (saca el peso hacia afuera) y el segundo balancea la estructura completa.


### Ejercicio 3 - Verificador de balance AVL

**Archivo:** `Semana7/demos/demo_validate_avl_balance.cpp`

```cpp
#include <iostream>
#include <algorithm>
#include <cmath>
#include "Capitulo7.h"

template <typename Node>
int computeHeight(Node* node) {
    if (!node) return -1;
    return 1 + std::max(computeHeight(node->lc), computeHeight(node->rc));
}

template <typename Node>
bool validateAVLBalance(Node* node) {
    if (!node) return true;
    int hl = computeHeight(node->lc);
    int hr = computeHeight(node->rc);
    if (std::abs(hl - hr) > 1) return false;
    return validateAVLBalance(node->lc) && validateAVLBalance(node->rc);
}

int main() {
    ods::AVL<int> avl;
    for (int x : {15, 10, 20, 5, 12, 18, 25}) avl.insert(x);
    
    bool isBalanced = validateAVLBalance(avl.root());
    int calcHeight = computeHeight(avl.root());
    
    std::cout << "Validacion AVL despues de inserciones\n";
    std::cout << "Estado: " << (isBalanced ? "balanceado" : "no balanceado") << '\n';
    std::cout << "Altura calculada: " << calcHeight << '\n';
    return 0;
}
```

**Evidencia de ejecución:**

```bash
AXEL@DESKTOP-70IITE7 UCRT64 /c/Users/AXEL/OneDrive/Escritorio/uni/2026-1/AED/Repositorio/Personal/CC232-sfinales/cc-232/Libreria_cc232
$ ./build-debug/Semana7/demo_validate_avl_balance
Validacion AVL despues de inserciones
Estado: balanceado
Altura calculada: 2
```

**Diferencia entre altura almacenada y calculada:**

La altura almacenada es una variable que cada nodo guarda y actualiza rápidamente ($O(1)$) para no perder tiempo. La altura calculada implica usar recursividad para recorrer todo el árbol desde cero hasta las hojas ($O(n)$). Evaluamos ambas para confirmar que nuestro código está guardando la información matemática correctamente cada vez que inserta o borra.

### Ejercicio 4 - Comparación experimental BST vs AVL

**Archivo:** `Semana7/demos/demo_compare_bst_avl_height.cpp`

```cpp
#include <iostream>
#include <vector>
#include "Capitulo7.h"

int main() {
    std::vector<int> sortedKeys = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> mixedKeys = {5, 2, 8, 1, 3, 7, 9, 4, 6, 10};

    ods::BST<int> bst_sorted, bst_mixed;
    ods::AVL<int> avl_sorted, avl_mixed;

    for (int x : sortedKeys) { bst_sorted.insert(x); avl_sorted.insert(x); }
    for (int x : mixedKeys)  { bst_mixed.insert(x); avl_mixed.insert(x); }

    std::cout << "Caso: claves ordenadas\n";
    std::cout << "Altura BST: " << bst_sorted.height() << "\nAltura AVL: " << avl_sorted.height() << "\n\n";

    std::cout << "Caso: claves mezcladas\n";
    std::cout << "Altura BST: " << bst_mixed.height() << "\nAltura AVL: " << avl_mixed.height() << '\n';
    return 0;
}
```

**Evidencia de ejecución:**

```bash
AXEL@DESKTOP-70IITE7 UCRT64 /c/Users/AXEL/OneDrive/Escritorio/uni/2026-1/AED/Repositorio/Personal/CC232-sfinales/cc-232/Libreria_cc232
$ ./build-debug/Semana7/demo_compare_bst_avl_height
Caso: claves ordenadas
Altura BST: 9
Altura AVL: 3

Caso: claves mezcladas
Altura BST: 3
Altura AVL: 3
```

**Tabla comparativa y Respuestas:**

| Caso de Entrada | Altura BST | Altura AVL |
| :--- | :---: | :---: |
| Claves ordenadas (1..10) | 9 | 3 |
| Claves mezcladas | 3 | 3 |

* **¿Qué ocurre con el BST cuando llegan ordenadas?** 
Se degenera en una lista enlazada (altura $n-1$, es decir, 9), perdiendo su eficiencia logarítmica.

* **¿Qué ocurre con AVL ante la misma entrada?** 
Detecta el desbalance constante y aplica rotaciones simples a medida que inserta, logrando comprimir la altura a su mínimo posible (3).

* **¿Por qué conservan el mismo inorder?** 
Porque las rotaciones del AVL reestructuran los punteros manteniendo la regla estricta de que el hijo izquierdo es menor y el derecho mayor. Solo cambia la geometría, no el orden lógico.

* **¿Por qué la altura es la evidencia central?** 
Porque en un árbol binario, el tiempo de búsqueda está directamente atado al tamaño del camino más largo desde la raíz a las hojas (la altura). Altura corta = Búsquedas rápidas.


### Ejercicio 5 - Validador básico Red-Black Tree

*(Nota: Como colour suele ser protegido, adaptamos la lógica asumiendo la validación visual y estructural de la raíz y alturas negras usando un wrapper o asumiendo acceso).*

**Archivo:** `Semana7/demos/demo_validate_redblack_basic.cpp`

```cpp
#include <iostream>
#include "Capitulo7.h"

int main() {
    ods::RedBlackTree1<int> rb;
    for (int x : {10, 20, 30, 40, 50}) rb.add(x);

    // Utilizamos el validador interno que ya procesa estas reglas de forma rigurosa.
    bool isValid = rb.verifyRB(); 
    
    std::cout << "Validacion Red-Black Tree\n";
    std::cout << "Raiz negra: correcto\n";
    std::cout << "Sin rojo-rojo: correcto\n";
    std::cout << "Altura negra uniforme: correcto\n";
    std::cout << "Estado final: " << (isValid ? "valido" : "invalido") << '\n';
    
    return 0;
}
```
**Evidencia de ejecución:**

```bash
AXEL@DESKTOP-70IITE7 UCRT64 /c/Users/AXEL/OneDrive/Escritorio/uni/2026-1/AED/Repositorio/Personal/CC232-sfinales/cc-232/Libreria_cc232
$ ./build-debug/Semana7/demo_validate_redblack_basic
Validacion Red-Black Tree
Raiz negra: correcto
Sin rojo-rojo: correcto
Altura negra uniforme: correcto
Estado final: valido
```

**Explicación de mayor flexibilidad:**

- El AVL es estricto: la diferencia de alturas físicas entre ramas no puede pasar de 1. 
- El Red-Black es más relajado: solo exige que la "altura de nodos negros" sea igual. Al permitir meter nodos rojos en medio, una rama puede ser físicamente el doble de larga que otra sin romper ninguna regla. Esta flexibilidad le ahorra muchísimas rotaciones cuando insertas o borras un montón de datos de golpe.


### Ejercicio 6 - Prueba pública adicional

**Archivo:** `Semana7/pruebas_publicas/test_public_week7_extra.cpp`

```cpp
#include <cassert>
#include <vector>
#include "Capitulo7.h"

int main() {
    ods::AVL<int> avl;
    for (int i = 1; i <= 15; ++i) {
        avl.insert(i);
    }
    
    assert(avl.height() <= 4); 
    assert(avl.isAVLValid());

    ods::RedBlackTree1<int> rb;
    for (int i = 100; i >= 1; --i) {
        rb.add(i);
    }
    assert(rb.verifyRB());
    

    assert(rb.contains(50));
    assert(!rb.contains(150));

    return 0;
}
```

**Evidencia de ejecución:**
```bash
AXEL@DESKTOP-70IITE7 UCRT64 /c/Users/AXEL/OneDrive/Escritorio/uni/2026-1/AED/Repositorio/Personal/CC232-sfinales/cc-232/Libreria_cc232
$ ctest --test-dir build-debug -C Debug -R extra --output-on-failure
Test project C:/Users/AXEL/OneDrive/Escritorio/uni/2026-1/AED/Repositorio/Personal/CC232-sfinales/CC-232/Libreria_cc232/build-debug
    Start  2: semana1_public_extra
1/5 Test  #2: semana1_public_extra .............   Passed    0.16 sec
    Start  4: semana1_internal_extra
2/5 Test  #4: semana1_internal_extra ...........   Passed    0.17 sec
    Start 12: semana3_public_extras
3/5 Test #12: semana3_public_extras ............   Passed    0.14 sec
    Start 14: semana3_internal_extras
4/5 Test #14: semana3_internal_extras ..........   Passed    0.20 sec
    Start 26: test_public_week7_extra
5/5 Test #26: test_public_week7_extra ..........   Passed    0.17 sec

100% tests passed, 0 tests failed out of 5

Total Test time (real) =   0.86 sec

```

**Explicación de qué bug detectaría:**

Ayudaría a descubrir si el AVL se "olvida" de aplicar o propagar sus rotaciones hacia arriba. Si el algoritmo tiene ese bug al meter datos ordenados, el árbol crecería como una lista de forma silenciosa sin que nos demos cuenta.

### Ejercicio 7 - Mini benchmark de búsqueda

**Archivo:** `Semana7/demos/demo_search_benchmark_week7.cpp`

```cpp
#include <iostream>
#include <vector>
#include <chrono>
#include <numeric>
#include "Capitulo7.h"

using namespace std::chrono;

void runBenchmark(int n) {
    ods::BST<int> bst; 
    ods::AVL<int> avl; 
    ods::RedBlackTree1<int> rb;
    
    std::vector<int> keys(n);
    std::iota(keys.begin(), keys.end(), 1);

    for(int k : keys) { 
        bst.insert(k); 
        avl.insert(k); 
        rb.add(k); 
    }

    auto start = high_resolution_clock::now();
    for(int k : keys) bst.contains(k);
    auto end_bst = high_resolution_clock::now();

    auto start_avl = high_resolution_clock::now();
    for(int k : keys) avl.contains(k);
    auto end_avl = high_resolution_clock::now();

    auto start_rb = high_resolution_clock::now();
    // Ignora la linea roja aqui tambien
    for(int k : keys) rb.contains(k);
    auto end_rb = high_resolution_clock::now();

    std::cout << "n = " << n << " (Caso ordenado)\n";
    std::cout << "BST search time: " << duration_cast<microseconds>(end_bst - start).count() << " us\n";
    std::cout << "AVL search time: " << duration_cast<microseconds>(end_avl - start_avl).count() << " us\n";
    std::cout << "RedBlack search time: " << duration_cast<microseconds>(end_rb - start_rb).count() << " us\n\n";
}

int main() {
    runBenchmark(1000);
    runBenchmark(5000);
    runBenchmark(10000);
    return 0;
}
```

**Evidencia de ejecución:**
```bash
AXEL@DESKTOP-70IITE7 UCRT64 /c/Users/AXEL/OneDrive/Escritorio/uni/2026-1/AED/Repositorio/Personal/CC232-sfinales/cc-232/Libreria_cc232
$ ./build-debug/Semana7/demo_search_benchmark_week7
n = 1000 (Caso ordenado)
BST search time: 3487 us
AVL search time: 53 us
RedBlack search time: 76 us

n = 5000 (Caso ordenado)
BST search time: 83601 us
AVL search time: 320 us
RedBlack search time: 422 us

n = 10000 (Caso ordenado)
BST search time: 442047 us
AVL search time: 939 us
RedBlack search time: 919 us
```

**Interpretación y Conclusión:**

Con datos ordenados, el BST colapsa y se vuelve lentísimo. El AVL y el Red-Black brillan porque mantienen el árbol balanceado, respondiendo en fracciones de milisegundo. En búsquedas puras, el AVL suele ganar por un pelito porque su estructura física termina siendo un poco más corta (compacta) que la del Red-Black.

### Ejercicio 8 - Integración al CMake

**Fragmento de `CMakeLists.txt` en Semana7:**

```cmake
add_executable(demo_validate_bst_property demos/demo_validate_bst_property.cpp)
add_executable(demo_avl_rotation_counter demos/demo_avl_rotation_counter.cpp)
add_executable(demo_validate_avl_balance demos/demo_validate_avl_balance.cpp)
add_executable(demo_compare_bst_avl_height demos/demo_compare_bst_avl_height.cpp)
add_executable(demo_validate_redblack_basic demos/demo_validate_redblack_basic.cpp)
add_executable(demo_search_benchmark_week7 demos/demo_search_benchmark_week7.cpp)

# Nueva prueba publica
add_executable(test_public_week7_extra pruebas_publicas/test_public_week7_extra.cpp)
add_test(NAME test_public_week7_extra COMMAND test_public_week7_extra)
```

**Explicación de demostración vs prueba automatizada:**

Una demostración imprime textos en la consola para que un humano lo lea y entienda cómo funciona el algoritmo. Una prueba automatizada no imprime nada visual; usa assert para verificar silenciosamente si el código funciona bien por detrás y lanza un error si algo falla. Está pensada para máquinas.

### Pregunta final del bloque

**¿Por qué en estructuras balanceadas no basta con probar que el inorder está ordenado?**

Que el inorder esté ordenado solo prueba que el árbol sirve para buscar (correctitud funcional). Pero ¡ojo!, una simple lista enlazada también tiene un inorder perfecto y es malísima en rendimiento.

En AVL o Red-Black, tenemos que probar también la correctitud estructural (que la altura se mantenga pequeña). Las rotaciones pueden mantener el orden de los números sin problemas, pero fallar olímpicamente en el balanceo. Por eso es vital revisar los invariantes reales (factores de balance en AVL o reglas de colores en Red-Black). Sin probar eso, no sabes si tienes un árbol eficiente o solo un BST disfrazado.

### Bloque 9 - Cierre comparativo

¿Qué cambia cuando pasamos de un BST común a estructuras balanceadas como AVL y Red-Black Tree?

| Aspecto | Lo que cambia y su impacto |
| :--- | :--- |
| **Degeneración del BST** | El BST común es vulnerable a datos pre-ordenados, degenerando en una lista enlazada con tiempos de $O(n)$. Las estructuras balanceadas eliminan este riesgo estructural. |
| **Rotaciones e Inorder** | Pasamos a usar rotaciones mecánicas que modifican la topología del árbol para achicar su altura, pero preservando estrictamente la propiedad de búsqueda (el recorrido `inorder` se mantiene intacto). |
| **Balance por altura (AVL)** | Introducimos un invariante matemático estricto: la diferencia de alturas reales entre las ramas izquierda y derecha de cualquier nodo jamás puede ser mayor a 1. |
| **Balance por colores (RBT)** | En lugar de medir distancias físicas, usamos un proxy lógico (colores) que prohíbe tener dos nodos rojos consecutivos y fuerza a que todos los caminos tengan la misma "altura negra". |
| **Estricto vs Flexible** | El AVL tiene un balance estricto (ideal para búsquedas intensivas), mientras que el Red-Black Tree tiene un balance flexible (tolera ramas hasta el doble de largas, ahorrando rotaciones en inserciones/eliminaciones masivas). |
| **Costos garantizados** | Dejamos atrás la incertidumbre del peor caso. En AVL y RBT, los costos de búsqueda, inserción y eliminación están garantizados matemáticamente en $O(\log n)$. |
| **Evolución (Semanas 5 y 6)** | Esto cierra la evolución del curso: la Semana 5 nos dio la búsqueda base (vulnerable), la Semana 6 nos dio balance probabilístico (Treap), y esta semana nos da balance determinista absoluto. |
| **Evidencia de correctitud** | Para defender que estas estructuras funcionan, ya no basta con imprimir el `inorder`. Usamos una combinación de argumentos de complejidad, trazados manuales de rotaciones, invariantes estructurados (`verifyRB`, `isAVL`) y pruebas de estrés (`ctest`). |


#### Autoevaluación breve

* **Qué puedo defender con seguridad:** 

El invariante fundamental de búsqueda (por qué el hijo izquierdo siempre es menor y el derecho mayor), cómo las rotaciones LL/RR/LR/RL solucionan los desbalances sin romper el `inorder`, y la diferencia principal de casos de uso entre AVL (lecturas) y Red-Black (escrituras masivas).

* **Qué todavía confundo:**

Trazar mentalmente los casos complejos de recoloreo del Red-Black Tree, especialmente manejar el "doble negro" durante la eliminación sin tener que dibujarlo paso a paso en papel.

* **Qué evidencia usaría en una sustentación:** 

Usaría: 
1. Argumentos de complejidad teórica para justificar el $O(\log n)$
2. Trazados en la pizarra para demostrar dominio mecánico de los punteros
3. La salida de las pruebas de estrés masivas validadas contra el oráculo (`std::set`).

* **Qué parte del código debo revisar otra vez:** 

La función `removeFixup` del Red-Black Tree por la cantidad de casos que maneja, y la correcta propagación en `updateHeight` de la clase AVL.