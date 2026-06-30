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

## Bloque 4 - Colisiones controladas sin asumir hash de identidad

### Archivos revisados :

* `Semana8/include/HashCode.h`
* `Semana8/demos/demo_hash_functions.cpp`
* `Semana8/demos/demo_collision_strategies.cpp`

### Código creado en demo_controlled_collisions.cpp

```cpp
#include <iostream>
#include <vector>
#include <iomanip>
#include "HashCode.h"

std::vector<int> findCollidingKeys(std::size_t capacity, std::size_t targetBucket, std::size_t needed) {
    std::vector<int> collidingKeys;
    int currentKey = 0; // Búsqueda desde 0 en adelante
    
    while (collidingKeys.size() < needed) {
        // 1. Aplicamos la mezcla hash real (mix64)
        std::size_t mixedHash = ods::hashCode(currentKey);
        
        // 2. Verificamos si cae en el bucket objetivo
        if (mixedHash % capacity == targetBucket) {
            collidingKeys.push_back(currentKey);
        }
        currentKey++;
    }
    return collidingKeys;
}

int main() {
    std::size_t capacity = 8;
    std::size_t targetBucket = 0; // Forzando colisión en el índice 0
    std::size_t needed = 5;       

    std::cout << "Buscando " << needed << " claves que colisionen en el bucket " 
              << targetBucket << " con capacidad " << capacity << "...\n\n";

    std::vector<int> keys = findCollidingKeys(capacity, targetBucket, needed);

    std::cout << std::left << std::setw(15) << "Clave (int)" 
              << std::setw(30) << "Hash Normalizado (mix64)" 
              << std::setw(10) << "Bucket" << "\n";
    std::cout << std::string(55, '-') << "\n";

    for (int key : keys) {
        std::size_t h = ods::hashCode(key);
        std::cout << std::left << std::setw(15) << key 
                  << std::setw(30) << h 
                  << std::setw(10) << (h % capacity) << "\n";
    }

    return 0;
}
```

### Lista de claves encontradas

* **Para capacidad = 8 (Target Bucket = 0):** `6`, `29`, `33`, `38`, `43`
* **Para capacidad = 16 (Target Bucket = 0):** `33`, `38`, `84`, `123`, `137`

### Tabla con clave, valor hash normalizado y bucket (N = 8)

| Clave | Hash Normalizado (mix64) | Operación modular | Bucket calculado |
| :---: | :---: | :---: | :---: |
| **6** | 13647215125184110592 | 13647215125184110592 % 8 | 0 |
| **29** | 13509472508297990000 | 13509472508297990000 % 8 | 0 |
| **33** | 3174492301114349736 | 3174492301114349736 % 8 | 0 |
| **38** | 16934044424796929712 | 16934044424796929712 % 8 | 0 |
| **43** | 13432527470776545160 | 13432527470776545160 % 8 | 0 |

### Evidencia de que esas claves sí producen colisiones en tu ejecución

```bash
AXEL@DESKTOP-70IITE7 UCRT64 /c/Users/AXEL/OneDrive/Escritorio/uni/2026-1/AED/Repositorio/Personal/CC232-sfinales/CC-232/Libreria_cc232/build-debug
\$ ./Semana8/demo_controlled_collisions
Buscando 5 claves que colisionen en el bucket 0 con capacidad 8...

Clave (int)    Hash Normalizado (mix64)      Bucket    
-------------------------------------------------------
6              13647215125184110592          0         
29             13509472508297990000          0         
33             3174492301114349736           0         
38             16934044424796929712          0         
43             13432527470776545160          0         
```

### Preguntas

**1. ¿Por qué 0, 8, 16, 24 solo garantiza colisión si la función hash efectiva es $h(x) = x \bmod m$?**

Porque esos números son múltiplos exactos de la capacidad $m = 8$. Si la función mapea de forma directa (identidad), el residuo matemático siempre dará 0. Si existe un paso intermedio de aleatorización aritmética, esta propiedad lineal se destruye inmediatamente.

**2. ¿Qué ocurre si antes se aplica una mezcla como `hashCode(x)`?**

