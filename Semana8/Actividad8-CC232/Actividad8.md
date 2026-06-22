# Actividad 8 - CC232

### Estudiante
- **Nombre:** Axel Alberto Reyes Baldeón
- **Código:** 20200485B

## Bloque 1 - Diagnóstico inicial de la Semana 8

### Archivos revisados :

* `Semana8/README.md`
* `Semana8/CMakeLists.txt`
* `Semana8/include/Capitulo9.h`
* `Semana8/include/HashCode.h`
* `Semana8/include/ChainedHashTable.h`

### Tabla de comandos ejecutados

| Comando | Resultado | Error | Interpretación |
| :--- | :--- | :--- | :--- |
| `cmake -S . -B build-debug -DCMAKE_BUILD_TYPE=Debug` | Configuración exitosa | Ninguno | Se generó el build tree para Semana 8. |
| `cmake --build build-debug` | Compilación exitosa | Ninguno | Los ejecutables de demos y pruebas se construyeron correctamente. |
| `ctest --test-dir build-debug -R semana8 --output-on-failure` | 6/6 pasados | Ninguno | Toda la suite de tests de Semana 8 pasó. |

### Cuestionario Analítico

**1. ¿Qué targets de demostración aparecen para Semana 8?**

Los targets son:

* `sem8_demo_chained`
* `sem8_demo_linear`
* `sem8_demo_hashtable_oa`
* `sem8_demo_aplicaciones`
* `sem8_demo_collision_strategies`
* `sem8_demo_hash_functions`
* `sem8_demo_tombstones`
* `sem8_demo_benchmark_load_factor`

**2. ¿Qué pruebas públicas e internas aparecen?**

* **Pruebas públicas**:
  * `sem8_test_public` (archivo `pruebas_publicas/test_public_week8.cpp`)
* **Pruebas internas**:
  * `sem8_test_internal` (`pruebas_internas/test_internal_week8.cpp`)
  * `sem8_test_tombstones` (`pruebas_internas/test_tombstones.cpp`)
  * `sem8_test_collision_patterns` (`pruebas_internas/test_collision_patterns.cpp`)
  * `sem8_test_rehashing` (`pruebas_internas/test_rehashing.cpp`)
  * `sem8_test_randomized_against_stl` (`pruebas_internas/test_randomized_against_stl.cpp`)

**3. ¿Qué archivos incluye Capitulo9.h?**

`Capitulo9.h` incluye:
* `Applications.h`
* `ArrayStack.h`
* `Bitmap.h`
* `ChainedHashTable.h`
* `Dictionary.h`
* `DoubleHashTable.h`
* `Entry.h`
* `HashCode.h`
* `HashStats.h`
* `HashtableOA.h`
* `LinearHashTable.h`
* `PrimeUtils.h`
* `QuadraticHashTable.h`
* `RehashPolicy.h`
* `RobinHoodHashTable.h`
* `UniversalHash.h`
* `array.h`

**4. ¿Qué relación conceptual hay entre Semana 5, Semana 6, Semana 7 y Semana 8?**

* **Semana 5**: árboles binarios y BST. Se introduce el concepto de diccionario y búsqueda ordenada.
* **Semana 6**: priorización y heaps, representación de datos en arreglos y comparación experimental.
* **Semana 7**: árboles balanceados (AVL y Red-Black Tree) con garantías de altura `O(log n)`.
* **Semana 8**: hashing y diccionarios no ordenados, donde la eficiencia es esperada con buenas funciones hash y políticas de carga.

**5. ¿Por qué no es correcto decir que una tabla hash siempre tiene costo O(1) garantizado?**

Porque el costo depende de:
* la calidad de la función hash;
* la presencia de colisiones;
* la política de resolución de colisiones;
* el factor de carga;
* el rehashing y los tombstones.

Una tabla hash ofrece `O(1)` esperado bajo distribuciones razonables, pero en el peor caso, con colisiones adversariales o carga alta, puede degradar a `O(n)`.

**6. ¿Qué evidencia inicial obtuviste al ejecutar las pruebas sin modificar nada?**

Ejecución de `ctest --test-dir build-debug -R semana8 --output-on-failure`:
* 6 tests ejecutados
* 6 tests aprobados
* Duración total 0.80 s

Esto demuestra que la implementación de la semana compila y pasa las pruebas básicas y de edge incluidas.

**7. ¿Qué diferencia práctica hay entre compilar todo el proyecto y compilar solo los targets de Semana 8?**

* **Compilar todo el proyecto**: construye todos los módulos y recursos de la librería, lo cual toma más tiempo.
* **Compilar solo Semana 8**: genera únicamente los demos y pruebas específicos de esta semana, reduciendo tiempo y concentrando el análisis en hashing.

### Estado de la semana

Semana 8 está bien organizada y funcional. El código incluye implementaciones diversas de tablas hash, demos para comparación experimental y pruebas automáticas. El principal hallazgo es que el paquete ya reúne evidencia de que las tablas hash funcionan y rehashan correctamente, pero requiere una lectura cuidadosa para diferenciar `loadFactor`, `occupiedFactor`, tombstones y estrategias de colisión.

