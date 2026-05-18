# Actividad 1 - Semana 1

**Estudiante:**
Axel Alberto Reyes Baldeón 

## Bloque 0 - Instalación y preparación

- Dejé lista mi carpeta de trabajo.
- Verifiqué que pude abrir Semana1, Proyecto0, Ejercicios0.md, INSTRUCCIONES_Ejercicios0_v4.2.md, stl_optimizacion_demostracion.cpp y resolver_ejercicios0_v4.2.sh.
- Creé el archivo actividad1_semana1.md.
- Anoté mi nombre como único integrante para esta evaluación.

## Bloque 1 - Núcleo conceptual de Semana 1

Archivos revisados:
- Semana1/README.md
- Semana1/src/bubble_sort.cpp
- Semana1/src/power.cpp
- Semana1/src/fibonacci.cpp
- Semana1/src/count_ones.cpp
- Semana1/demos/demo_adt_secuencia.cpp

### 1. Diferencia entre problema, algoritmo, ADT e implementación

* **Problema:** Es el requerimiento o la tarea específica que necesito resolver (ej. "ordenar un conjunto de enteros"). Define el *qué* se debe hacer.
* **Algoritmo:** Es la secuencia finita y lógica de pasos para solucionar el problema, independiente de cualquier lenguaje de programación. Define el *cómo* a nivel conceptual.
* **ADT (Tipo de Dato Abstracto):** Especifica el comportamiento de los datos y las operaciones permitidas (ej. `add()`, `remove()`) como un contrato público, abstrayendo los detalles de cómo están construidas internamente.
* **Implementación:** Es la traducción del algoritmo y el ADT a código fuente en un lenguaje específico (en nuestro caso, C++), gestionando estructuras de datos reales, punteros y asignación de memoria.

### 2. En bubble_sort.cpp, expliquen qué observable conecta correctitud y costo.

Al revisar el código, noté que la optimización del algoritmo se basa en detectar si el arreglo ya alcanzó su estado ordenado antes de completar todas las iteraciones teóricas, utilizando variables de estado como `changed` o `lastSwapIndex`.

* **Correctitud:** Si una iteración completa finaliza sin registrar intercambios (`changed == false`), verifico que el orden local coincide con el orden global. El invariante se cumple y el arreglo está matemáticamente ordenado.
* **Costo:** Al monitorear esta variable, el algoritmo `bubbleSortOptimized` interrumpe el ciclo prematuramente o reduce el rango de evaluación. Esto conecta la validación de un estado "correcto" con la reducción directa del "costo" computacional, evitando comparaciones redundantes que consumen tiempo.

### 3. En power.cpp, expliquen por qué power mejora la idea de una versión ingenua.

La implementación ingenua (`powerBF`) realiza multiplicaciones sucesivas, lo que implica una complejidad temporal lineal O(n) respecto al exponente. 
Por ejemplo: Si `n` es un millón, el programa se ve forzado a hacer un millón de iteraciones.

La versión optimizada (`power`) emplea exponenciación binaria mediante operaciones a nivel de bits (como `n >>= 1`). Al elevar la base al cuadrado en cada iteración, el espacio de búsqueda se reduce a la mitad. Esto disminuye la complejidad temporal de lineal a logarítmica O(log n), logrando una eficiencia notablemente mayor al probarlo con exponentes grandes.

### 4. En fibonacci.cpp, expliquen por qué una función puede ser correcta y aun así ser una mala elección práctica.

La versión recursiva pura (`fib(n)`) es matemáticamente correcta al reflejar la fórmula original, pero resulta inviable en la práctica debido al recálculo redundante de subproblemas. Su complejidad temporal es exponencial y genera un consumo excesivo de memoria en la pila de llamadas (pudiendo provocar un Stack Overflow si le paso un número grande).

La solución práctica requiere la versión iterativa o una implementación con memorización. Estas alternativas me proporcionan el resultado correcto recorriendo los estados una sola vez, lo que reduce la complejidad temporal a O(n).

### 5. En count_ones.cpp, expliquen por qué el tamaño de entrada no siempre coincide con el valor numérico.

En algoritmos orientados a bits, comprendí que el "tamaño de la entrada" que afecta el costo no es la magnitud del valor de `n` (por ejemplo, si le ingreso 10 o 1,000,000), sino la cantidad de espacio (bits) que requiere el modelo RAM para representarlo.