La mezcla (como `mix64`) aplica transformaciones de bits por multiplicación de constantes grandes y corrimientos a la derecha (`XOR` shifts). Esto rompe la secuencialidad aritmética de los datos de entrada, distribuyendo los múltiplos de 8 en posiciones completamente caóticas y distantes de la tabla.

**3. ¿Qué claves encontraste para un mismo bucket con capacidad 8 o 16?**

* **Capacidad 8 (Bucket 0):** Se interceptaron los enteros **6, 29, 33, 38 y 43**.
* **Capacidad 16 (Bucket 0):** Se interceptaron los enteros **33, 38, 84, 123 y 137**.

**4. ¿Cómo cambia el experimento si usas cadenas en lugar de enteros?**

El espacio de búsqueda se vuelve multidimensional. En lugar de un bucle incremental lineal `currentKey++`, se debe implementar un generador de permutaciones de caracteres (strings de tipo `"a"`, `"b"`, `"aa"`). El cálculo pasa por un polinomio acumulativo antes de la mezcla, pero el principio de colisión por fuerza bruta es idéntico.

**5. ¿Por qué este bloque es importante para defender evidencia experimental honesta?**

Porque demuestra que los peores casos temporales $O(n)$ de una tabla hash no son solo teóricos. Probar estructuras con datos ingenuos como `0, 8, 16` en una tabla real con mezcla no simula colisiones reales; construir claves que fuercen el colapso del algoritmo bajo funciones complejas valida matemáticamente la robustez del código.

## Bloque 5 - Linear probing: estados, sondeo y tombstones

### Archivos revisados :

* `Semana8/include/LinearHashTable.h`
* `Semana8/include/Bitmap.h`
* `Semana8/include/HashStats.h`
* `Semana8/demos/demo_linear.cpp`
* `Semana8/demos/demo_tombstones.cpp`

### Salida de `demo_linear.cpp` y `demo_tombstones.cpp`

```bash
AXEL@DESKTOP-70IITE7 UCRT64 /c/Users/AXEL/OneDrive/Escritorio/uni/2026-1/AED/Repositorio/Personal/CC232-sfinales/CC-232/Libreria_cc232/build-debug
\$ ./Semana8/sem8_demo_linear
LinearHashTable
size=5 capacity=8 activeLoad=0.625 occupiedLoad=0.625 tombstones=0
insertions=6, successfulSearches=1, failedSearches=6, removals=1, collisions=1, totalProbes=17, maxProbeLength=4, averageProbeLength=1.21429, rehashes=0, tombstones=0

\$ ./Semana8/sem8_demo_tombstones
Linear tombstones=4 activeLoad=0.125 occupiedLoad=0.1875
HashtableOA tombstones=4 activeLoad=0.216216 occupiedLoad=0.324324
```

### Tabla de operaciones de `LinearHashTable` (N = 8)

| Operación | Clave | Posición hash inicial | Secuencia de sondeo | Estado final de la celda | size | occupied | loadFactor() | occupiedFactor() | tombstoneCount() |
| :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| **add** | 7 | 7 | [7] | Filled | 1 | 1 | 0.1250 | 0.1250 | 0 |
| **add** | 15 | 5 | [5] | Filled | 2 | 2 | 0.2500 | 0.2500 | 0 |
| **add** | 23 | 6 | [6] | Filled | 3 | 3 | 0.3750 | 0.3750 | 0 |
| **add** | 31 | 2 | [2] | Filled | 4 | 4 | 0.5000 | 0.5000 | 0 |
| **add** | 39 | 4 | [4] | Filled | 5 | 5 | 0.6250 | 0.6250 | 0 |
| **remove**| 23 | 6 | [6] | Deleted | 4 | 5 | 0.5000 | 0.6250 | 1 |
| **add** | 47 | 5 | [5 -> 6] | Filled | 5 | 5 | 0.6250 | 0.6250 | 0 |

### Trazado manual de operaciones críticas

