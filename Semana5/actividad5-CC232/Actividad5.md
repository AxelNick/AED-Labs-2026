# Actividad 5 - Semana 5

## Integrantes
- Axel Alberto Reyes Baldeón

## Bloque 0 - Instalación y preparación

- [x] Carpeta de trabajo lista.
- [x] Verificación de acceso a lecturas y archivo de entrega.
- [x] Creación del archivo `Actividad5-CC232.md`.
- [x] Registro de mi nombre completo.
- [x] Compilación y ejecución de demostraciones y pruebas.

### Verificación de Entorno (Semana 5)

**Estado de Compilación y Ejecución:**

* **Demo ejecutada:** `sem5_demo_binary_tree.exe`

```
$ ./sem5_demo_binary_tree.exe
Arbol:
│       ┌── 12
│   ┌── 10
│   │   └── 8
└── 7
    │       ┌── 6
    │   ┌── 5
    │   │   └── 4
    └── 3
        └── 1

Preorden recursivo: 7 3 1 5 4 6 10 8 12
Preorden iterativo: 7 3 1 5 4 6 10 8 12
Inorden recursivo: 1 3 4 5 6 7 8 10 12
Inorden iterativo #1: 1 3 4 5 6 7 8 10 12
Inorden iterativo #2: 1 3 4 5 6 7 8 10 12
Inorden iterativo #3: 1 3 4 5 6 7 8 10 12
Postorden recursivo: 1 4 6 5 3 8 12 10 7
Postorden iterativo: 1 4 6 5 3 8 12 10 7
Niveles: 7 3 10 1 5 8 12 4 6
Iteracion por sucesor: 1 3 4 5 6 7 8 10 12
Sucesor de 5: 6
Predecesor de 5: 4
Primer nodo inorden: 1
Ultimo nodo inorden: 12
Altura estructural: 3
Profundidad de 5: 2
Parent links OK: si
```

### Pruebas públicas ejecutadas:

```
$ ctest --test-dir build-debug -C Debug -R semana5 --output-on-failure
Test project C:/Users/AXEL/OneDrive/Escritorio/uni/2026-1/AED/Repositorio/Personal/CC232/Libreria_cc232/build-debug
    Start 20: semana5_public
1/2 Test #20: semana5_public ...................   Passed    0.10 sec
    Start 21: semana5_internal
2/2 Test #21: semana5_internal .................   Passed    0.10 sec

100% tests passed, 0 tests failed out of 2

Total Test time (real) =   0.22 sec
```
*Nota: Se confirma que el entorno de desarrollo está correctamente configurado y que los algoritmos de recorrido de árboles binarios funcionan según lo esperado*

## Bloque 1 - Núcleo conceptual de la semana

Revisamos:
* `Semana5/README.md`
* `Semana5/lecturas/Notas.md`
* `Semana5/include/BinNode.h`
* `Semana5/include/BinTree.h`
* `Semana5/include/BinaryTree.h`
* `Semana5/include/BinarySearchTree.h`
* `Semana5/include/BinaryHeap.h`

### 1. Explica con tus palabras qué diferencia hay entre un árbol binario enlazado y un árbol binario almacenado implícitamente en un arreglo.
En un árbol enlazado, los nodos se conectan físicamente usando punteros de memoria dinámica. En un árbol implícito (como un arreglo), no existen punteros; las relaciones entre padres e hijos se calculan matemáticamente usando los índices (por ejemplo, el hijo izquierdo está en la posición `2i + 1`).

### 2. Explica qué información guarda un BinNode: dato, padre, hijo izquierdo, hijo derecho y altura.
El `BinNode` almacena el valor del nodo (`dato`), punteros hacia sus descendientes (`hijo izquierdo` y `derecho`), un puntero hacia su ancestro directo (`padre`) y su `altura` en la estructura, la cual es una métrica clave para aplicar algoritmos de balanceo en el futuro.

### 3. Explica por qué el puntero parent permite implementar operaciones como succ(), pred() y actualización ascendente de alturas.
Porque nos permite retroceder hacia la raíz sin necesidad de usar estructuras auxiliares como una pila. Esto es indispensable para buscar sucesores escalando por el árbol, o para recalcular las alturas de los ancestros inmediatamente después de insertar o eliminar un nodo.

### 4. Explica qué responsabilidad tiene BinTree frente a BinNode.
Mientras que `BinNode` solo gestiona su información local y sus conexiones vecinas, `BinTree` administra la estructura completa. Es responsable de ubicar la raíz, rastrear el tamaño total (`size`) y coordinar operaciones globales, como cortar o unir subárboles completos.

### 5. Explica qué agrega BinaryTree sobre la infraestructura base de BinTree.
`BinaryTree` añade una capa de herramientas de navegación y depuración sobre la base estructural de `BinTree`. Incorpora utilidades como iteradores, cálculo de profundidad, y métodos para imprimir el árbol de forma visual en consola.