En `countOnes1`, la operación `n &= (n - 1)` limpia el bit encendido más a la derecha en cada iteración. Por lo tanto, el ciclo `while` se ejecuta exactamente la misma cantidad de veces que "unos" haya en su representación binaria, no en base al valor numérico total. El costo depende directamente de la estructura del dato binario.

### 6. En demo_adt_secuencia.cpp, expliquen por qué la misma interfaz puede convivir con representaciones distintas.

Este principio demuestra la utilidad del ADT. La interfaz `IntSequence` actúa como un contrato que garantiza la disponibilidad de métodos estándar (como tamaño o acceso a elementos).

El código cliente que invoca la interfaz opera de manera agnóstica respecto a mi representación interna (ya sea un arreglo estático continuo o un vector de tamaño dinámico). Esta separación me permite optimizar o reemplazar la estructura de datos subyacente sin tener que alterar la lógica de mi programa principal.

## Bloque 2 - Demos y trazado guiado

Archivos revisados:
- Semana1/demos/demo_bubblesort.cpp
- Semana1/demos/demo_power.cpp
- Semana1/demos/demo_fibonacci.cpp
- Semana1/demos/demo_countones.cpp

### TABLA DE ANÁLISIS

| Archivo | Salida u observable importante | Idea algorítmica | Argumento de costo |
| :--- | :--- | :--- | :--- |
| `demo_bubblesort.cpp` | Contadores de comparaciones, intercambios y el índice del último intercambio | Comparar adyacentes y hacer flotar el mayor, optimizando al reducir el rango de búsqueda usando la posición del último intercambio | El conteo de operaciones en la terminal indica si el caso fue el peor(O n²) o mejor(O n). |
| `demo_power.cpp` | Tiempos de ejecución y número de pasos entre las diferentes versiones | Reducir el exponente a la mitad en cada paso usando operaciones de bits(«1) usando la recursividad. | Muestra la diferencia entre un crecimiento lineal (O n) y uno logarítmico (menos pasos). |
| `demo_fibonacci.cpp` | Tiempos de ejecución de la recursiva clásica contra la iterativa | La iterativa construye los valores progresivamente, la recursiva clásica hace call stack recalculando subproblemas (repetidos) | la versión recursiva colapsa por su costo exponencial (recalculo), mientras la iterativa se mantiene estable (O n) |
| `demo_countones.cpp` | Cantidad de bits encendidos calculados mediante desplazamientos (forma binaria). | Utiliza máscaras y desplazamientos para sumar los bits en paralelo; suma en bloques (2, 4 ..) | El costo temporal es O log b (cantidad de bits) teóricamente. En la práctica el tiempo es O 1, ya que se resolverá en exactamente 5 operaciones fijas |

### RESPUESTAS A LAS PREGUNTAS

* Lo principal es la impresión de las variables que cuentan las comparaciones y los intercambios.
* Mostrar el arreglo ordenado al final solo demuestra que el algoritmo es correcto; sin embargo, al ver que las comparaciones disminuyen drásticamente en un arreglo casi ordenado, obtengo la prueba empírica de que la optimización reduce el costo de operaciones.
* Para hallar el exponente de 1000, noté que la fuerza bruta hará 1000 pasos, mientras que la optimizada lo hará en apenas 10 divisiones.
* La diferencia entre `fibI` y `fib` es abismal. Al compilar y correr esto en mi laptop (una HP OMEN), si intento hallar el fibonacci de 20, la versión recursiva se nota pesada debido a la redundancia, mientras que la iterativa me arroja la respuesta en milisegundos.
* Usar 1048576 (2²⁰) parece un valor enorme, pero en representación binaria es simplemente un 1 seguido de 20 ceros. Al ejecutarlo, el programa termina rapidísimo, dejando claro que el esfuerzo del algoritmo depende netamente del tamaño en bits y no de la magnitud decimal.

## Bloque 3 - Pruebas públicas y Sustentación

Archivos revisados:
- Semana1/pruebas_publicas/README.md
- Semana1/pruebas_publicas/test_public_week1.cpp
- Semana1/pruebas_publicas/test_public_week1_extra.cpp
- Semana1/sustentacion/preguntas_semana1.md
- Semana1/sustentacion/rubrica_semana1.md