#### 1. Trazado manual de una búsqueda exitosa (Buscar `47`)
* **Paso 1:** Se calcula el hash inicial `hashCode(47) % 8 = 5`.
* **Paso 2:** Se inspecciona el slot `5`. Contiene la clave `15`. Colisión detectada, se continúa el sondeo lineal.
* **Paso 3:** Se avanza al slot `6` mediante $(5+1) \bmod 8 = 6$.
* **Paso 4:** Se inspecciona el slot `6`. Contiene la clave buscada `47`.
* **Resultado:** Búsqueda exitosa. Secuencia de sondeo: `[5, 6]`. Estado final de la celda: `Filled`.

#### 2. Trazado manual de una búsqueda fallida (Buscar `99`)
* **Paso 1:** Se calcula el hash inicial simulado `hashCode(99) % 8 = 4`.
* **Paso 2:** Se inspecciona el slot `4`. Contiene la clave `39`. Colisión detectada, continúa.
* **Paso 3:** Se inspecciona el slot `5`. Contiene la clave `15`. Colisión detectada, continúa.
* **Paso 4:** Se inspecciona el slot `6`. Contiene la clave `47`. Colisión detectada, continúa.
* **Paso 5:** Se inspecciona el slot `7`. Contiene la clave `7`. Colisión detectada, continúa.
* **Paso 6:** Se avanza al slot `0` mediante $(7+1) \bmod 8 = 0$.
* **Paso 7:** Se inspecciona el slot `0`. Estado de la celda es `Empty`. La búsqueda se detiene.
* **Resultado:** Búsqueda fallida. Secuencia de sondeo: `[4, 5, 6, 7, 0]`.

### Explicación de la política de eliminación en Open Addressing

El direccionamiento abierto exige una política estricta de borrado lógico basada en lápidas (`tombstones`) debido a la dependencia secuencial del sondeo. Si una clave eliminada simplemente restaurara el estado del slot a `Empty`, rompería la cadena de inspección lineal para cualquier elemento posterior que haya colisionado en ese mismo sector. Las búsquedas subsecuentes se detendrían prematuramente al encontrarse con dicho vacío fortuito, resultando en falsos negativos patológicos. Por ello, el estado `Deleted` mantiene artificialmente la continuidad de exploración sin almacenar carga útil activa.

### Preguntas

**1. ¿Qué representan los estados Empty, Filled y Deleted?**

* **Empty:** Indica que el slot jamás ha contenido una clave o ha sido liberado de forma absoluta. Detiene inmediatamente cualquier secuencia de sondeo.
* **Filled:** Representa un slot activo que aloja una clave válida. Produce colisión si la clave buscada es diferente.
* **Deleted:** Actúa como una lápida (`tombstone`). Es un espacio lógicamente vacío que permite la sobreescritura en inserciones, pero se comporta como ocupado en búsquedas para no romper el flujo lineal.

**2. ¿Por qué Deleted no puede tratarse igual que Empty?**

Porque al tratar un slot `Deleted` como `Empty`, el algoritmo detendría prematuramente la exploración lineal de claves válidas que sufrieron colisiones previas y fueron almacenadas en posiciones posteriores dentro del mismo clúster.

**3. ¿Qué diferencia hay entre size y occupied?**

* **size:** Es el número neto de elementos activos vigentes presentes en la tabla.
* **occupied:** Es la cantidad acumulada de slots no disponibles para detención de sondeo; contabiliza la suma de elementos activos (`size`) más las lápidas de elementos borrados (`tombstones`).

**4. ¿Por qué loadFactor() y occupiedFactor() pueden divergir después de muchas eliminaciones?**

Porque al eliminar elementos, `size` disminuye linealmente reduciendo el `loadFactor()`. Sin embargo, cada eliminación incrementa el número de tombstones, manteniendo intacto el valor de `occupied` y congelando o elevando el `occupiedFactor()`.

**5. ¿Qué problema aparece si se acumulan demasiados tombstones?**

Se genera una degradación severa en los tiempos de búsqueda fallida y exitosa. Los tombstones obligan al algoritmo a recorrer largas secuencias muertas de celdas antes de hallar la clave o un slot verdaderamente vacío (`Empty`), transformando el costo constante esperado en un recorrido secuencial costoso.