### 6. Explica qué propiedad adicional convierte un árbol binario en un BinarySearchTree.
Le añade la propiedad de orden total. Impone la regla estricta de que, para cualquier nodo, todos los elementos de su rama izquierda deben ser menores y los de su rama derecha mayores. Esto permite realizar búsquedas descartando mitades de la estructura en cada paso.

### 7. Explica qué propiedad adicional convierte un arreglo en un BinaryHeap mínimo.
Introduce la propiedad de montículo (prioridad). Esta regla asegura que cualquier nodo padre siempre tenga un valor menor o igual al de sus hijos, garantizando que el elemento más pequeño de todo el arreglo siempre se ubique en la raíz (índice 0).

### 8. Compara la propiedad de orden de un BST con la propiedad de prioridad de un heap.
El BST mantiene un orden estricto de izquierda a derecha (los menores a un lado, los mayores al otro). El Heap solo mantiene un orden vertical y parcial: al padre solo le importa ser menor que sus hijos, pero no impone ningún tipo de ordenamiento entre los hermanos.

### 9. Explica por qué un recorrido inorden de un BST produce una secuencia ordenada.
Porque el recorrido inorden sigue la secuencia "Izquierda, Nodo, Derecha". Como en un BST los menores ya están agrupados a la izquierda y los mayores a la derecha, aplicar este patrón extrae los valores de forma natural de menor a mayor.

### 10. Explica por qué un heap no permite, por sí solo, recorrer los elementos en orden sin destruir o copiar la estructura.
Porque el heap solo sabe con certeza quién es el mínimo absoluto (la raíz). Para descubrir cuál es el segundo menor, es obligatorio extraer la raíz y dejar que el heap se reorganice internamente (`trickleDown`). Por lo tanto, leerlos todos en orden implica vaciar la estructura original o trabajar sobre una copia.

## Bloque 2 - Navegación, altura, profundidad y tamaño

Revisamos:
* `Semana5/include/BinNode.h`
* `Semana5/include/BinTree.h`
* `Semana5/include/BinaryTree.h`
* `Semana5/demos/demo_binary_tree.cpp`

### 1. En `BinNode`, explica qué significan `hasLeft()`, `hasRight()`, `isRoot()`, `isLeaf()`, `isLeftChild()` e `isRightChild()`.
Son métodos booleanos de consulta para conocer el estado local de un nodo sin acceder directamente a sus punteros:

* **`hasLeft()` / `hasRight()`:** Indica si el nodo tiene un hijo izquierdo o derecho válido (puntero distinto de nulo).
* **`isRoot()`:** Indica si el nodo es la raíz del árbol (su puntero `parent` es nulo).
* **`isLeaf()`:** Indica si el nodo es una hoja (no tiene hijo izquierdo ni derecho).
* **`isLeftChild()` / `isRightChild()`:** Indica si este nodo es el hijo izquierdo (o derecho) de su respectivo padre.

### 2. Explica el caso en que `succ()` baja al subárbol derecho y luego busca el nodo más a la izquierda.
El recorrido inorden sigue la regla "Izquierda, Nodo, Derecha". Si estamos en un nodo y este tiene un hijo derecho, significa que ya terminamos con él y ahora debemos visitar su subárbol derecho. Dentro de ese subárbol derecho, el primer elemento que debe visitarse por regla inorden es el que esté más a la izquierda posible.

### 3. Explica el caso en que `succ()` sube por los ancestros hasta encontrar el primer giro hacia la izquierda.
Si un nodo no tiene hijo derecho, significa que terminamos de procesar toda su rama. Para encontrar el siguiente, debemos retroceder (subir). Mientras subamos siendo un "hijo derecho", significa que estamos terminando las ramas derechas de nuestros ancestros. El sucesor será el primer padre al que lleguemos desde su lado izquierdo, porque eso indica que acabamos de procesar su subárbol izquierdo y ahora le toca el turno a ese padre.

### 4. Explica simétricamente cómo debe funcionar `pred()`.
El predecesor es el espejo exacto del sucesor. Sigue dos casos:

* Si el nodo tiene hijo izquierdo, el predecesor es el nodo más a la derecha de ese subárbol izquierdo.
* Si no tiene hijo izquierdo, debemos subir por el árbol mientras seamos un "hijo izquierdo". El predecesor será el primer padre al que lleguemos desde su lado derecho.

### 5. Dibuja un árbol de al menos 7 nodos y marca el sucesor y predecesor inorden de tres nodos distintos.

```text
      D
     / \
    B   F
   / \ / \
  A  C E  G
```

Secuencia Inorden: A, B, C, D, E, F, G

Análisis de tres nodos distintos:

Para el nodo B:
- Predecesor: A (es el nodo más a la derecha de su subárbol izquierdo).
- Sucesor: C (es el nodo más a la izquierda de su subárbol derecho).

Para el nodo C:
- Predecesor: B (al no tener hijo izquierdo, sube y es hijo derecho de B).
- Sucesor: D (al no tener hijo derecho, sube siendo hijo derecho hasta llegar a D por la izquierda).

Para el nodo D (la raíz):
- Predecesor: C (el más a la derecha de su subárbol izquierdo).
- Sucesor: E (el más a la izquierda de su subárbol derecho).