## Bloque 2 - Núcleo conceptual de hashing y diccionarios

### Archivos revisados :

* `Semana8/lecturas/Notas.md`
* `Semana8/lecturas/GuiaHashing.md`
* `Semana8/include/Dictionary.h`
* `Semana8/include/Entry.h`
* `Semana8/include/HashCode.h`
* `Semana8/include/HashStats.h`
* `Semana8/include/RehashPolicy.h`

### Preguntas

**1. Define con precisión qué es un diccionario abstracto.**

Un diccionario abstracto es un ADT que asocia claves `K` con valores `V` y soporta al menos las operaciones: insertar o actualizar (`put`), buscar (`get`) y eliminar (`remove`). En `Dictionary.h`, la interfaz define `size()`, `put`, `get` y `remove`.

**2. Explica la diferencia entre diccionario, mapa, conjunto y tabla hash.**

* **Diccionario**: abstracción de pares `(clave, valor)` con las operaciones básicas mencionadas.
* **Mapa**: sinónimo práctico de diccionario en C++ y otros lenguajes.
* **Conjunto**: almacena solo claves sin valores asociados; la operación principal es `contains`.
* **Tabla hash**: representación concreta del diccionario/conjunto basada en hashing.

**3. Explica qué representa un `Entry<K,V>`.**

`Entry<K,V>` es una estructura que guarda una clave y su valor asociado. En `HashtableOA`, representa la celda almacenada cuando hay un par clave-valor activo.

**4. Explica qué hace una función hash.**

Convierte una clave arbitraria en un entero de dispersión. El resultado sirve de entrada para calcular el índice de tabla: `index = hashCode(key) % capacity`.

**5. Explica por qué pueden existir colisiones aunque la función hash sea razonable.**

Porque el dominio de claves es generalmente más grande que el número de posiciones de tabla. Dos claves distintas pueden producir el mismo índice después de modularizar.

**6. Explica qué significa factor de carga.**

`loadFactor = elementosActivos / capacidad`. Mide qué tan llena está la tabla con elementos activos.

**7. Explica qué significa rehashing.**

Reconstruir la tabla con una nueva capacidad, reinsertando todos los elementos activos. Se usa para crecer, encoger o limpiar tombstones.

**8. Explica qué mide `HashStats`.**

Registra métricas de rendimiento y uso de la tabla: inserciones, búsquedas exitosas/erróneas, colisiones, sondeos, longitud máxima de sondeo, rehashes y tombstones.

**9. Explica qué decide `RehashPolicy`.**

Cuándo crecer (`shouldGrow`), cuándo limpiar por tombstones (`shouldCleanOrGrow`) y cuándo contraer (`shouldShrink`). Define umbrales de carga y factores de crecimiento/contracción.

**10. Compara el costo esperado de una tabla hash con el costo garantizado de AVL y Red-Black Tree.**

* **Tabla hash**: operaciones esperadas `O(1)` si la función hash distribuye bien y la política de carga se cumple.
* **AVL / Red-Black Tree**: operaciones garantizadas `O(log n)` en peor caso, porque mantienen invariantes de balanceo.

### Tabla Conceptual

| Concepto | Definición | Archivo relacionado | Ejemplo |
| :--- | :--- | :--- | :--- |
| **Diccionario abstracto** | ADT de claves y valores con put/get/remove | `Dictionary.h` | `HashtableOA<string,int>` |
| **Entrada** | Par `clave-valor` | `Entry.h` | `Entry<string,int>{"hola", 1}` |
| **Función hash** | Transformación de clave a entero | `HashCode.h` | `hashCode("abc")` |
| **Factor de carga** | `n/capacity` | `ChainedHashTable.h`, `HashtableOA.h` | `6/17 = 0.35` |
| **Rehashing** | Reconstrucción de la tabla para cambiar capacidad | `HashtableOA.h`, `LinearHashTable.h` | `rehash(17)` |
| **Estadísticas de hash** | Métricas de sondeos y colisiones | `HashStats.h` | `maxProbeLength = 4` |
| **Política de rehash** | Condiciones de crecimiento y limpieza | `RehashPolicy.h` | `maxLoad=0.70` |

### Por qué hashing no reemplaza completamente a los árboles balanceados.

Hashing es excelente para búsquedas exactas y diccionarios no ordenados, pero no ofrece orden ni `lowerBound`/`upperBound`. Los árboles balanceados mantienen claves ordenadas y garantizan complejidad en el peor caso, por lo tanto siguen siendo necesarios para consultas de rango y datos adversariales.

## Bloque 3 - Chaining: buckets, colisiones y longitud máxima

### Archivos revisados :

* `Semana8/include/ChainedHashTable.h`
* `Semana8/include/ArrayStack.h`
* `Semana8/include/HashCode.h`
* `Semana8/demos/demo_chained.cpp`