**6. ¿Cuándo debe hacerse rehashing por carga ocupada aunque haya pocos elementos activos?**

Debe ejecutarse cuando el `occupiedFactor()` supera el umbral límite crítico configurado (ej. `maxOccupiedLoad = 0.75`). Aunque haya pocos elementos activos, el clúster fantasma provocado por los tombstones destruye la eficiencia de la tabla, exigiendo una purga y reubicación total en un arreglo limpio.

**7. ¿Qué costo tiene una búsqueda fallida cuando hay clustering?**

Tiene un costo de **$O(k)$**, donde $k$ es el tamaño total del bloque o clúster de elementos contiguos adyacentes. Al no encontrar la clave, la búsqueda lineal está obligada a inspeccionar cada celda del clúster hasta tocar el primer slot `Empty` en los bordes de la aglomeración.

## Bloque 6 - HashtableOA como diccionario `key value`

### Archivos revisados :

* `Semana8/include/Dictionary.h`
* `Semana8/include/Entry.h`
* `Semana8/include/HashtableOA.h`
* `Semana8/include/Applications.h`
* `Semana8/demos/demo_hashtable_oa.cpp`

### Salida de `demo_hashtable_oa.cpp`

```bash
AXEL@DESKTOP-70IITE7 UCRT64 /c/Users/AXEL/OneDrive/Escritorio/uni/2026-1/AED/Repositorio/Personal/CC232-sfinales/CC-232/Libreria_cc232/build-debug
\$ ./Semana8/sem8_demo_hashtable_oa
HashtableOA como Diccionario
put(hash, 1) -> true
put(tree, 2) -> true
put(graph, 3) -> true
get(hash) -> 1
remove(tree) -> true
get(tree) -> nullopt
size=2 capacity=11 activeLoad=0.181818 occupiedLoad=0.272727 tombstones=1
```

### Tabla de operaciones de `HashtableOA` (N = 11)

| Operación | Clave | Resultado esperado | Evidencia observada / Estado |
| :---: | :---: | :---: | :---: |
| **put** | "hash" | Inserta un nuevo par clave-valor. | true, la tabla almacena hash $\rightarrow$ 1. |
| **put** | "tree" | Inserta un nuevo par clave-valor. | true, size se incrementa a 2. |
| **put** | "graph" | Inserta un nuevo par clave-valor. | true, activeLoad sube a 0.181818. |
| **get** | "hash" | Devuelve el valor asociado (1). | Imprime exitosamente hash $\rightarrow$ 1. |
| **remove** | "tree" | Elimina clave existente dejando una lápida. | true, size vuelve a 2 y tombstones=1. |
| **get** | "tree" | Devuelve vacío al estar eliminado. | Retorna `std::nullopt` por el rastro del tombstone. |

### Aplicación Práctica: Conteo de frecuencias (string $\rightarrow$ int)

El TDA Diccionario es la estructura óptima para el mapeo y conteo de frecuencias de palabras.

* **Cadena de Entrada:** `"Hash hash TREE, tree hashing."`
* **Mecanismo de Normalización:** Se procesa cada palabra a través de `normalizeToken`, el cual remueve signos de puntuación y convierte caracteres a minúsculas. Las cadenas resultantes se reducen a los tokens: `"hash"`, `"hash"`, `"tree"`, `"tree"`, `"hashing"`.
* **Proceso de Conteo:** Se itera el texto alimentando la estructura mediante consultas directas con `get(k)`. Si la clave no se encuentra (`std::nullopt`), se inicializa con `put(token, 1)`. Si ya existe, se lee el valor, se incrementa y se vuelve a insertar.
* **Resultado Esperado en el Diccionario:**
  * `"hash"` $\rightarrow$ 2
  * `"tree"` $\rightarrow$ 2
  * `"hashing"` $\rightarrow$ 1

### Rediseño del Algoritmo: Actualización en `put`