### 6. Explica qué calcula depth(u) y por qué puede implementarse subiendo por parent.
La profundidad (depth) calcula la distancia (cantidad de aristas) desde la raíz del árbol hasta el nodo u. Como en un árbol cada nodo tiene un único camino válido hacia la raíz, la forma más sencilla de implementarlo es usar un contador y subir de padre en padre usando el puntero parent hasta que este sea nulo.

### 7. Explica qué calcula height(u) y por qué suele implementarse bajando recursivamente por los hijos.
La altura (height) calcula la distancia máxima desde el nodo u hasta su hoja más lejana. Se implementa recursivamente hacia abajo porque la altura de un nodo depende estrictamente de la altura de sus hijos (es igual a 1 + max(altura_izq, altura_der)). El nodo necesita "preguntar" a sus descendientes cuál es su rama más larga para poder calcular la suya.

### 8. Explica qué calcula subtreeSize(u).
Calcula la cantidad total de nodos que conforman el subárbol donde u es la raíz. Esto incluye al propio nodo u más todos sus descendientes (tanto por la izquierda como por la derecha).

### 9. Demuestra que para todo nodo u se cumple depth(u) + height(u) <= height(T).
- height(T) es la longitud del camino más largo desde la raíz hasta la hoja más profunda de todo el árbol.
- Para cualquier nodo u, depth(u) es la distancia desde la raíz hasta u.
- height(u) es la distancia desde u hasta su hoja más profunda.
- Al sumar depth(u) + height(u), estamos midiendo la longitud de un camino específico que va desde la raíz hasta una hoja pasando obligatoriamente por u.
- Dado que height(T) es, por definición, el camino máximo absoluto del árbol entero, el camino que pasa por u no puede ser mayor que este máximo absoluto, lo que demuestra la desigualdad.

### 10. Indica la condición necesaria y suficiente para que se alcance la igualdad anterior.
La igualdad depth(u) + height(u) == height(T) se cumple única y exclusivamente si el nodo u forma parte de la rama más larga (o una de las ramas más largas, si hay empates) de todo el árbol T.

## Bloque 3 - Recorridos y trazado guiado

Revisamos:

* `Semana5/include/BinNode.h`
* `Semana5/include/BinTree.h`
* `Semana5/demos/demo_binary_tree.cpp`
* `Semana5/demos/demo_capitulo5_panorama.cpp`


### 3. Análisis de Recorridos en Árboles Binarios

A partir de la ejecución de `demo_binary_tree.cpp` y el código fuente en `BinNode.h`, se presenta el análisis de los nueve recorridos implementados en el curso.

| Recorrido | Versión revisada | Estructura auxiliar usada | Secuencia producida en el árbol de prueba | Argumento de correctitud y costo |
| :--- | :--- | :--- | :--- | :--- |
| **Preorden** | Recursiva | Pila de llamadas del sistema (Call Stack) | 7 3 1 5 4 6 10 8 12 | **Correctitud:** Visita el nodo antes de delegar la recursión a sus hijos (N-I-D).<br>**Costo:** O(n) en tiempo y O(h) en espacio por la profundidad máxima de llamadas. |
| **Preorden** | Iterativa 2 | Pila explícita (`std::stack`) | 7 3 1 5 4 6 10 8 12 | **Correctitud:** Visita el tope de la pila, luego empuja primero el hijo derecho y después el izquierdo para simular el orden N-I-D al desapilar.<br>**Costo:** O(n) en tiempo y O(h) en memoria para la pila. |
| **Inorden** | Recursiva | Pila de llamadas del sistema (Call Stack) | 1 3 4 5 6 7 8 10 12 | **Correctitud:** Llama a la rama izquierda, visita el nodo, y luego llama a la rama derecha (I-N-D).<br>**Costo:** O(n) en tiempo y O(h) en espacio auxiliar. |
| **Inorden** | Iterativa 1 | Pila explícita (`std::stack`) | 1 3 4 5 6 7 8 10 12 | **Correctitud:** Baja por la izquierda apilando todo hasta llegar a nulo, desapila, visita el nodo, y se mueve un paso a la derecha.<br>**Costo:** O(n) en tiempo y O(h) en espacio. |
| **Inorden** | Iterativa 2 | Punteros locales (`prev`, `curr`, `next`) | 1 3 4 5 6 7 8 10 12 | **Correctitud:** Rastrea la proveniencia del movimiento (desde el padre, hijo izquierdo o hijo derecho) usando el puntero `parent` para decidir si bajar, visitar o subir, emulando la recursión.<br>**Costo:** O(n) en tiempo y **O(1)** en memoria extra. |
| **Inorden** | Iterativa 3 | Puntero a función (`succ()`) | 1 3 4 5 6 7 8 10 12 | **Correctitud:** Comienza en el nodo más a la izquierda (`leftmost`) y salta estrictamente usando el algoritmo del sucesor inorden hasta llegar al final.<br>**Costo:** O(n) amortizado en tiempo y **O(1)** en memoria extra. |
| **Postorden** | Recursiva | Pila de llamadas del sistema (Call Stack) | 1 4 6 5 3 8 12 10 7 | **Correctitud:** Llama recursivamente a los hijos izquierdo y derecho antes de visitar el nodo actual (I-D-N).<br>**Costo:** O(n) en tiempo y O(h) en memoria. |
| **Postorden** | Iterativa | Doble pila (`std::stack`) | 1 4 6 5 3 8 12 10 7 | **Correctitud:** La primera pila procesa en orden N-D-I y transfiere los nodos a la segunda pila. Al vaciar la segunda, se invierte el orden quedando el correcto I-D-N.<br>**Costo:** O(n) en tiempo y O(n) estricto en memoria auxiliar. |
| **Niveles** | Iterativa | Cola (`std::queue`) | 7 3 10 1 5 8 12 4 6 | **Correctitud:** Explora en anchura (Breadth-First). Encola la raíz, visita, y encola sus hijos garantizando el procesamiento estricto capa por capa.<br>**Costo:** O(n) en tiempo y O(w) en memoria, siendo 'w' el ancho máximo del árbol. |

