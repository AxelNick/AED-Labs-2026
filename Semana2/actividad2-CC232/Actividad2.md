# Actividad 2 - Semana 2

**Estudiante:**
Axel Alberto Reyes Baldeón

## Bloque 0 - Instalación y preparación

- [x] Dejé lista mi carpeta de trabajo
- [x] Acceso a Semana2, lecturas y archivos de entrega verificados
- [x] Archivo `actividad2_semana2.md` creado
- [x] Compilación y ejecución de demos y pruebas públicas completadas en mi máquina

### Compilación realizada en mi entorno local

```bash
cmake -S . -B build
cmake --build build --config Debug
```

### Demo ejecutada localmente

- **sem2_demo_array_basico.exe**
  ```text
  array.length = 5
  contenido: 10 20 30 40 50
  antes de la asignacion, b[0] = -1
  despues de b = a, b.length = 5
  b: 10 20 30 40 50
  nota: esta version de array usa una asignacion por transferencia de ownership.
  ```
  **Mi observación**: En la consola pude ver la creación del arreglo con 5 elementos, el acceso por índice y cómo la asignación transfiere el ownership sin hacer una copia profunda.

### Prueba pública ejecutada desde mi terminal

```text
Test project C:/Users/AXEL/OneDrive/Documentos/Codes/2026_1/Algoritmos y estructura de datos/CC-232-main/cc-232/CC-232/Libreria_cc232/Semana2/build
    Start 1: semana2_public
1/5 Test #1: semana2_public ...................   Passed    0.01 sec
    Start 2: semana2_internal
2/5 Test #2: semana2_internal .................   Passed    0.02 sec
    Start 3: semana2_resize_stress
3/5 Test #3: semana2_resize_stress ............   Passed    0.02 sec
    Start 4: semana2_public_cap2
4/5 Test #4: semana2_public_cap2 ..............   Passed    0.02 sec
    Start 5: semana2_internal_cap2
5/5 Test #5: semana2_internal_cap2 ............   Passed    0.02 sec

100% tests passed, 0 tests failed out of 5
Total Test time (real) =   0.09 sec
```
**Resultado**: **5/5 tests pasaron**. Comprobé que todas las pruebas públicas e internas funcionan correctamente en mi entorno.

## Bloque 1 - Núcleo conceptual de la semana

### Material Revisado:
- `Semana2/README.md`
- `Lectura4-Deng`
- `Lectura5-Morin`
- `Semana2/include/ArrayStack.h`
- `Semana2/include/FastArrayStack.h`
- `Semana2/include/RootishArrayStack.h`
- `Semana2/include/DengVector.h`

### 1. Expliquen con sus palabras qué significa que un arreglo use memoria contigua.

Entiendo que la memoria contigua significa que los elementos del arreglo se almacenan uno tras otro, ocupando posiciones consecutivas en mi memoria RAM sin espacios intermedios. La dirección física de cualquier elemento la puedo calcular mediante una fórmula lineal: `dirección = dirección_base + índice × tamaño_elemento`. Esta característica es el fundamento del acceso directo.

### 2. Expliquen por qué acceder a A[i] es una operación de costo O(1).

Acceder a un elemento por índice es O(1) porque mi CPU puede calcular directamente su dirección de memoria sin necesidad de recorrer elementos anteriores. Dado que el vector es contiguo, la operación se reduce a una simple suma y un acceso a memoria, que son operaciones de hardware con tiempo constante.

### 3. Expliquen la diferencia entre size y capacity.

- `size` es la cantidad **lógica** de elementos que realmente he almacenado en el vector. 
- `capacity` es la cantidad **física** de celdas que he reservado en la memoria. La capacidad siempre es ≥ al size. Noté que esta diferencia es la que permite crecer dinámicamente: cuando inserto algo, uso el espacio libre antes de tener que expandir.

### 4. Expliquen por qué un arreglo dinámico no puede crecer "en el mismo sitio" y necesita reservar un bloque nuevo al hacer resize().