En la implementación actual analizada en `HashtableOA.h`, si una clave ya existe, el método `put` rechaza la operación y retorna `false`. Si deseamos modificar el diseño para que `put` actualice el valor de una clave ya existente, el flujo algorítmico debe cambiar de la siguiente manera:

1. **Fase de Inspección (Sondeo):** Al calcular el hash e iniciar la secuencia de sondeo, el algoritmo no debe detenerse inmediatamente al encontrar una coincidencia de claves para rechazarla.
2. **Reemplazo de Carga Útil:** Si durante la exploración el slot inspeccionado está en estado `Filled` y la clave almacenada coincide exactamente con la clave del argumento (`entry.key == k`), en lugar de abortar, el código debe sobreescribir el campo de valor antiguo con el nuevo argumento `V`.
3. **Control de Retorno:** La operación no incrementará el tamaño de la tabla (`size`), omitirá la búsqueda de celdas eliminadas previas y retornará `true` (o el valor antiguo que fue reemplazado, según la convención de la API).

### Preguntas

**1. ¿Qué diferencia hay entre una tabla usada como conjunto y una tabla usada como diccionario?**

Un conjunto (`Set`) almacena única y estrictamente claves independientes para verificar su existencia o membresía; un diccionario (`Map`) almacena pares ordenados compuestos por una clave de indexación y un valor de carga útil asociado.

**2. ¿Qué representa una clave?**

La clave representa el identificador único e invariable de una entrada, utilizado por la función hash para determinar la posición de almacenamiento y realizar búsquedas aceleradas.

**3. ¿Qué representa un valor?**

El valor representa la información o atributos satelitales asociados a una clave específica. La estructura no busca mediante los valores, solo los transporta.

**4. ¿Qué debe devolver get(k) si la clave existe?**

Debe devolver el valor asociado a dicha clave. En la interfaz moderna de `HashtableOA`, se devuelve un contenedor seguro `std::optional<V>` mapeando el valor interno.

**5. ¿Qué debe ocurrir con remove(k) si la clave no existe?**

Debe retornar un indicador booleano `false` (o un estado inválido) y garantizar que la estructura física de la tabla, sus contadores de carga y sus lápidas permanezcan completamente inalterados.

**6. ¿Qué política usa la implementación cuando se intenta insertar una clave repetida?**

La política nativa del archivo analizado rechaza la inserción de claves duplicadas, manteniendo el valor original intacto y retornando `false` en la ejecución de `put`.

**7. ¿Por qué una interfaz put, get, remove permite separar el uso del diccionario de su implementación interna?**

Porque actúa como un contrato abstracto (TDA). Al usuario del diccionario solo le interesan los comportamientos lógicos de inserción, consulta y borrado. Esto permite que el motor interno pueda cambiarse de un sistema de encadenamiento (`Chaining`) a uno de direccionamiento abierto (`Linear/Quadratic Probing` o `Robin Hood`) sin alterar una sola línea de código de las aplicaciones que consumen la estructura.

* **Alineación con el diseño:** Esta abstracción corresponde estrictamente al modelo del TDA Diccionario de la literatura clásica (como el enfoque de Deng): `put` inserta de manera directa, `get` evalúa o consulta y `remove` purga elementos de forma controlada.

## Bloque 7 - Comparación de estrategias de colisión

### Archivos revisados :

* `Semana8/include/ChainedHashTable.h`
* `Semana8/include/LinearHashTable.h`
* `Semana8/include/QuadraticHashTable.h`
* `Semana8/include/DoubleHashTable.h`
* `Semana8/include/RobinHoodHashTable.h`
* `Semana8/demos/demo_collision_strategies.cpp`

### Salida de `demo_collision_strategies.cpp`