### 1. ¿Qué significa visitar un nodo en preorden?
Significa procesar o leer el valor del nodo actual antes de visitar a cualquiera de sus descendientes. El flujo siempre sigue el orden: Nodo, Izquierda, Derecha.

### 2. ¿Qué significa visitar un nodo en inorden?
Significa visitar el nodo actual justo en el medio, después de haber procesado todo su subárbol izquierdo, pero antes de entrar a su subárbol derecho. Sigue el orden: Izquierda, Nodo, Derecha.

### 3. ¿Qué significa visitar un nodo en postorden?
Significa dejar el procesamiento del nodo actual para el final, es decir, solo se visita la raíz local después de haber recorrido por completo sus hijos izquierdo y derecho. Sigue el orden: Izquierda, Derecha, Nodo.

### 4. ¿Qué significa visitar un árbol por niveles?
Significa recorrer la estructura en anchura (de arriba hacia abajo y de izquierda a derecha), terminando de procesar absolutamente todos los nodos de una misma capa o profundidad antes de bajar al siguiente nivel.

### 5. ¿Por qué los recorridos recursivos tienen tiempo O(n)?
Porque visitan cada nodo del árbol exactamente una sola vez, realizando una cantidad constante de operaciones (O(1)) en cada parada. Al sumar todas las visitas, el tiempo total es directamente proporcional a la cantidad de nodos.

### 6. ¿Por qué las versiones iterativas también tienen tiempo O(n)?
Porque la lógica subyacente es exactamente la misma. Aunque no usen recursión, cada nodo entra y sale de la pila (o es transitado mediante punteros locales) un número fijo de veces, por lo que el esfuerzo final sigue siendo proporcional al total de elementos.

### 7. ¿Cuál es la memoria auxiliar de un recorrido recursivo en un árbol balanceado?
Es O(log n). Al estar balanceado, la profundidad máxima de las llamadas recursivas (el tamaño del Call Stack) coincide con la altura del árbol, la cual es logarítmica respecto al número de nodos.

### 8. ¿Cuál es la memoria auxiliar de un recorrido recursivo en un árbol degenerado?
Es O(n). En un árbol degenerado (que tiene forma de lista enlazada), la recursión tiene que bajar hasta el último nodo antes de empezar a cerrarse, acumulando $n$ llamadas simultáneas en la pila del sistema.

### 9. ¿Qué diferencia hay entre usar una pila explícita y usar la pila de llamadas?
La pila de llamadas (Call Stack) la maneja el sistema operativo de forma automática durante la recursión y tiene un límite de memoria muy estricto (alto riesgo de *Stack Overflow*). Una pila explícita (`std::stack`) la controlamos nosotros en el código y usa la memoria dinámica general de la computadora (el Heap), permitiendo procesar árboles inmensamente más profundos sin colapsar.

### 10. ¿Por qué la cola del recorrido por niveles puede crecer mucho más en un árbol completo que en un árbol degenerado?
En un árbol degenerado, cada nivel tiene solo 1 nodo, así que la cola nunca pasa de tamaño 1 o 2. Por el contrario, en un árbol completo la cola almacena los nodos capa por capa; al llegar al nivel más profundo, la cola tiene que guardar a todas las hojas a la vez, las cuales representan aproximadamente la mitad del total de nodos del árbol, consumiendo una memoria auxiliar de O(n).

## Bloque 4 - Demostración: evidencia observable

Revisamos y ejecutamos:

* `Semana5/demos/demo_binary_tree.cpp`
* `Semana5/demos/demo_bst.cpp`
* `Semana5/demos/demo_heap.cpp`
* `Semana5/demos/demo_capitulo5_panorama.cpp`

### Tabla de análisis de demos

### 4. Análisis de Demostraciones y Ejecución

A partir de las salidas obtenidas en la terminal, se presenta el análisis de los cuatro programas de demostración que validan las estructuras desarrolladas en la semana.