### 1. ¿Qué funciones o ideas están verificando las pruebas públicas?

Al revisar `test_public_week1.cpp` y `test_public_week1_extra.cpp`, observo que las pruebas están verificando el comportamiento mínimo esperado y casos borde de los algoritmos que implementé. Específicamente validan:

* **Casos base y extremos:** Arreglos vacíos (tamaño 0) para sumas o exponentes 0 en conteos de bits.
* **Correctitud en recursión e iteración:** Que ambas versiones de una misma idea matemática (Suma, Potencias, Fibonacci) me den el mismo resultado.
* **Comportamiento de ADTs y modificaciones:** Que funciones como `bubbleSortOptimized`, `reverseRecursive` y `shiftLeftByK` realmente alteren mi arreglo al estado esperado (ordenado, invertido o desplazado).
* **Propiedades específicas:** Que la Torre de Hanoi ejecute exactamente el número de movimientos matemáticamente esperados.

### 2. ¿Qué sí demuestra una prueba pública?

Demuestra que mi código compila correctamente, que no sufre caídas abruptas (como un Segmentation Fault por acceder mal a la memoria) bajo esas condiciones exactas, y que, para los casos específicos introducidos en el test, el programa genera la salida esperada. Es una validación en un escenario controlado.

### 3. ¿Qué no demuestra una prueba pública?

**No demuestra la correctitud universal de mi algoritmo.** Una prueba pública no evalúa los infinitos tamaños de entrada posibles, no asegura que mi algoritmo sea eficiente (podría pasar la prueba pero tardar horas si le meto un millón de datos), ni garantiza que no vaya a ocurrir un desbordamiento de memoria (Stack Overflow) con casos degenerados que no estén en el test.

### 4. Pregunta de sustentación (Sección 1: Concepto formal de algoritmo)

### 4.1. ¿Qué es un algoritmo y qué condiciones debe cumplir para ser considerado correcto y útil?

Un algoritmo es una secuencia finita, rigurosa y ordenada de pasos lógicos que diseño para resolver un problema específico. 

* Para que lo considere **correcto**, debe garantizar que, dada cualquier entrada válida, el proceso terminará y producirá exactamente la salida esperada (cumple con su especificación matemática/lógica). 
* Para que lo considere **útil (o tratable)**, debe resolver el problema utilizando una cantidad razonable de recursos de mi computadora (tiempo de CPU y RAM). Un algoritmo correcto que tarda milenios en ejecutarse no me sirve en la práctica.

### 4.2. Explica con tus palabras las nociones de:

* **Entrada:** Son los datos iniciales que le paso al algoritmo antes de que empiece a trabajar.
* **Salida:** Es el resultado final que me entrega el algoritmo una vez que ha terminado de procesar.
* **Determinismo:** Significa que no hay ambigüedades. Si le paso exactamente la misma entrada cien veces, el programa ejecutará los mismos pasos y me devolverá la misma salida las cien veces.
* **Factibilidad:** Cada paso debe ser lo suficientemente básico como para que mi computadora pueda ejecutarlo físicamente.
* **Finitud:** Tiene que tener un final garantizado; no puede quedarse en un bucle infinito.
* **Corrección:** Es la garantía de que el código hace lo que promete. La salida obtenida coincide al 100% con la teórica.

### 4.3. Da un ejemplo de procedimiento que no califique como algoritmo y explica por qué.

Un ejemplo clásico es pedir: *"Escribe todos los números pares que existen y luego suma 1"*. O si lo programo: `while(true) { cout << "Hola"; }`.

**¿Por qué no es un algoritmo?** Porque viola directamente el principio de finitud; los números pares son infinitos, por lo que mi programa jamás terminaría de ejecutarse para pasar al siguiente paso.

### 4.4. ¿Por qué la corrección por sí sola no basta para considerar bueno a un algoritmo?

Porque un algoritmo puede dar el resultado matemáticamente correcto pero ser un desastre en consumo de recursos. Como vi con la versión recursiva pura de Fibonacci (`fib(n)`), el código está bien planteado, pero su costo temporal crece exponencialmente. Si le pido calcular un número grande, mi máquina se quedará sin memoria o tardará muchísimo en darme la respuesta.