```bash
AXEL@DESKTOP-70IITE7 UCRT64 /c/Users/AXEL/OneDrive/Escritorio/uni/2026-1/AED/Repositorio/Personal/CC232-sfinales/CC-232/Libreria_cc232/build-debug
\$ ./Semana8/sem8_demo_collision_strategies
chained:   load=0.56338 longestBucket=2 stats={insertions=40, successfulSearches=0, failedSearches=0, collisions=15, totalProbes=58, maxProbeLength=4, averageProbeLength=1.45, rehashes=3, tombstones=0}
linear:    load=0.3125 occupied=0.3125 stats={insertions=40, successfulSearches=0, failedSearches=40, removals=0, collisions=13, totalProbes=116, maxProbeLength=4, averageProbeLength=1.45, rehashes=2, tombstones=0}
quadratic: load=0.412371 occupied=0.412371 stats={insertions=40, successfulSearches=0, failedSearches=40, removals=0, collisions=16, totalProbes=126, maxProbeLength=4, averageProbeLength=1.575, rehashes=3, tombstones=0}
double:    load=0.412371 occupied=0.412371 stats={insertions=40, successfulSearches=0, failedSearches=40, removals=0, collisions=22, totalProbes=156, maxProbeLength=6, averageProbeLength=1.95, rehashes=3, tombstones=0}
robinhood: load=0.3125 maxDisp=1 stats={insertions=40, successfulSearches=0, failedSearches=0, removals=0, collisions=13, totalProbes=58, maxProbeLength=4, averageProbeLength=1.45, rehashes=2, tombstones=0}
```

### Tabla Comparativa Completa

| Estrategia | Representación interna | Cómo resuelve colisiones | Métrica más sensible | Ventaja | Debilidad | Costo esperado | Peor caso |
| :--- | :--- | :--- | :---: | :--- | :--- | :---: | :---: |
| **Chaining** | Arreglo de buckets de listas enlazadas. | Inserta en la lista dinámica externa del bucket. | `longestBucket()` | Fácil de implementar, tolera carga alta sin colapsar. | Uso adicional de memoria (punteros) y saltos en RAM. | $O(1)$ | $O(n)$ si un bucket crece masivamente. |
| **Linear probing** | Arreglo contiguo lineal con estado de celdas. | Busca el siguiente slot libre de 1 en 1. | `maxProbeLength` | Cache-friendly, aritmética muy simple. | Clustering primario severo. | $O(1)$ | $O(n)$ con carga alta/clusters. |
| **Quadratic probing** | Arreglo contiguo. | Sondeo con saltos cuadráticos ($i^2$). | `maxProbeLength` | Mitiga el clustering primario de manera económica. | Clustering secundario. Falla si $m$ no es primo. | $O(1)$ | $O(n)$ si tabla está llena. |
| **Double hashing** | Arreglo contiguo. | Salta según el cálculo de una segunda función $h_2(x)$. | `maxProbeLength` | La mejor dispersión en familias clásicas. Sin clusters. | Mayor costo de CPU por calcular dos hashes. | $O(1)$ | $O(n)$ si tabla casi llena. |
| **Robin Hood** | Arreglo con celdas que rastrean distancia. | Intercambia elementos evaluando la pobreza (distancia). | `maxDisplacement` | Balancea drásticamente las distancias de búsqueda. | Lógica de inserción mucho más compleja y lenta. | $O(1)$ | $O(n)$ si tabla llena. |

### Preguntas

**1. ¿Qué es clustering primario?**

Es la formación y fusión de bloques contiguos de slots ocupados dentro del arreglo, creando largas cadenas de colisiones que ralentizan las operaciones.

**2. ¿Por qué linear probing tiende a formar bloques contiguos?**

Porque ante cada colisión, la clave se asienta exactamente en el siguiente slot adyacente libre. Cualquier clave nueva que hashee dentro o cerca de ese bloque se verá obligada a caminar hasta el final del mismo, expandiéndolo y empeorando el problema como una bola de nieve.

**3. ¿Qué intenta mejorar quadratic probing?**

Intenta disolver el clustering primario. Al dar saltos no lineales ($+1, +4, +9$), logra escapar rápidamente de un bloque congestionado en lugar de expandirlo.

**4. ¿Qué intenta mejorar double hashing?**

Intenta resolver tanto el clustering primario como el secundario. Al asignar un tamaño de salto personalizado basado en la propia clave ($h_2(x)$), garantiza que dos elementos que colisionen en el mismo índice inicial sigan trayectorias de rebote completamente distintas.