### Salida de `demo_chained.cpp`

```bash
AXEL@DESKTOP-70IITE7 UCRT64 /c/Users/AXEL/OneDrive/Escritorio/uni/2026-1/AED/Repositorio/Personal/CC232-sfinales/CC-232/Libreria_cc232/Semana8/build-debug
$ ./sem8_demo_chained.exe
ChainedHashTable
size=6 capacity=17 load=0.352941 longestBucket=2
contains(26)=1 contains(99)=0
insertions=6, successfulSearches=1, failedSearches=1, removals=0, collisions=4, totalProbes=14, maxProbeLength=3, averageProbeLength=1.75, rehashes=1, tombstones=0
```

### Tabla de operaciones de `ChainedHashTable`

| Operación | Clave | Bucket calculado | Tamaño del bucket antes | Tamaño del bucket después | Colisión observada | loadFactor() | longestBucket() |
| :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| **add** | 10 | 2 | 0 | 1 | no | 0.12500 | 1 |
| **add** | 18 | 2 | 1 | 2 | sí | 0.25000 | 2 |
| **add** | 26 | 2 | 2 | 3 | sí | 0.37500 | 3 |
| **add** | 34 | 5 | 0 | 1 | no | 0.50000 | 3 |
| **add** | 42 | 5 | 1 | 2 | sí | 0.62500 | 3 |
| **add** | 50 | 8 *(rehash a N=17)* | 0 | 1 | no | 0.35294 | 2 |

### Dibujo conceptual de la tabla hash (N = 17)

```text
Bucket index:  0    1       2        3    4       5        6    7    8    9   10   11   12   13   14   15   16
Bucket list:  [ ]  [ ]  [10,18,26]  [ ]  [ ]  [34,42]  [ ]  [ ]  [50] [ ]  [ ]  [ ]  [ ]  [ ]  [ ]  [ ]  [ ]
```

### Preguntas

**1. ¿Qué diferencia hay entre el arreglo principal y los buckets?**

El arreglo principal es una estructura estática y contigua en memoria de tamaño fijo $N$ que almacena las cabeceras o punteros. Los buckets son las estructuras dinámicas independientes (como listas enlazadas) que cuelgan de cada posición del arreglo para almacenar las entradas reales.

**2. ¿Por qué chaining puede almacenar más elementos que la cantidad de posiciones del arreglo principal?**

Porque no guarda los elementos directamente en las celdas del arreglo. Al utilizar memoria dinámica externa para expandir cada bucket de forma vertical, la capacidad total de almacenamiento es teóricamente ilimitada y permite factores de carga $\lambda > 1$.

**3. ¿Qué significa que un bucket crezca demasiado?**

Significa que múltiples claves distintas han generado el mismo índice hash (alta tasa de colisiones concentrada). Esto rompe la distribución uniforme esperada y degrada el rendimiento de la búsqueda local, convirtiéndola en un recorrido secuencial.

**4. ¿Por qué `longestBucket()` es una métrica importante?**

Es el indicador del peor caso temporal en tiempo de ejecución. Al medir la longitud del bucket más congestionado, define directamente el número máximo de comparaciones requeridas para resolver una búsqueda exitosa o fallida en esa tabla.

**5. ¿En qué caso la búsqueda en chaining deja de parecerse a $O(1)$ esperado?**

Cuando la función hash distribuye las claves de forma no uniforme o cuando ocurre un ataque por colisión que agrupa todos los elementos en un único bucket. En ese escenario patológico, la tabla se degrada y se comporta como una lista enlazada simple.

**6. ¿Qué costo tiene recorrer un bucket de longitud $k$?**

Tiene un costo temporal lineal estricto de **$O(k)$**. Se deben inspeccionar uno a uno los elementos encadenados hasta encontrar la clave buscada o alcanzar el final de la lista en una búsqueda fallida.

**7. ¿Qué parte del costo depende de la función hash y qué parte depende de la distribución de claves?**

* **Función Hash**: Determina el costo constante $O(1)$ del cálculo aritmético inicial para transformar la clave en un índice entero bruto.
* **Distribución de Claves**: Determina la longitud promedio y máxima de los buckets ($k$). Si las claves se distribuyen mal, el costo de resolver colisiones dentro del bucket crece.

### Explicación de costo esperado y peor caso

* **Costo Esperado $O(1)$**: Bajo la suposición de hashing uniforme simple, las claves se distribuyen equitativamente entre los buckets. Si el factor de carga $\lambda = n/N$ se mantiene pequeño mediante políticas de rehash, la longitud promedio de cada bucket es una constante muy pequeña, logrando un acceso directo inmediato.

* **Peor Caso $O(n)$**: Si todas las $n$ claves colisionan en la misma posición del arreglo debido a una pésima función hash o datos patológicos, el bucket se convierte en una lista lineal de tamaño $n$. Buscar un elemento requerirá recorrer la lista entera, anulando las ventajas de la tabla hash.