### 4.5. ¿Qué relación hay entre especificación e implementación?

* La especificación es el "qué" debe hacer mi programa (el problema, la entrada esperada, la salida prometida). Es básicamente el contrato.
* La implementación es el "cómo" lo logro físicamente. Es el trabajo real escribiendo el código en C++, gestionando mis variables y la memoria para cumplir ese contrato.

### 5. Autoevaluación basada en la rúbrica

* **Comprensión conceptual:** **[Logrado]**. He definido con claridad la diferencia teórica y práctica entre problema, algoritmo, correctitud y eficiencia, teniendo claro por qué "funcionar" no es lo mismo que ser tratable.
* **Sustentación de correctitud:** **[Logrado]**. He justificado que la correctitud no la pruebo solo empíricamente (pasando el `test_public`), sino entendiendo las invariantes de mi código (como el orden local en bubblesort).
* **Análisis de eficiencia:** **[Logrado]**. He relacionado el costo temporal con los métodos revisados, identificando cómo las optimizaciones asintóticas salvan a mi programa de tiempos de ejecución inviables.

## Bloque 4 - Puente corto con Proyecto0

Archivos revisados:
- Proyecto0/apps/demo_const_refs.cpp
- Proyecto0/bench/bench_vector_growth.cpp
- Proyecto0/bench/bench_vector_ops.cpp
- Proyecto0/bench/bench_cache_effects.cpp

### 1. ¿Qué diferencia observable deja `demo_const_refs.cpp` entre lectura, modificación y copia?

La salida en mi terminal demuestra claramente cómo se comporta la memoria al llamar a las funciones:

* **Lectura (`sum_readonly`):** No altera mi vector original.
* **Modificación (`append_in_place`):** Muestra que el vector fue alterado directamente en su espacio de memoria, añadiéndole el 4 con un `push_back`.
* **Copia (`appended_copy`):** Al imprimir el original veo que está intacto, pero la copia sí tiene el 99 agregado, demostrando que se duplicó el espacio en memoria.

### 2. En `bench_vector_growth.cpp`, ¿qué cambia con `reserve`?

Cambia drásticamente el tiempo de ejecución. Al usar `push_with_reserve`, mi programa le pide al SO el tamaño de memoria de golpe al inicio. Esto es mucho más rápido que usar `push_without_reserve`, donde el vector nace con capacidad 0 y tiene que estar redimensionándose y copiando datos a cada rato.

### 3. En `bench_vector_ops.cpp`, ¿por qué `push_back`, `insert(begin())` e `insert(middle)` no cuestan lo mismo?

Por cómo funciona la memoria contigua de un `std::vector` en C++. 

* `push_back` es el más veloz porque solo coloca el valor al final del bloque.
* `insert(begin)` es el peor escenario porque me obliga a empujar todos los elementos existentes una posición hacia la derecha en la memoria.
* `insert(middle)` tiene un costo intermedio, ya que solo mueve la mitad de los elementos.

### 4. En `bench_cache_effects.cpp`, ¿qué intuición deja sobre localidad de memoria?

Me deja muy claro que leer datos de forma secuencial es muchísimo más rápido que dar saltos aleatorios, por cómo interactúa el hardware.

* `sum_vector_sequential` vuela porque aprovecha la localidad espacial; el procesador lee los bloques enteros (líneas de caché) que trae de la RAM.
* `sum_vector_random_access` castiga el rendimiento. Al leer aleatoriamente, el procesador falla en encontrar el dato en caché (cache miss) y pierde tiempo yendo a la RAM constantemente.
* `sum_list` es lento porque los nodos de la lista enlazada están dispersos por toda mi memoria RAM, rompiendo la eficiencia del caché.

## Bloque 5 - Extensión breve con Ejercicios0

Archivos revisados:
- Ejercicios0.md
- INSTRUCCIONES_Ejercicios0_v4.2.md
- stl_optimizacion_demostracion.cpp
- resolver_ejercicios0_v4.2.sh

### 1. Según `Ejercicios0.md`, ¿cuál es el orden correcto antes de optimizar?

La metodología técnica me exige seguir estos cuatro pasos:

1. Elegir el algoritmo y la estructura de datos adecuados desde el inicio.
2. Verificar rigurosamente que mi lógica sea correcta.
3. Medir el rendimiento inicial con datos reales (hacer profiling).
4. Recién ahí, explorar optimizaciones avanzadas de compilación. 
El microajuste no salva un mal diseño algorítmico.

### 2. ¿Qué quiere mostrar `stl_optimizacion_demostracion.cpp` con `reserve`, `nth_element`, `partial_sort` y `lower_bound`?

Me demuestra objetivamente que conocer y usar la función correcta de la biblioteca estándar (STL) me da un salto de eficiencia brutal, muy superior a intentar micro-optimizar código manual.

* `reserve()`: Evito el costo de pedir memoria repetidas veces cuando mi vector crece.
* `nth_element()`: Me permite hallar el k-ésimo elemento en tiempo $O(n)$, evitándome el costo $O(n \log n)$ de hacer un `sort()` a todo el arreglo.
* `partial_sort()`: Super eficiente si solo necesito el Top-K de una lista enorme.
* `lower_bound()`: Aprovecha vectores ordenados para hacer búsquedas binarias en $O(\log n)$, destrozando los tiempos de una búsqueda lineal tradicional.

### 3. ¿Qué tipo de evidencia puede producir `resolver_ejercicios0_v4.2.sh`?

Al correr este script en mi terminal, me automatiza la compilación y me escupe evidencia empírica clave:

- Tiempos reales de ejecución en segundos.
- El peso físico de mis binarios compilados.
- Advertencias (warnings) que arroja el compilador.
- Reportes de cobertura de mi código (`gcov`).
- Trazas de sanitizers (ASan, UBSan) que me chivatean si estoy haciendo accesos indebidos a la memoria o provocando data races.

### 4. ¿Qué limitaciones de entorno menciona `INSTRUCCIONES_Ejercicios0_v4.2.md`?

Menciona problemas de compatibilidad graves si intento correr esto en entornos Windows tradicionales (como Git Bash o MSYS2 base). Herramientas como los sanitizers de memoria o el profiler pueden fallar o no enganchar bien. Recomienda usar el entorno UCRT64 o directamente ir por WSL Ubuntu/Linux nativo para sacarle el jugo a las herramientas de profiling.

### 5. ¿Por qué esta parte no reemplaza la discusión de correctitud de Semana1?

Porque aquí solo estoy midiendo el rendimiento físico (tiempo, memoria) de mi código frente a casos limitados. El benchmark me puede decir que mi código corre en 1 milisegundo, pero eso no me asegura que la matemática detrás no falle en un caso extremo. La Semana 1 me dio las herramientas lógicas (invariantes, casos base) para asegurar que el algoritmo es correcto por diseño; este bloque solo prueba qué tan rápido corre esa implementación en mi máquina.

## Bloque 6 - Cierre comparativo

En la primera semana mi objetivo era responder "¿Mi código hace lo que le piden matemáticamente?", mientras que ahora, con la evidencia experimental, respondo "¿Cómo sobrevive este código interactuando con mi hardware real bajo estrés?".

* **Afirmación de especificación:** El contrato inicial es solo la base. Puedo escribir cinco implementaciones distintas que cumplan la misma especificación, pero que físicamente se comporten de maneras totalmente opuestas.
* **Afirmación de correctitud:** Que el código dé la respuesta correcta ya no es la meta, es lo mínimo indispensable. Si está mal programado lógicamente, ni siquiera vale la pena medirlo en el benchmark.
* **Afirmación de costo:** Comprobé que la teoría asintótica puede engañar. Dos algoritmos $O(n)$ pueden tener tiempos de ejecución abismalmente diferentes en mi máquina por latencias del caché o constantes ocultas.
* **Afirmación de representación o memoria:** No importa cuánta RAM tenga, si estructuro mal mis datos (como en una lista enlazada fragmentada) destruyo el rendimiento. La memoria contigua manda.
* **Advertencia metodológica:** No puedo confiar en ejecutar mi programa una sola vez y mirar el reloj. Debo medir correctamente el movimiento de datos y asegurarme de que el compilador (con sus flags de optimización) no esté eliminando el código que justamente estoy intentando evaluar.