| Archivo | Salida u observable importante | Idea estructural | Argumento de costo, espacio o diseño |
| :--- | :--- | :--- | :--- |
| `demo_binary_tree.cpp` | Representación visual del árbol, verificación de enlaces y secuencias idénticas en todas las versiones de un mismo recorrido (ej. los tres inorden iterativos dan la misma salida). | El árbol binario base se construye usando punteros explícitos. La navegación se apoya fuertemente en el puntero `parent` para hallar sucesores, predecesores y calcular profundidades sin recursión. | Los recorridos toman tiempo O(n). Usar el puntero `parent` mejora el diseño espacial, permitiendo hallar el sucesor en tiempo O(h) y memoria O(1), evitando el uso de pilas auxiliares. |
| `demo_bst.cpp` | El recorrido inorden produce una secuencia ordenada. Las búsquedas exactas y por cota (`lowerBound`, `upperBound`) funcionan correctamente. Se observa la reestructuración tras `remove` y `rotateLeft`. | Al ser un Árbol Binario de Búsqueda, la estructura impone una propiedad de orden. Cada comparación descarta un subárbol, y las rotaciones permiten modificar la topología sin romper este orden. | Las operaciones `add`, `remove` y `find` cuestan O(h). La demostración incluye la construcción de un BST balanceado desde un arreglo, lo que garantiza h = O(log n) y previene la degradación a O(n). |
| `demo_heap.cpp` | El arreglo original se reordena con `Heapify`. Al insertar o eliminar, el menor siempre queda en la cima. Extraer todos los elementos consecutivamente genera una secuencia ordenada. | Implementación de una Cola de Prioridad usando un Heap binario mínimo sobre un arreglo implícito. Las relaciones padre-hijo se calculan con índices (`2i+1`, `2i+2`), sin usar punteros. | El diseño implícito ahorra la memoria de los punteros (espacio extra O(1)). `add` y `remove` toman O(log n) por el hundimiento/flote, y `Heapify` construye la estructura inicialmente en tiempo lineal O(n). |
| `demo_capitulo5_panorama.cpp` | Acceso directo al mínimo del Heap (`1`). Para el BST, se visualiza la raíz y se recorre usando un bucle `for` moderno (`for (int x : bst)`), produciendo una lista ordenada. | Integra ambos conceptos destacando sus casos de uso: el Heap para obtener la máxima prioridad al instante y el BST para permitir navegación ordenada e iteración estándar. | El diseño de iteradores de C++ (`begin()`, `end()`, `operator++`) sobre el BST encapsula la lógica de `succ()`, permitiendo al usuario recorrer la estructura en tiempo amortizado O(1) por paso sin conocer su interior. |

### Evidencias de Compilación y Ejecución

#### `demo_binary_tree.cpp`
```
$ ./sem5_demo_binary_tree.exe
Arbol:
│       ┌── 12
│   ┌── 10
│   │   └── 8
└── 7
    │       ┌── 6
    │   ┌── 5
    │   │   └── 4
    └── 3
        └── 1
Preorden recursivo: 7 3 1 5 4 6 10 8 12
Preorden iterativo: 7 3 1 5 4 6 10 8 12
Inorden recursivo: 1 3 4 5 6 7 8 10 12
Inorden iterativo #1: 1 3 4 5 6 7 8 10 12
Inorden iterativo #2: 1 3 4 5 6 7 8 10 12
Inorden iterativo #3: 1 3 4 5 6 7 8 10 12
Postorden recursivo: 1 4 6 5 3 8 12 10 7
Postorden iterativo: 1 4 6 5 3 8 12 10 7
Niveles: 7 3 10 1 5 8 12 4 6
Iteracion por sucesor: 1 3 4 5 6 7 8 10 12
Sucesor de 5: 6
Predecesor de 5: 4
Primer nodo inorden: 1
Ultimo nodo inorden: 12
Altura estructural: 3
Profundidad de 5: 2
Parent links OK: si
```

#### `demo_bst.cpp`
```
$ ./sem5_demo_bst.exe
BST:
│       ┌── 12
│   ┌── 10
│   │   └── 8
└── 7
    │       ┌── 6
    │   ┌── 5
    │   │   └── 4
    └── 3
        └── 1
BST inorden: 1 3 4 5 6 7 8 10 12
findEQ(5): 5
lowerBound(9): 10
upperBound(8): 10
findLast(9): 8
Tras remove(3): 1 4 5 6 7 8 10 12
Tras rotateLeft(root):
│   ┌── 12
└── 10
    │   ┌── 8
    └── 7
        │       ┌── 6
        │   ┌── 5
        └── 4
            └── 1
BST balanceado desde vector ordenado:
│       ┌── 9
│   ┌── 8
│   │   └── 7
│   │       └── 6
└── 5
    │   ┌── 4
    └── 3
        └── 2
            └── 1
isBST: si
```

#### `demo_heap.cpp`
```
$ ./sem5_demo_heap.exe
Heapify: 1 3 2 7 5 8 10
isHeap: si
Tras add(0): 0 1 2 3 5 8 10 7
remove() -> 0
Tras remove(): 1 3 2 7 5 8 10
Secuencia ordenada por extraccion: 1 2 3 5 7 8 10
```