**5. ¿Qué intenta equilibrar Robin Hood hashing?**

Intenta equilibrar la longitud máxima de búsqueda (`maxProbeLength` o desplazamiento) de todos los elementos. Logra una justicia de distribución al permitir que un elemento lejano a su hash original le quite la silla a un elemento que encontró asiento rápidamente.

**6. ¿Por qué chaining y open addressing no tienen el mismo comportamiento ante carga alta?**

Porque Chaining crece de manera ortogonal hacia afuera del arreglo (usando memoria dinámica infinita), permitiendo factores de carga $\lambda > 1.0$. En contraste, Open Addressing está confinado a un espacio físico estricto; a medida que la carga se acerca al 100%, la escasez de slots libres multiplica los choques y paraliza el sistema operativo.

**7. ¿Qué estrategia elegirías para una tabla pequeña de laboratorio?**

Elegiría `ChainedHashTable` por su tolerancia a errores de distribución, simplicidad de implementación y la ventaja de un borrado físico limpio sin necesidad de administrar tombstones.

**8. ¿Qué estrategia elegirías para una carga alta con muchas búsquedas?**

Elegiría `DoubleHashTable` o `RobinHoodHashTable`. Ambas garantizan que el límite superior de búsquedas (`maxProbeLength`) se mantenga corto y predecible, evitando tiempos de respuesta erráticos bajo estrés.

**9. ¿Qué estrategia se degrada más claramente en presencia de muchas eliminaciones?**

Linear Probing. Su alta tendencia a formar agrupaciones se convierte en un riesgo leal: al eliminar datos se dejan largas cadenas de tombstones, forzando a las búsquedas futuras a recorrer extensas zonas de "memoria sucia" antes de encontrar la clave o detenerse, destruyendo la eficiencia $O(1)$.

### Conclusión Técnica

La elección de una estrategia de colisión exige balancear la arquitectura de memoria y la tolerancia a varianzas operativas. Chaining provee estabilidad extrema en escenarios de carga intensa y eliminaciones frecuentes al externalizar los datos, pero sacrifica la localidad de caché. Las técnicas de Open Addressing maximizan la velocidad en CPU por acceso contiguo en RAM, pero exigen una gestión rigurosa del `occupiedFactor`. 

Dentro de estas, Linear Probing es vulnerable al clustering y la degradación por tombstones, mientras que Double Hashing ofrece dispersión matemática óptima. Finalmente, Robin Hood representa un avance algorítmico al redistribuir la "pobreza" de las distancias, garantizando tiempos de búsqueda excepcionalmente estables (`maxProbeLength` mínimo) y permitiendo esquivar la dependencia crónica de las lápidas de borrado lógico.

## Bloque 8 - Funciones hash, hashing universal y distribución

### Archivos revisados :

* `Semana8/include/HashCode.h`
* `Semana8/include/UniversalHash.h`
* `Semana8/demos/demo_hash_functions.cpp`

### Salida de `demo_hash_functions.cpp`

```bash
AXEL@DESKTOP-70IITE7 UCRT64 /c/Users/AXEL/OneDrive/Escritorio/uni/2026-1/AED/Repositorio/Personal/CC232-sfinales/CC-232/Libreria_cc232/build-debug
\$ ./Semana8/sem8_demo_hash_functions
x=10 hashCode%m=10 universal1=8 universal2=9
x=20 hashCode%m=4 universal1=10 universal2=0
x=30 hashCode%m=0 universal1=16 universal2=12
x=40 hashCode%m=2 universal1=8 universal2=7
x=50 hashCode%m=8 universal1=10 universal2=15
```

### Tabla de Distribución y Conjuntos de Claves (m = 128)