Como un arreglo requiere memoria contigua, cuando se me agota la capacidad, no puedo simplemente "crecer" en el mismo sitio porque la RAM que viene inmediatamente después puede estar ocupada por otros datos de mi programa o del sistema operativo. 
Por eso comprendí que `resize()` debe: 
- Primero reservar un nuevo bloque más grande en otro lado.
- Después copiar todos los elementos antiguos al nuevo bloque.
- Y finalmente liberar el bloque antiguo de la memoria.

### 5. Expliquen por qué duplicar capacidad permite defender costo amortizado O(1) para inserciones al final.

Si duplico la capacidad, garantizo que entre dos expansiones sucesivas ocurran muchas inserciones. El costo total de expandir a lo largo de n inserciones es O(n) porque las expansiones forman una suma geométrica (costo 1, luego 2, luego 4, 8, 16... que suma ~2n). Al repartir esto entre n operaciones, me da O(1) por operación. Si yo decidiera crecer por una cantidad fija (como de 10 en 10), necesitaría muchas más expansiones y el costo se dispararía.

### 6. Comparen ArrayStack y DengVector: ¿qué comparten y qué cambia en interfaz o intención didáctica?

Ambos implementan un stack con arreglo dinámico. Al revisar el código, noté que `ArrayStack` (del autor Morin) es una implementación clásica y general que sirve de base. En cambio, `DengVector` (del autor Deng) tiene una intención más educativa; ilustra explícitamente los conceptos de size, capacity, expand(), shrink() y operaciones como inserción, eliminación y búsqueda. Comparten la misma lógica, pero el de Deng me pareció más completo para estudiar.

### 7. Expliquen qué mejora FastArrayStack respecto a ArrayStack.

`FastArrayStack` hereda de `ArrayStack` pero reemplaza los bucles manuales de copia que yo normalmente escribiría por rutinas optimizadas de C++ como `std::copy` y `std::copy_backward`. Esto no cambia la complejidad asintótica teórica, pero al ejecutarlo vi que mejora el rendimiento práctico porque esas rutinas de la librería estándar están ajustadas a bajo nivel y aprovechan instrucciones del procesador.

### 8. Expliquen cuál es la idea espacial central de RootishArrayStack

En lugar de usar un único arreglo grande que se duplica, me di cuenta de que usa múltiples bloques más pequeños de tamaños incrementales: 1, 2, 3, 4, 5... El primer bloque almacena 1 elemento, el segundo 2, etc. Estos bloques se guardan en un `ArrayStack<T*>` de punteros. La idea central es reducir el desperdicio masivo de memoria que genera duplicar arreglos grandes.

### 9. Expliquen por qué RootishArrayStack usa bloques de tamaños 1, 2, 3, ....

Al analizar el diseño matemático, identifiqué que asignar bloques con tamaños secuenciales (1, 2, 3, ..., b) tiene como objetivo resolver la ineficiencia espacial de los arreglos dinámicos sin perder velocidad. Se apoya en dos pilares:

* **Reducción drástica del espacio desperdiciado (de O(n) a O(√n)):**
Un vector tradicional duplica su capacidad al llenarse, desperdiciando memoria proporcional a los elementos (O(n)). El `RootishArrayStack`, al crecer de forma aritmética, requiere aproximadamente b ≈ √2n bloques para alojar n elementos. El desperdicio máximo se limita al espacio sobrante en el último bloque, reduciendo mi memoria inactiva a **O(√n)**.

* **Acceso directo en tiempo constante (O(1)):**
Aunque los datos se dividan en varios bloques distintos, ubicar un elemento no me exige iterar. Puedo calcular la ubicación física de cualquier índice lógico i resolviendo una inecuación cuadrática en tiempo **O(1)**.

**En conclusión:** Esta arquitectura elimina la gran penalización de memoria (O(n)) conservando la inmediatez matemática (O(1)) para lecturas y escrituras.

### 10. Expliquen qué relación hay entre representación, costo temporal y desperdicio espacial en estas estructuras.

Observo que la relación entre estos tres factores se define por un **trade-off** o compromiso estructural, donde para mejorar uno, debo sacrificar otro:

* **Representación y Tiempo:** Mantener una memoria estrictamente contigua (como en `ArrayStack`) me garantiza un acceso directo en O(1). Sin embargo, me penaliza el tiempo de modificación (O(n-i)), ya que me obliga a desplazar datos masivamente para no romper esa contigüidad.
* **Tiempo y Espacio:** Para que el crecimiento tenga un costo amortizado de O(1), estoy obligado a reservar mucha más memoria de la que uso (redimensionamiento geométrico). Esto asume deliberadamente un desperdicio espacial de orden O(n).
* **Flexibilización y Optimización:** Si fragmento la memoria física (como en `RootishArrayStack`), logro reducir el desperdicio a solo O(√n). A cambio, la sobrecarga matemática para calcular posiciones me aumenta el tiempo real de ejecución, aunque asintóticamente siga siendo el mismo.

## Bloque 2 - Demostración y trazado guiado

### Material Revisado:
- `Semana2/demos/demo_array_basico.cpp`
- `Semana2/demos/demo_arraystack.cpp`
- `Semana2/demos/demo_arraystack_explicado.cpp`
- `Semana2/demos/demo_fastarraystack.cpp`
- `Semana2/demos/demo_rootisharraystack.cpp`
- `Semana2/demos/demo_rootisharraystack_explicado.cpp`
- `Semana2/demos/demo_deng_vector.cpp`
- `Semana2/demos/demo_stl_vector_contraste.cpp`

### Tabla de análisis de demos

| Archivo | Salida u observable importante | Idea estructural | Argumento de costo o espacio |
| :--- | :--- | :--- | :--- |
| **`demo_array_basico.cpp`** | `b = a` cambia el dueño del arreglo. | Es un *wrapper* simple. Transfiere el puntero en lugar de hacer copia profunda. | Asignar cuesta O(1). Evito el costo de O(n) de copiar todo a mano. |
| **`demo_arraystack.cpp`** y **`_explicado`** | La consola detalla cómo los elementos se desplazan (izq/der) al insertar/eliminar. | Arreglo dinámico clásico contiguo con expansión geométrica. | Desplazar cuesta O(n-i). El redimensionamiento genera desperdicio de hasta O(n). |
| **`demo_fastarraystack.cpp`** | Resultados idénticos a `ArrayStack`, pero más rápidos en mi máquina. | Conserva contigüidad, pero usa `std::copy` o `memmove`. | Complejidad O(n-i), pero menor **constante de ejecución** por optimización de hardware. |
| **`demo_rootisharraystack.cpp`** y **`_explicado`** | Visualiza el mapeo de índices a bloques (`bloque b`, `offset j`). | Estructura basada en lista de bloques incrementales y ecuaciones cuadráticas. | Desperdicio baja a O(√n). El acceso aleatorio se mantiene en O(1). |
| **`demo_deng_vector.cpp`** | Muestra saltos de capacidad y copias independientes. | ADT vectorial completo con separación de `size` y `capacity`. | Inserción al final es O(1) amortizado. Eliminación por intervalo optimiza desplazamientos. |
| **`demo_stl_vector_contraste.cpp`** | Imprime el patrón de crecimiento geométrico de `capacity`. | Uso de `std::vector` como línea base para comparar mis implementaciones. | Valida el análisis amortizado: O(1) con costo espacial residual de O(n). |

### Evidencias de Ejecución Local

**Ejecución: demo_array_basico.cpp**
```text
$ ./sem2_demo_array_basico
array.length = 5
contenido: 10 20 30 40 50
antes de la asignacion, b[0] = -1
despues de b = a, b.length = 5
b: 10 20 30 40 50
nota: esta version de array usa una asignacion por transferencia de ownership.
```

**Ejecución: demo_arraystack.cpp**
```text
$ ./sem2_demo_arraystack
size = 3
10 15 20
remove(1) = 15
```