#### `demo_capitulo5_panorama.cpp`
```
$ ./sem5_demo_capitulo5_panorama.exe
Semana 5 final: BinaryTree, BST, heap, recorridos iterativos y utilidades
Heap minimo actual: 1
Raiz BST: 9
Altura BST: 2
Arbol BST:
│       ┌── 15
│   ┌── 12
│   │   └── 10
└── 9
    │   ┌── 7
    └── 4
        └── 2
Recorrido STL-like: 2 4 7 9 10 12 15
```

### 1. En `demo_binary_tree.cpp`, ¿qué salida permite verificar que los recorridos visitan los nodos en el orden esperado?
Las líneas que imprimen las secuencias de los recorridos. Al comprobar que todas las variantes de un mismo método (por ejemplo, el inorden recursivo y los tres iterativos) generan exactamente la misma secuencia numérica (`1 3 4 5 6 7 8 10 12`), se confirma empíricamente que la lógica de visita funciona bien sin importar cómo esté programada internamente.

### 2. ¿Qué parte de la demo permite defender que `succ()` y `pred()` respetan el orden inorden?
La línea `Iteracion por sucesor: 1 3 4 5 6 7 8 10 12`. Esta salida es idéntica a la del recorrido inorden clásico. Además, las pruebas individuales (`Sucesor de 5: 6` y `Predecesor de 5: 4`) calzan perfectamente con la posición que tienen esos números en la secuencia ordenada.

### 3. ¿Qué evidencia produce la representación ASCII del árbol?
Produce una confirmación visual e instantánea de la topología (la "forma") del árbol. Permite comprobar a simple vista quién es hijo de quién, de qué lado están conectados (izquierda o derecha) y si la altura que calcula el programa tiene sentido físico en la realidad.

### 4. En `demo_bst.cpp`, ¿qué observable permite defender que el inorden del BST queda ordenado?
La salida directa de la línea `BST inorden: 1 3 4 5 6 7 8 10 12`. Con solo mirarla, se evidencia que los números han perdido el orden en el que fueron insertados originalmente y ahora siguen una secuencia matemática estricta de menor a mayor.

### 5. ¿Qué operaciones de búsqueda se distinguen mejor en la demo del BST: `find`, `findEQ`, `lowerBound` o `upperBound`?
Se distingue perfectamente la diferencia entre la búsqueda exacta y la búsqueda por cota. Mientras `findEQ(5)` devuelve un valor exacto que sí existe, `lowerBound(9)` y `upperBound(8)` demuestran la utilidad real del BST: son capaces de devolver el valor más cercano hacia arriba (ambos devuelven `10`) cuando se les pide un límite o se busca un elemento que no está en el árbol.

### 6. En `demo_heap.cpp`, ¿qué salida permite defender que el mínimo queda en la raíz?
Las impresiones del arreglo interno. Tanto en `Heapify: 1 3 2...` como en `Tras add(0): 0 1 2...`, se observa que el número más pequeño siempre ocupa físicamente la primera posición del arreglo (índice 0). Esto se ratifica cuando `remove()` expulsa exactamente ese número inicial.

### 7. ¿Qué evidencia permite distinguir entre insertar con `add()` y construir con `heapify()`?
Se nota en cómo procesan los datos. `Heapify` toma el arreglo desordenado original y lo reestructura de golpe, aplicando la propiedad de montículo a todos los elementos a la vez. En cambio, `add(0)` evidencia un reacomodo individual: inserta un solo elemento y lo hace "flotar" hasta la primera posición sin alterar innecesariamente a los demás.

### 8. En `demo_capitulo5_panorama.cpp`, ¿qué comparación resume mejor la semana: árbol enlazado, BST o heap?
La forma en que cada estructura expone su información. El Heap demuestra su propósito al dar la máxima prioridad al instante (`Heap minimo actual: 1`). El BST, por otro lado, demuestra su capacidad de mantener el orden y permitir navegación fluida al dejar que un simple bucle `for` de C++ extraiga todos sus datos de menor a mayor (`Recorrido STL-like: 2 4...`). Es el resumen perfecto de la semana: el Heap es para urgencia y el BST es para estructura y orden.

## Bloque 5 - Pruebas públicas, pruebas internas e invariantes

Revisamos:

* `Semana5/pruebas_publicas/test_public_week5.cpp`
* `Semana5/pruebas_internas/test_internal_week5.cpp`


### 1. ¿Qué operaciones del BST valida la prueba pública?
Valida la inserción (`add`), eliminación (`remove`), búsquedas exactas y por cota (`findEQ`, `lowerBound`, `upperBound`), extracción de extremos (`minNode`, `maxNode`), validación de la propiedad (`isBST`) y la creación de un árbol balanceado (`buildBalancedFromSorted`).

### 2. ¿Qué casos validan que el BST no acepta duplicados?
La prueba inserta los números iniciales y luego hace la aserción `!bst.add(5)`. Como el 5 ya existe, espera que la función rechace la inserción y retorne `false`.