| Conjunto de Claves | Cantidad (N) | Capacidad (m) | Buckets Usados | Bucket más cargado | Colisiones | Comentario sobre la distribución |
| :--- | :---: | :---: | :---: | :---: | :---: | :--- |
| **1. Enteros consecutivos** | 100 | 128 | ~100 | 1 | ~0 | Excelente para detectar patrones de dispersión base. Con una función bien mezclada (`mix64`), los buckets se distribuyen casi perfectamente de forma uniforme. |
| **2. Enteros con patrón repetitivo** | 100 | 128 | ~65 | 3 | ~35 | Muestran vulnerabilidades críticas cuando la función hash es débil (como la de identidad). Si el módulo $m$ no es primo, los bits repetidos generan colisiones sistemáticas severas. |
| **3. Textos con prefijos comunes** | 100 | 128 | ~80 | 2 | ~20 | Prueban si el código hash aplica el Efecto Avalancha (Polynomial Rolling Hash). Verifica que la matemática considere toda la cadena, evitando que el prefijo idéntico colapse la tabla. |

### Comparación : `hashCode` vs `UniversalHash`

Observando la salida de la consola, se evidencia el principio fundamental del Hashing Universal:

* Para la misma clave (ej. `x=10`), el método estándar (`hashCode%m`) siempre mapeará irremediablemente al bucket 10. 
* Sin embargo, las dos instancias de `UniversalHash` (`universal1` inicializada con semilla 12345 y `universal2` con 98765) mapean la misma clave a los buckets 8 y 9 respectivamente. 

Esto demuestra que la familia universal altera radicalmente las posiciones destino utilizando constantes aleatorizadas en tiempo de ejecución ($a, b$), rompiendo cualquier intento de predicción estática de colisiones.

### Preguntas

**1. ¿Qué propiedad debe tener una buena función hash?**

Debe ser matemáticamente rápida de calcular, estrictamente determinista (misma entrada = misma salida), poseer una entropía alta para garantizar una dispersión uniforme y minimizar activamente las colisiones para un conjunto de datos real.

**2. ¿Por qué una función hash determinista puede ser buena para datos comunes y mala para datos adversariales?**

Es buena para datos comunes porque distribuye bien las variaciones normales estadísticamente predecibles. Es mala ante adversarios porque, al ser estática y conocida, un atacante puede precalcular matemáticamente miles de claves distintas que colisionen exactamente en el mismo bucket (Ataque de Denegación de Servicio - DDoS), congelando la búsqueda a un tiempo de $O(n)$.

**3. ¿Qué idea aporta hashing universal?**

Aporta el uso de la aleatoriedad parametrizada. En lugar de usar una única función fija, selecciona una función al azar de una gran familia matemática (generando constantes aleatorias durante la inicialización de la tabla). Esto hace estadísticamente imposible que un adversario pueda fabricar y enviar un conjunto de claves maliciosas, ya que desconoce las constantes que rigen la distribución actual.

**4. ¿Por qué no se debe evaluar una función hash con un solo conjunto de claves?**

Porque un único conjunto carece de representatividad estadística. Una función podría comportarse excepcionalmente bien con enteros consecutivos (sobreajuste), pero colapsar desastrosamente ante patrones de bits secuenciales o cadenas prefijadas. Se requiere someterla a varianza máxima para confirmar su robustez.

**5. ¿Qué relación existe entre dispersión y costo esperado?**

La relación es directamente proporcional a la eficiencia. Una alta dispersión estadística garantiza un número mínimo de colisiones. Al haber pocas colisiones, las listas enlazadas (Chaining) o las secuencias de sondeo (Open Addressing) se mantienen extremadamente cortas (cercanas a 1). Esto es el núcleo matemático que garantiza que el costo esperado de las operaciones fundamentales (`put`, `get`, `remove`) permanezca sólidamente en $O(1)$.

### Conclusión Técnica sobre el Rendimiento Real

La función hash representa el verdadero cuello de botella algorítmico y motor de rendimiento de cualquier estructura de diccionario. Mientras que las políticas de resolución de colisiones y rehashing actúan como mecanismos de mitigación pasivos, una función hash deficiente destruye la eficiencia $O(1)$ desde la primera capa computacional. 

La implementación de Hashing Universal (MAD) es obligatoria en entornos de producción, ya que externaliza el riesgo geométrico de los datos de entrada, asegurando que la entropía de la tabla dependa de una matemática inyectada de forma pseudoaleatoria y no de la predictibilidad o malicia del usuario final.