**Ejecución: demo_arraystack_explicado.cpp**
```text
$ ./sem2_demo_arraystack_explicado
ArrayStack explicado (Morin, capitulo 2)
Operacion 1: push_back(10)
size=1, capacity=1
layout=[10]
invariante: 0 <= n <= capacity y los elementos validos viven en [0, n)

Operacion 2: push_back(20)
size=2, capacity=2
layout=[10 | 20]
invariante: 0 <= n <= capacity y los elementos validos viven en [0, n)

Operacion 3: add(1, 15)
Se desplazan a la derecha los elementos desde i hasta n-1.
size=3, capacity=4
layout=[10 | 15 | 20 | _]
invariante: 0 <= n <= capacity y los elementos validos viven en [0, n)

Operacion 4: remove(0)
Se desplazan a la izquierda los elementos desde i+1 hasta n-1.
Valor removido = 10
size=2, capacity=4
layout=[15 | 20 | _ | _]
invariante: 0 <= n <= capacity y los elementos validos viven en [0, n)

Idea central: add(i,x) y remove(i) cuestan O(n-i) por los desplazamientos.
```

**Ejecución: demo_fastarraystack.cpp**
```text
$ ./sem2_demo_fastarraystack
size = 7
0 1 2 99 3 4 5
```

**Ejecución: demo_rootisharraystack_explicado.cpp**
```text
$ ./sem2_demo_rootisharraystack_explicado
RootishArrayStack explicado (Morin, capitulo 2)
size=6, blocks=3, capacidad total=6

 bloque 0 (tam=1):
 bloque 1 (tam=2): [1:20 | 2:30]
 bloque 2 (tam=3): [3:40 | 4:50 | 5:60]
invariante: el bloque b tiene capacidad b+1 y guarda una porcion contigua logica de la secuencia

Como se ubican algunos indices:
 indice logico 0 -> bloque 0, offset 0, valor=10
 indice logico 2 -> bloque 1, offset 1, valor=30
 indice logico 5 -> bloque 2, offset 2, valor=60

Operacion: add(2, 99)
size=7, blocks=4, capacidad total=10

 bloque 0 (tam=1):
 bloque 1 (tam=2): [1:20 | 2:99]
 bloque 2 (tam=3): [3:30 | 4:40 | 5:50]
 bloque 3 (tam=4): [6:60 | _ | _ | _]
invariante: el bloque b tiene capacidad b+1 y guarda una porcion contigua logica de la secuencia

Operacion: remove(4)
Valor removido = 40
size=6, blocks=4, capacidad total=10
...
```

**Ejecución: demo_stl_vector_contraste.cpp**
```text
$ ./sem2_demo_stl_vector_contraste 
push_back(0) -> size=1, capacity=1
push_back(10) -> size=2, capacity=2
push_back(20) -> size=3, capacity=4
push_back(30) -> size=4, capacity=4
push_back(40) -> size=5, capacity=8
push_back(50) -> size=6, capacity=8
push_back(60) -> size=7, capacity=8
```

### Respuestas de análisis

### 1. En demo_array_basico.cpp, ¿qué deja claro sobre arreglo, longitud y asignación?
Me deja claro que encapsula un arreglo primitivo con su longitud. Al correr `b = a`, comprobé visualmente la **transferencia de propiedad** (*ownership transfer*); se intercambian punteros en O(1) sin hacer una copia profunda pesada.

### 2. En demo_arraystack_explicado.cpp, ¿qué operación muestra mejor el costo por desplazamientos?
Al revisar mi terminal, vi que `add(1, 15)` y `remove(0)` son los mejores ejemplos. Ver el *layout* imprimiéndose y los guiones bajos moviéndose me ilustró perfectamente el movimiento físico en memoria y el costo O(n-i).

### 3. En demo_fastarraystack.cpp, ¿qué cambia en la implementación aunque no cambie la complejidad asintótica?
Bajo el capó, cambian los lentos ciclos iterativos `for` por instrucciones de movimiento de memoria nativas de C++ (como `std::copy`). El costo asintótico sigue siendo O(n-i), pero mi procesador lo ejecuta mucho más rápido en tiempo real.

### 4. En demo_rootisharraystack_explicado.cpp, ¿qué ejemplo explica mejor el mapeo de índice lógico a bloque y offset?
La línea de la consola `índice lógico 5 -> bloque 2, offset 2`. Me demostró cómo el código calcula la posición resolviendo una ecuación, dándome un acceso O(1) sin tener que recorrer los bloques anteriores.