### 3. ¿Qué se verifica al comparar el inorden recursivo con las versiones iterativas?
Se verifica empíricamente que la lógica de los algoritmos iterativos es correcta, al asegurar que las cuatro versiones generen la misma secuencia ordenada de números sin perder o duplicar nodos.

### 4. ¿Qué se espera de findEQ(8) en la prueba pública?
Se espera que busque y retorne el puntero directo al nodo que contiene exactamente el valor 8, demostrando una búsqueda de coincidencia exacta exitosa.

### 5. ¿Qué se espera de lowerBound(9) y upperBound(8)?
Ambas operaciones deben devolver el nodo con valor 10. `lowerBound(9)` busca el primer número mayor o igual a 9, y `upperBound(8)` busca el primer número estrictamente mayor a 8. Esto valida las búsquedas por rangos o cotas.

### 6. ¿Qué propiedad se valida con isBST()?
Valida que todo el árbol respete estrictamente su invariante de orden: que cada nodo sea mayor que toda su rama izquierda y menor que toda su rama derecha, además de verificar que los punteros al padre no estén rotos.

### 7. ¿Qué se valida después de eliminar un nodo con remove()?
Se confirma que el elemento ya no esté en el árbol (`!contains(3)`), que el recorrido inorden siga siendo una secuencia perfecta de menor a mayor y que los enlaces de los punteros no hayan quedado apuntando a la nada.

### 8. ¿Qué valida checkParentLinks() después de borrar, separar o adjuntar subárboles?
Garantiza la integridad estructural. Verifica que la relación bidireccional se mantenga: si el nodo A apunta a B como su hijo, B obligatoriamente debe apuntar a A como su padre. Ningún nodo puede quedar "huérfano".

### 9. ¿Qué operaciones del heap valida la prueba pública?
Valida la construcción masiva desde un vector (`heapify`), la revisión de estructura válida (`isHeap`, `isHeapArray`) y la extracción constante del elemento más pequeño (`remove`).

### 10. ¿Qué demuestra extraer repetidamente de un min-heap hasta vaciarlo?
Demuestra indirectamente el funcionamiento del algoritmo de ordenamiento "HeapSort". Al extraer siempre el nodo raíz (que es el mínimo garantizado), los elementos salen perfectamente ordenados de menor a mayor.

### 11. ¿Qué operaciones de BinTree se validan con attachAsRC, secede y removeSubtree?
Demuestran el manejo de árboles a nivel macro. Validan que se pueda pegar un árbol externo como rama (`attachAsRC`), cortarlo para volverlo independiente (`secede`) o destruirlo por completo (`removeSubtree`), manteniendo actualizados los tamaños totales (`size`).

### 12. ¿Qué agregan las pruebas internas respecto a rotaciones, bubbleUp, trickleDown, profundidad, altura, sucesor y predecesor?
Revisan la mecánica fina debajo del capó. Confirman que girar el BST (`rotateLeft/Right`) cambia la raíz sin romper el orden, que `bubbleUp/trickleDown` realmente mueven los datos en el Heap, y que las matemáticas para calcular `depth`, `height` y moverse con `succ()/pred()` son exactas.

### 13. ¿Qué sí demuestra pasar las pruebas públicas?
Demuestra que tu código hace lo que pide el problema para casos de uso normales, que no tiene errores de sintaxis y que las salidas concuerdan con los resultados previstos por el profesor.

### 14. ¿Qué no demuestra pasar las pruebas públicas?
No garantiza que tu código sea óptimo en tiempo, ni que no existan fugas de memoria (memory leaks), ni asegura que el programa soporte casos extremos o maliciosos (por ejemplo, insertar una lista ordenada enorme que cause un Stack Overflow en el modo recursivo).

### 15. ¿Por qué una defensa correcta debe mencionar invariantes y complejidad además de resultados observables?
Porque en Estructuras de Datos, que un código "arroje el resultado correcto" es solo la mitad del trabajo. Debes argumentar que respeta las reglas matemáticas (invariantes) y que es eficiente en memoria y tiempo (complejidad), garantizando que la estructura aguantará cuando se use a gran escala.

## Bloque 6 - Lectura cercana: BinNode, BinTree y BinaryTree

Revisamos:

* `Semana5/include/BinNode.h`
* `Semana5/include/BinTree.h`
* `Semana5/include/BinaryTree.h`

### 7. Análisis del Código Fuente: BinNode, BinTree y BinaryTree

### 1. En BinNode, ¿qué invariantes deben mantenerse entre parent, left y right?
Debe existir una relación bidireccional perfecta. Si un nodo A tiene como `left` o `right` a un nodo B, entonces el puntero `parent` del nodo B debe apuntar obligatoriamente de vuelta al nodo A.

### 2. ¿Por qué insertAsLC e insertAsRC deben rechazar una inserción cuando el hijo correspondiente ya existe?
Para evitar sobrescribir el puntero existente. Si se sobrescribe sin cuidado, perderíamos para siempre el acceso al subárbol que ya estaba ahí, provocando una grave fuga de memoria (memory leak) y rompiendo la estructura.