### 5. En demo_deng_vector.cpp, ¿qué observable permite defender el crecimiento de capacity?
Los saltos impresos (`capacity=3` a `6` a `12`). Esta evidencia empírica que corrí en mi máquina confirma la política de **expansión geométrica**, necesaria para lograr inserciones en O(1) amortizado.

### 6. En demo_stl_vector_contraste.cpp, ¿qué similitud conceptual observan con DengVector?
Noté que `std::vector` hace exactamente lo mismo: separa estrictamente `size` de `capacity` y crece duplicándose (1, 2, 4, 8), lo que me valida que ambos se rigen por la misma teoría matemática.

### 7. ¿Qué demo sirve mejor para defender amortización y cuál sirve mejor para defender uso de espacio?
* **Para amortización:** Considero que `demo_stl_vector_contraste.cpp` es ideal, porque me muestra de forma clara cómo se reserva memoria sobrante para "pagar" la velocidad de inserciones futuras.
* **Para uso de espacio:** `demo_rootisharraystack_explicado.cpp`, ya que ver en la consola los bloques fragmentados confirma que el desperdicio espacial se queda arrinconado en el último bloque asignado (O(√n)).

## Bloque 3 - Pruebas públicas, stress y correctitud

### Material Revisado:
- `Semana2/pruebas_publicas/README.md`
- `Semana2/pruebas_publicas/test_public_week2.cpp`
- `Semana2/pruebas_internas/test_internal_week2.cpp`
- `Semana2/pruebas_internas/resize_stress_week2.cpp`

### 1. ¿Qué operaciones mínimas valida la prueba pública para ArrayStack?
Al revisar el código del test, noté que valida:
- **Inserción:** `add(x)` y `add(i, x)`.
- **Consulta:** `size()` y `get(i)`.
- **Eliminación:** `remove(i)`.

### 2. ¿Qué operaciones mínimas valida la prueba pública para FastArrayStack?
Valida el mismo conjunto (`add`, `size`, `get`, `remove`), pero vi que hace énfasis en `remove(0)` para estresar el desplazamiento masivo hacia la izquierda usando `std::copy`.

### 3. ¿Qué operaciones mínimas valida la prueba pública para RootishArrayStack?
Además de las operaciones base, esta prueba me valida explícitamente `set(i, x)` (sobreescribir un valor), para comprobar que la ubicación en los distintos bloques funciona para escritura.

### 4. ¿Qué sí demuestra una prueba pública sobre una estructura?
Para mí, demuestra la **correctitud funcional empírica**. Me asegura que, bajo casos de uso específicos de clase, la estructura devuelve los valores correctos y no hace crashear mi computadora.

### 5. ¿Qué no demuestra una prueba pública?
No me demuestra la eficiencia asintótica (O(1) vs O(n)). El test puede pasar en verde, pero mi algoritmo podría estar consumiendo memoria excesiva, tener *memory leaks* graves o ser sumamente ineficiente si le paso un millón de datos.

### 6. En `resize_stress_week2.cpp`, ¿qué comportamiento intenta estresar sobre crecimiento, reducción o estabilidad?
Al ejecutar este archivo, vi que inyecta cientos de elementos de golpe y luego los borra. Intenta estresar los métodos `grow` y `shrink` para verificar que mi código gestione la RAM sin corromper datos al expandirse y sin quedarse con gigas de memoria inútil al contraerse.

### 7. ¿Por qué pasar pruebas no reemplaza una explicación de invariantes y complejidad?
Porque que mi terminal diga "100% tests passed" solo aplica para los 50 o 100 datos que usé en el test. Solo si entiendo y explico las **invariantes** puedo asegurar que mi lógica nunca fallará, y solo con el **análisis de complejidad** sé si mi programa sobrevivirá en un entorno real con Big Data.

## Bloque 4 - Vector como puente entre teoría y código

### Material Revisado:
- `Semana2/include/DengVector.h`
- `Semana2/demos/demo_deng_vector.cpp`
- `Lectura4-Deng`

### 1. ¿Qué papel cumplen `_size`, `_capacity` y `_elem`?
Son las variables que definen mi estado lógico y físico:
- `_elem` : puntero a mi arreglo en memoria.
- `_size` : cantidad de datos válidos que el usuario ve.
- `_capacity` : tamaño máximo del arreglo actual antes de que yo necesite hacer un `resize`.

### 2. ¿Cuándo debe ejecutarse `expand()`?
Debo ejecutarlo justo antes de una inserción, pero solo cuando detecto que `_size == _capacity`. Expandirlo duplicando el tamaño es lo que me asegura el costo amortizado O(1).

### 3. ¿Por qué `insert(r, e)` necesita desplazar elementos?
Por culpa de la memoria contigua. Si quiero meter un dato en medio (posición `r`), no tengo otra opción más que empujar manualmente a todos los vecinos de la derecha para hacerle hueco, costándome O(n-r) tiempo de ejecución.

### 4. ¿Qué diferencia conceptual hay entre `remove(r)` y `remove(lo, hi)`?
Descubrí que `remove(lo, hi)` es la operación real que hace el trabajo pesado de mover un bloque de memoria completo. `remove(r)` es solo un caso especial o "atajo" (un intervalo de 1) que internamente llama a la primera para no duplicar código en la librería.

### 5. ¿Qué evidencia de copia profunda aparece en la demo?
Cuando en mi terminal se imprimen los resultados de `increaseByOne` y `MultiplyByTwo`. Las salidas son diferentes, demostrándome que el constructor de copia generó un bloque de memoria 100% nuevo y no solo copió la dirección del puntero.

### 6. ¿Por qué `traverse()` es una buena interfaz didáctica?
Porque me separa la molestia de armar un bucle `for` de la lógica de negocio. Es un buen acercamiento a la programación funcional en C++, ya que puedo pasarle funciones o functores como argumentos.

### 7. ¿Qué ventaja tiene implementar un vector propio antes de depender de `std::vector`?
Implementarlo a mano me obliga a pelear con la memoria (punteros, destructores, *memory leaks*), y me permite entender por qué `std::vector` es tan rápido, al comprender matemáticamente la magia del costo amortizado.

## Bloque 5 - RootishArrayStack: espacio y mapeo

### Material Revisado: 
- `Semana2/include/RootishArrayStack.h`
- `Semana2/include/RootishArrayStackExplicado.h`
- `Semana2/demos/demo_rootisharraystack.cpp`
- `Semana2/demos/demo_rootisharraystack_explicado.cpp`
- `Lectura5-Morin`

### 1. ¿Cómo se distribuyen los elementos entre bloques?
Se ubican en arreglos separados: el bloque 0 recibe 1 elemento, el bloque 1 recibe 2, el bloque 2 recibe 3, formando una progresión aritmética. Lógicamente yo lo veo contiguo, pero físicamente están dispersos.

### 2. ¿Por qué con $r$ bloques la capacidad total es $r(r+1)/2$?
Porque es simplemente la suma de una serie aritmética (la suma de Gauss). Sumar los tamaños de los bloques 1 + 2 + 3 + ... + r da exactamente la fórmula r(r+1)/2.

### 3. ¿Qué problema resuelve `i2b(i)`?
Me evita tener que usar un bucle `while` lento para encontrar en qué bloque está mi índice. Mediante la resolvente de una ecuación cuadrática, me da el bloque correcto en O(1).

### 4. ¿Qué información produce `locate(i)` en la versión explicada?
En la consola de mi terminal me arroja un par `[b, j]`. `b` es el índice del bloque en memoria, y `j` me dice el offset o cuántos "pasos" adentro de ese bloque debo dar para leer el dato.

### 5. ¿Qué se gana en espacio frente a `ArrayStack`?
Dejo de desperdiciar la mitad de mi RAM cada vez que expando. Mientras `ArrayStack` desperdicia espacio O(n), el `RootishArrayStack` arrincona los vacíos en el último bloquecito asignado, haciendo que el desperdicio se desplome a O(√n).