### 3. Explica cómo size() de BinNode recorre el subárbol.
Funciona de manera recursiva. El nodo se cuenta a sí mismo (1) y luego suma el resultado de llamar a `size()` en su hijo izquierdo y a `size()` en su hijo derecho. Si un hijo es nulo, suma 0.

### 4. Explica cómo funcionan leftmost() y rightmost().
Parten del nodo actual y usan un bucle `while` para bajar en línea recta. `leftmost()` avanza continuamente por los punteros `left` hasta encontrar un nulo, mientras que `rightmost()` hace lo mismo por los punteros `right`. Así encuentran los extremos del subárbol.

### 5. Explica paso a paso cómo funciona succ().
Tiene dos escenarios:
1. Si el nodo tiene hijo derecho, baja a ese hijo y luego busca su `leftmost()` (el más a la izquierda de esa rama).
2. Si no tiene hijo derecho, sube por el árbol usando el `parent` mientras siga siendo un "hijo derecho". El sucesor es el primer ancestro al que llegue proveniente desde la izquierda.

### 6. Explica paso a paso cómo funciona pred().
Es el espejo exacto de `succ()`.
1. Si tiene hijo izquierdo, baja a él y busca su `rightmost()`.
2. Si no tiene hijo izquierdo, sube por el árbol mientras siga siendo un "hijo izquierdo". El predecesor es el primer ancestro al que llegue proveniente desde la derecha.

### 7. En BinTree, ¿qué papel cumplen root_ y size_?
Son el núcleo administrativo global. `root_` es el ancla principal que da acceso a todo el árbol. `size_` lleva el conteo total de nodos actualizados en tiempo real, permitiendo consultar el tamaño en O(1) sin tener que recorrer toda la estructura.

### 8. Explica qué hace updateHeight(Node*).
Recalcula la altura de un nodo específico evaluando a sus dos hijos. Toma la altura de su rama izquierda, la altura de su rama derecha, elige la máxima y le suma 1.

### 9. Explica qué hace updateHeightAbove(Node*) y por qué sube hacia la raíz.
Llama a `updateHeight()` en el nodo actual y usa un bucle para repetir el proceso con su padre, su abuelo, y así sucesivamente hasta la raíz. Esto es vital porque insertar o eliminar un nodo altera la longitud de la rama, afectando en cascada las alturas de todos sus ancestros directos.

### 10. Explica cómo attachAsLC o attachAsRC transfieren un subárbol desde un árbol hacia otro.
Toman la raíz del árbol donante (`subtree`) y la enlazan como hijo del nodo `parent` en el árbol receptor. Luego, suman el tamaño del donante al receptor, recalculan alturas y "vacían" el árbol donante (poniendo su raíz a nulo) para que no haya dos estructuras controlando los mismos nodos en memoria.

### 11. Explica qué diferencia hay entre removeSubtree y secede.
Ambas operaciones cortan una rama completa del árbol. La diferencia radica en el destino: `removeSubtree` destruye los nodos y libera su memoria (`delete`), mientras que `secede` encapsula esa rama cortada en un nuevo objeto `BinTree` y te lo devuelve intacto para seguir usándolo.

### 12. Explica por qué secede no debe destruir los nodos desprendidos.
Porque su propósito es "separar" o extraer una porción útil del árbol para que siga existiendo como una estructura independiente. Si usara `delete`, destruiría los datos que el usuario está intentando recuperar.

### 13. Explica por qué removeSubtree sí debe liberar nodos.
Porque su propósito es eliminar permanentemente esa rama. Si solo cortara los enlaces sin usar `delete`, esa rama quedaría "flotando" en la memoria RAM inaccesible, provocando una fuga de memoria (memory leak).

### 14. Explica qué verifica checkParentLinks().
Audita todo el árbol de forma recursiva para comprobar que los enlaces dobles no estén rotos. Confirma que la regla `nodo->hijo->parent == nodo` se cumpla en absolutamente todos los niveles.

### 15. En BinaryTree, explica cómo se implementan firstNode, lastNode, nextNode y prevNode.
Son envolturas (wrappers) que delegan el trabajo a los métodos del nodo base. `firstNode` devuelve el `leftmost()` de la raíz, y `lastNode` su `rightmost()`. `nextNode` simplemente llama al `succ()` del nodo recibido, y `prevNode` llama a su `pred()`.

### 16. Explica por qué un iterador basado en succ() produce recorrido inorden.
Porque la matemática detrás de `succ()` está diseñada para seguir estrictamente la regla "Izquierda, Nodo, Derecha". Al comenzar en el primer nodo inorden (el mínimo absoluto) y llamar a `succ()` en bucle, se reconstruye automáticamente el recorrido inorden completo, paso a paso.

### 17. Explica qué aporta asciiArt() para depuración y sustentación.
Genera un diagrama visual del árbol en la terminal. Esto es invaluable para depurar, ya que permite comprobar a simple vista si las ramas están del lado correcto y si la geometría del árbol tiene sentido, en lugar de intentar adivinar la forma leyendo una lista plana de números.