### 6. ¿Qué se conserva igual respecto a la interfaz?
Para mí, como usuario consumiendo la clase, no noto la diferencia. Los métodos `get`, `set`, `add` y `remove` funcionan igualito a como si fuera un arreglo lineal normal (ADT List).

### 7. ¿Qué parte les parece más difícil de defender oralmente: el mapeo, el análisis espacial o el costo amortizado de grow/shrink?
Personalmente, la parte más densa para defender en una sustentación oral es el **costo amortizado de `grow`/`shrink`**. El mapeo espacial es solo álgebra (ecuaciones) que puedo dibujar en una pizarra. Pero justificar cómo los elementos "saltan" las fronteras físicas de los bloques durante un `add` en cascada, y que eso siga cumpliendo matemáticamente con O(n-i) usando expansiones amortizadas, es muy abstracto de explicar con palabras.

## Bloque 6 - Refuerzo de lectura

### Material Revisado: 
- `Lectura4-Deng`

### 1. ¿Qué aporta `operator[]` a la idea de vector?
Me aporta naturalidad sintáctica al codificar. Permite que mi clase Vector, a pesar de tener punteros, expansiones y copias profundas por dentro, se lea y se sienta tan simple como usar `A[i]` en un arreglo de C clásico.

### 2. ¿Qué supone `find(e)` sobre igualdad entre elementos?
Me exige que el tipo de dato que estoy guardando sepa compararse a sí mismo. Supone que tengo sobrecargado el operador lógico `==`, sin el cual la iteración de búsqueda no podría evaluar coincidencias.

### 3. ¿Qué muestra `traverse()` sobre procesamiento uniforme de toda la estructura?
Muestra que puedo procesar datos masivamente inyectando comportamientos externos. Me enseñó a usar plantillas (templates) para aplicar operaciones arbitrarias a la colección sin alterar el código fuente del propio vector.

### 4. ¿Por qué esta lectura sirve como refuerzo natural de `DengVector` aunque no sea el centro exclusivo de la semana?
Porque me dio la base teórica que sustenta el código fuente. Mientras el archivo `.h` me enseñaba la sintaxis de C++, la lectura me justificaba por qué decidimos usar una progresión geométrica para el `capacity` basándose en el análisis amortizado.

## Bloque 7 - Cierre comparativo

### De Arreglo Primitivo a Estructura Dinámica (ADT)

Al finalizar esta actividad, entiendo que pasar de un arreglo primitivo a un **Tipo de Dato Abstracto (ADT)** dinámico requiere asimilar estos cinco pilares:

1.  **Representación:** Aprendí a independizar mi gestión de memoria separando lo que el usuario cree tener (`size`) del bloque de RAM que yo realmente he pedido al sistema operativo (`capacity`).
2.  **Correctitud:** Ya no dependo del usuario; la estructura encapsulada asume el dolor de cabeza de copiar y mover bytes (invariantes internas), protegiéndome de desbordamientos y *segmentation faults*.
3.  **Costo amortizado:** Comprendí que multiplicar por dos la memoria duele mucho temporalmente, pero si lo diluyo a largo plazo mediante crecimiento geométrico, matemáticamente pago solo **O(1)** por inserción.
4.  **Uso de espacio:** Acepto que para ganar velocidad y evitar cuellos de botella por continuas reasignaciones de RAM, estoy obligado a desperdiciar espacio de manera intencional (sobreaprovisionamiento temporal).
5.  **Comparación de variantes revisadas:**
    * **ArrayStack:** El clásico. Muy rápido para leer contiguo, pero desperdicia mucha RAM (O(n)) y reubica lento usando bucles clásicos.
    * **FastArrayStack:** Idéntico en consumo de RAM a ArrayStack, pero en mi terminal se ejecutó más rápido porque explota operaciones de bajo nivel nativas del hardware para copiar los bytes en bloque.
    * **RootishArrayStack:** El más creativo espacialmente. Rompe la memoria continua en bloquecitos, conservando el acceso en tiempo O(1) a punta de ecuaciones matemáticas, pero logrando reducir asombrosamente mi pérdida de memoria a solo **O(√n)**.