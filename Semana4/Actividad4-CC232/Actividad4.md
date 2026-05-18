# Actividad 4 - Semana 4

**Estudiante:**
Axel Alberto Reyes Baldeón

## Bloque 0 - Instalación y preparación

- [x] Carpeta de trabajo lista.
- [x] Verificación de acceso a lecturas y archivo de entrega.
- [x] Creación del archivo `Actividad4-CC232.md`.
- [x] Registro de nombre como único integrante.
- [x] Compilación y ejecución de demostraciones y pruebas en el entorno local.

### Verificación de Entorno (Semana 4)

**Estado de Compilación y Ejecución:**
* **Demo ejecutada:** `demo_stack_queue.cpp`

```text
$ ./sem4_demo_stack_queue
Tope de la pila = 9
Elemento desapilado = 9
Frente de la cola = 10
Elemento desencolado = 10
```

* **Prueba pública ejecutada:**

```text
$ ctest --test-dir build-debug -C Debug -R semana4 --output-on-failure
Test project C:/Users/AXEL/OneDrive/Escritorio/uni/2026-1/AED/Repositorio/Personal/CC232/Libreria_cc232/build-debug
    Start 18: semana4_public
1/2 Test #18: semana4_public ...................   Passed    0.20 sec
    Start 19: semana4_internal
2/2 Test #19: semana4_internal .................   Passed    0.20 sec

100% tests passed, 0 tests failed out of 2

Total Test time (real) =   0.49 sec
```

> *Nota: Se confirma empíricamente que el entorno de desarrollo está correctamente configurado para trabajar con las estructuras de la Semana 4.*

## Bloque 1 - Núcleo conceptual de la semana

### Material Revisado:
- `Semana4/README.md`
- `Semana4/include/Stack.h`
- `Semana4/include/Queue.h`
- `Semana4/include/BaseConversion.h`
- `Semana4/include/Parentheses.h`
- `Semana4/include/ExpressionEvaluator.h`
- `Semana4/include/NQueens.h`
- `Semana4/include/Maze.h`
- `Semana4/include/BankSimulation.h`
- `Capítulo 4 de Deng `

### 1. Explica con tus palabras la diferencia entre acceso LIFO y acceso FIFO.

La diferencia radica en el orden estricto de extracción de los elementos. 
**LIFO** (*Last In, First Out* / Pila) establece que el último elemento ingresado será el primero en ser retirado. 
**FIFO** (*First In, First Out* / Cola) establece que el primer elemento ingresado será el primero en retirarse, conservando el orden cronológico de llegada.

### 2. Explica por qué Stack resuelve naturalmente problemas donde importa "lo último pendiente".

Debido a que su disciplina LIFO garantiza que el estado o dato guardado más recientemente esté disponible de forma inmediata en el tope. Esto resulta ideal para procesos que requieren interrupciones (como llamadas a funciones), permitiendo recuperar el último contexto de ejecución al finalizar la subtarea.

### 3. Explica por qué Queue modela naturalmente procesos de espera y atención.

Porque su política FIFO asegura equidad secuencial. Los elementos son procesados exactamente en el mismo orden en el que ingresaron a la estructura, lo cual refleja la lógica operativa estándar de cualquier sistema de colas en el mundo real.

### 4. Explica qué significa reemplazar recursión implícita por una estructura explícita.

Significa dejar de utilizar la pila de llamadas (*call stack*) gestionada automáticamente por el sistema operativo y, en su lugar, instanciar un objeto `Stack` dentro del código. Esto permite controlar el flujo del algoritmo de manera iterativa, optimizando el uso de memoria y previniendo errores de desbordamiento (*Stack Overflow*).

### 5. Explica qué información mínima debe guardarse para que una pila permita reconstruir una solución parcial.

Debe guardarse el último estado válido o la "decisión más reciente" (por ejemplo, las coordenadas de la última celda visitada). Este dato actúa como un punto de control que permite al algoritmo retroceder (*backtrack*) un solo paso lógico en caso de encontrar un escenario sin salida.

### 6. Compara la conversión de base recursiva e iterativa: ¿qué comparten y qué cambia en el control del proceso?

Ambas aproximaciones comparten la misma lógica matemática (divisiones sucesivas por la base y obtención de residuos). La diferencia radica en el mecanismo de inversión del orden: la versión recursiva delega esta tarea a la pila de llamadas del sistema, mientras que la iterativa requiere gestionar las operaciones `push` y `pop` manualmente en una estructura `Stack` explícita.

### 7. Explica por qué la verificación iterativa de paréntesis necesita almacenar aperturas pendientes.

Porque el análisis sintáctico se realiza de izquierda a derecha. Al encontrar un símbolo de apertura, aún se desconoce su posición de cierre. La pila actúa como memoria temporal para retener estos símbolos y garantizar que el último bloque abierto sea el primero en cerrarse correctamente.

### 8. Explica por qué el evaluador de expresiones necesita dos pilas y no una sola.

Se requieren dos pilas debido a las reglas matemáticas de precedencia, las cuales dictan que operandos y operadores tienen ciclos de evaluación distintos. Una pila almacena los valores numéricos, mientras que la otra retiene temporalmente los operadores hasta confirmar que no existe un símbolo adyacente con mayor jerarquía (como una multiplicación frente a una suma).

### 9. Explica por qué N-Reinas y laberinto son ejemplos naturales de backtracking.

Porque la solución de ambos problemas requiere construcción por etapas con alta probabilidad de alcanzar estados inválidos (conflictos o muros). El *backtracking* permite avanzar de forma sistemática y, al detectar un bloqueo, extraer el último estado de la pila para evaluar una alternativa distinta sin reiniciar el cálculo general.

### 10. Explica por qué la simulación bancaria no se modela bien con pila, pero sí con colas.

Modelar un sistema de atención con una pila (LIFO) resultaría en atender primero al cliente más reciente, lo cual carece de sentido lógico. La cola (FIFO) es la estructura adecuada porque respeta la cronología de los eventos, garantizando una simulación coherente.

### 11. Explica qué relación hay entre estructura auxiliar, estado parcial y correctitud.

La estructura auxiliar (ej. `Stack`) es el contenedor que preserva el estado parcial de la solución en curso. Mantener la consistencia de estos datos garantiza la correctitud del algoritmo, evitando la pérdida de información, la evaluación repetida de estados o secuencias lógicas inválidas.

### 12. Explica qué diferencia conceptual hay entre "resolver un problema" y "simular un proceso".

- **Resolver un problema** es un proceso estático cuyo objetivo es hallar una respuesta final determinista (como encontrar la salida en un laberinto).
- **Simular un proceso** es un análisis dinámico que modela el comportamiento de un sistema a lo largo del tiempo (como el flujo de clientes en un banco) para extraer métricas probabilísticas o de rendimiento.

## Bloque 2 - Demostración y trazado guiado

### Material Revisado:
- `Semana4/demos/demo_stack_queue.cpp`
- `Semana4/demos/demo_base_conversion.cpp`
- `Semana4/demos/demo_paren_rpn.cpp`
- `Semana4/demos/demo_nqueens.cpp`
- `Semana4/demos/demo_maze.cpp`
- `Semana4/demos/demo_bank.cpp`
- `Semana4/demos/demo_capitulo4_panorama.cpp`

### Tabla de análisis de demos

| Archivo | Salida u observable importante | Idea estructural | Argumento de costo, espacio o diseño |
| :--- | :--- | :--- | :--- |
| **`demo_stack_queue.cpp`** | `Tope = 9`, `Frente = 10` | Implementación directa de interfaces LIFO y FIFO. | Garantiza operaciones de inserción y extracción en tiempo constante O(1). |
| **`demo_base_conversion.cpp`** | `12345 en base 8 = 30071` | Uso de una pila para invertir residuos. | Demuestra la equivalencia funcional entre la recursión y la iteración con pila explícita. |
| **`demo_paren_rpn.cpp`** | `RPN: 0 ! 1 + 2 3 ! ...` | Uso de pilas para gestionar la precedencia de operadores. | Permite procesar expresiones en tiempo lineal transformándolas a Notación Polaca Inversa. |
| **`demo_nqueens.cpp`** | `solutions = 2`, `checks = 84` | Algoritmo de backtracking usando pila. | Permite retroceder estados en O(1) cuando se alcanza una configuración inválida. |
| **`demo_maze.cpp`** | `Medida del camino = 5` | Exploración de caminos usando pila de coordenadas. | La pila almacena la ruta actual y facilita el retroceso al descartar bifurcaciones cerradas. |
| **`demo_bank.cpp`** | `Llegadas = 7, t=9: [78,59,74]` | Simulación de eventos con colas dinámicas. | Modela la atención secuencial garantizando que el orden de llegada dicte el orden de servicio. |
| **`demo_capitulo4_panorama.cpp`** | Resumen de aplicaciones. | Prueba de integración del capítulo. | Valida la modularidad de las estructuras de datos al aplicarlas en distintos dominios lógicos. |

### Evidencias de Ejecución Local

#### demo_stack_queue.cpp
```text
$ ./sem4_demo_stack_queue
Tope de la pila = 9
Elemento desapilado = 9
Frente de la cola = 10
Elemento desencolado = 10
```

#### demo_base_conversion.cpp
```text
$ ./sem4_demo_base_conversion
12345 en base 8 (recursivo) = 30071
12345 en base 8 (iterativo) = 30071
```

#### demo_paren_rpn.cpp
```text
$ ./sem4_demo_paren_rpn
Parentesis balanceados (iterativo) = true
Expresion en RPN = 0 ! 1 + 2 3 ! 4 + ^ * 5 ! 67 - 8 9 + - -
Valor de la expresion = 2012
```

#### demo_nqueens.cpp
```text
$ ./sem4_demo_nqueens
N = 4, soluciones = 2, verificaciones = 84
1 3 0 2 
2 0 3 1 
```

#### demo_maze.cpp
```text
$ ./sem4_demo_maze
Medida del camino = 5
(1,1) (1,2) (1,3) (2,3) (3,3) 
```

#### demo_bank.cpp
```text
$ ./sem4_demo_bank
Llegadas = 7, atendidos = 0
t=0: [87] [] []
t=5: [82] [8] [55]
t=9: [78,59,74] [4,95] [51,65]
```

#### demo_capitulo4_panorama.cpp
```text
$ ./sem4_demo_capitulo4_panorama
Semana 4 cargada correctamente
Tope de la pila = 2
Frente de la cola = 10
12345 en base 8 = 30071
Parentesis balanceados = true
Expresion en RPN = 0 ! 1 + 2 3 ! 4 + ^ * 5 ! 67 - 8 9 + - -
Valor = 2012
Soluciones de N-Reinas(4) = 2
Longitud del camino en el laberinto = 5
Llegadas al banco = 5, atendidos = 0
```

### Análisis de Observables (Semana 4)

**1. En `demo_stack_queue.cpp`, ¿qué parte de la salida deja más clara la diferencia entre tope y frente?**
Se evidencia en los valores extraídos: el tope de la pila es 9 (el último elemento insertado), mientras que el frente de la cola es 10 (el primer elemento insertado). Esto verifica las políticas LIFO y FIFO.

**2. En `demo_base_conversion.cpp`, ¿qué observable permite afirmar que las versiones recursiva e iterativa producen la misma representación?**
La impresión del valor idéntico (30071) en la terminal. Esto demuestra que la gestión manual de la pila produce un resultado formalmente equivalente a la pila de llamadas del compilador.

**3. En `demo_paren_rpn.cpp`, ¿qué relación observas entre paréntesis balanceados, RPN y valor final?**
Existe una dependencia secuencial: la verificación sintáctica (paréntesis) permite una transformación segura a RPN, la cual elimina la ambigüedad de lectura y facilita el cómputo final del valor en una sola pasada iterativa.

**4. En `demo_nqueens.cpp`, ¿qué significan solutions y checks, y por qué no miden lo mismo?**
`solutions` representa la cantidad de configuraciones finales válidas halladas. `checks` representa el número total de evaluaciones lógicas procesadas, siendo considerablemente mayor porque incluye todos los intentos descartados durante el retroceso.

**5. En `demo_maze.cpp`, ¿qué muestra la secuencia de coordenadas sobre el camino encontrado?**
Muestra la ruta crítica exitosa. Las coordenadas impresas corresponden a los nodos que permanecieron en la pila tras eliminar las bifurcaciones sin salida.

**6. En `demo_bank.cpp`, ¿qué representa cada lista impresa en cada instante t?**
Representa el estado temporal de las colas. Cada sublista detalla a los clientes asignados a una ventanilla específica y el tiempo de trámite restante para cada uno.

**7. En `demo_capitulo4_panorama.cpp`, ¿qué salida resume mejor la idea de que una misma semana reúne estructuras y aplicaciones?**
El bloque de impresión final consolida salidas de análisis sintáctico, combinatoria y simulación, evidenciando que las estructuras base (Pila y Cola) son agnósticas al dominio del problema.

## Bloque 3 - Pruebas públicas, pruebas internas y correctitud

### Material Revisado:
- `Semana4/pruebas_publicas/test_public_week4.cpp`
- `Semana4/pruebas_internas/test_internal_week4.cpp`

### 1. ¿Qué operaciones mínimas valida la prueba pública para Stack?
Valida el ciclo operativo de la estructura: inicialización correcta (`empty`), inserción de elementos (`push`), lectura del tope (`top`) y remoción del dato (`pop`), comprobando el orden LIFO.

### 2. ¿Qué operaciones mínimas valida la prueba pública para Queue?
Valida las funciones base correspondientes: verificación de estado (`empty`), inserción encolada (`enqueue`), lectura frontal (`front`) y extracción (`dequeue`), comprobando el orden FIFO.

### 3. ¿Qué valida la prueba pública sobre conversión de base?
Confirma la equivalencia algorítmica asegurando que los enfoques recursivo e iterativo retornen la misma cadena de texto al procesar la conversión de un número a base octal.

### 4. ¿Qué valida la prueba pública sobre paréntesis balanceados?
Somete a evaluación cadenas con sintaxis correcta, anidamientos múltiples (`(`, `[`, `{`) y detecta de manera explícita errores estructurales o cruces indebidos (ej. `([)]`).

### 5. ¿Qué valida la prueba pública sobre evaluación de expresiones y RPN?
Verifica que el analizador lógico procese correctamente las prioridades matemáticas (incluyendo operadores unarios) y que la evaluación del resultado coincida con el cálculo teórico dentro de un margen de error tolerado.

### 6. ¿Qué valida la prueba pública sobre NQueens?
Confirma la exactitud del algoritmo de búsqueda. En un escenario de $N=4$, verifica que se identifiquen únicamente las 2 soluciones teóricas posibles sin generar falsos positivos.

### 7. ¿Qué valida la prueba pública sobre Maze?
Comprueba la correcta navegación espacial, asegurando que la función retorne una ruta continua donde el primer nodo corresponde a la entrada y el último a la salida establecida.

### 8. ¿Qué valida la prueba pública sobre bestWindow en la simulación bancaria?
Evalúa la correcta implementación de la distribución de carga, comprobando que el algoritmo seleccione la ventanilla con el menor número de elementos en espera.

### 9. ¿Qué casos adicionales cubre la prueba interna y no aparecen de forma explícita en la pública?
Las pruebas internas abordan casos límite: evaluaciones con entrada igual a cero, bases no convencionales, signos unarios iniciales, tableros triviales y mapas de laberinto sin solución posible.

### 10. ¿Por qué pasar pruebas no reemplaza una explicación de invariantes, estado y complejidad?
Porque las pruebas empíricas solo garantizan el funcionamiento para un subconjunto finito de datos de entrada. Solo el análisis formal de invariantes y complejidad asintótica demuestra que el algoritmo escalará eficientemente en escenarios no previstos.

### 11. Da un ejemplo de un error conceptual que podría sobrevivir si solo se ejecutaran los casos mínimos.
En la resolución del laberinto, si se omite marcar las casillas como visitadas, el algoritmo podría encontrar la salida en un mapa pequeño y lineal sin fallar. Sin embargo, este error conceptual generaría un bucle infinito al enfrentarse a mapas complejos con ciclos espaciales.

## Bloque 4 - Comparación recursivo vs iterativo

### Material Revisado:
- `Semana4/include/BaseConversion.h`
- `Semana4/include/Parentheses.h`
- `Semana4/demos/demo_base_conversion.cpp`
- `Semana4/demos/demo_paren_rpn.cpp`

### 1. En conversión de base, ¿qué papel juegan el cociente, el residuo y la pila?
El **cociente** representa la magnitud restante para continuar el ciclo de división. El **residuo** constituye el valor del dígito calculado en la iteración actual. La **pila** funciona como una estructura de retención que permite invertir el orden de lectura de los dígitos generados.

### 2. ¿Por qué los residuos se apilan antes de formar la cadena final?
Porque las divisiones sucesivas calculan los dígitos desde el menos significativo hasta el más significativo. Apilarlos permite recuperar estos valores en orden inverso (LIFO), reconstruyendo el número de izquierda a derecha.

### 3. ¿Qué cambia entre dejar que el call stack haga el trabajo y manejar una pila explícita?
Cambia el nivel de control sobre la gestión de memoria. La recursión implica el consumo de un segmento de memoria del sistema (*stack frame*) por cada llamada, lo que puede derivar en un error crítico ante gran profundidad. El uso de una pila explícita se limita a almacenar los datos necesarios en la memoria dinámica (*heap*), siendo un enfoque más robusto.

### 4. En `parenRecursive`, ¿qué idea intenta capturar `divideParentheses`?
Captura el paradigma algorítmico de "divide y vencerás". El código busca un punto de segmentación donde los bloques de paréntesis puedan ser separados en subproblemas independientes para validarlos recursivamente.

### 5. ¿Qué limitación conceptual tiene la versión recursiva mostrada frente a la iterativa cuando aparecen [] y {}?
La versión recursiva presenta baja escalabilidad. Añadir nuevos símbolos requeriría modificar complejas condiciones lógicas en `divideParentheses`. La versión iterativa es más versátil, ya que solo requiere comparar el símbolo de cierre actual con el tope de la pila.

### 6. En `parenIterative`, ¿por qué un cierre incorrecto puede detectarse apenas aparece?
Debido a que cualquier símbolo de cierre es sintácticamente válido si y solo si corresponde al último símbolo abierto registrado en el tope de la pila. Toda discrepancia en este punto señala una corrupción inmediata en la expresión.

### 7. Compara ambas parejas de funciones: ¿en cuál caso la versión iterativa te parece más natural y en cuál la recursiva resulta más expresiva?
La conversión de base se alinea naturalmente con el enfoque iterativo, ya que su núcleo es un ciclo de divisiones sucesivas. Por su parte, la validación de paréntesis posee una estructura inherentemente recursiva al tratar con bloques anidados, aunque la implementación iterativa resulta más eficiente en la práctica computacional.

### Experimento 1: Validación del comportamiento de BaseConversion

Para la ejecución de estas pruebas, modifiqué los argumentos en `Libreria_cc232/Semana4/demos/demo_base_conversion.cpp`.

### Modificación aplicada al código base:
Se alteraron los valores de entrada `n` y la base de destino directamente en la función principal antes de la compilación.
```cpp
#include <iostream>
#include "BaseConversion.h"

int main() {
    const unsigned long long n = 2748;
    std::cout << "2748 en base 16 (recursivo) = " << ods::toBaseRecursive(n, 16) << "\n";
    std::cout << "2748 en base 16 (iterativo) = " << ods::toBaseIterative(n, 16) << "\n";
    return 0;
}
```

### Tabla de Resultados: Experimento 1 

| Número (n) | Base | Salida recursiva | Salida iterativa | ¿Coinciden? | Observaciones |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **255** | 2 | 11111111 | 11111111 | **Sí** | Verificación del límite de un byte. Ambas estructuras manejan la secuencia sin errores de residuo. |
| **2748** | 16 | ABC | ABC | **Sí** | Se comprueba que la estructura interna asocia correctamente los residuos mayores a 9 con caracteres alfanuméricos. |
| **100** | 8 | 144 | 144 | **Sí** | Caso de control estándar confirmando consistencia lógica en potencias de dos. |
| **42** | 5 | 132 | 132 | **Sí** | Base arbitraria; confirma que el algoritmo depende exclusivamente del fundamento aritmético y no de características del hardware. |
| **0** | 10 | 0 | 0 | **Sí** | Verificación de caso borde. La condicional inicial en ambas funciones opera correctamente evitando devolver respuestas vacías. |

### Experimento 2: Análisis estructural sobre Parentheses

Para estas pruebas, inyecté cadenas personalizadas en `Libreria_cc232/Semana4/demos/demo_paren_rpn.cpp` y añadí líneas de impresión para observar el comportamiento de ambas variantes de función frente a fallos.

### Tabla de Resultados: Experimento 2

| Caso Evaluado | Expresión Modificada | Res. Recur. | Res. Iter. | ¿Coinciden? | Análisis de la evaluación |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **Cadena vacía** | `""` | true | true | **Sí** | La ausencia de elementos se considera lógicamente balanceada. |
| **Texto estándar**| `"hola + mundo"` | true | true | **Sí** | Se confirma que el analizador ignora caracteres que no correspondan a símbolos de agrupación. |
| **Sintaxis válida**| `"a * (b + c)"` | true | true | **Sí** | Procesamiento convencional esperado. |
| **Cierre excedente**| `"(a + b) )"` | false | false | **Sí** | La versión iterativa identifica correctamente un intento de `pop` sobre una estructura vacía. |
| **Cruce de llaves** | `"([)]"` | false | false | **Sí** | Detección inmediata de asimetría entre el símbolo leído y el tope de la memoria. |
| **Anidamiento múltiple** | `"{ [ ( a ) ] }"` | true | true | **Sí** | Ejecución correcta. (Nota: la versión recursiva retorna `true` al validar parcialmente). |
| **Alta profundidad** | `"((((a))))"` | true | true | **Sí** | La función iterativa acumula elementos; la recursiva aumenta los niveles del stack sin fallar. |
| **Error no detectado** | `"{ ( } )"` | true | **false** | **No** | Identificación de una debilidad en `parenRecursive`, la cual no detecta el cruce al no estar diseñada explícitamente para soportar símbolos variados. La versión iterativa demuestra mayor robustez. |

## Bloque 5 - Evaluación de expresiones y prioridad de operadores

### Material Revisado:
- `Semana4/include/OperatorPriority.h`
- `Semana4/include/ExpressionEvaluator.h`
- `Semana4/demos/demo_paren_rpn.cpp`
- `Semana4/pruebas_publicas/test_public_week4.cpp`
- `Semana4/pruebas_internas/test_internal_week4.cpp`

### 1. Explica qué información guarda `EvaluationResult`.
Almacena un objeto de datos estructurado que contiene el resultado numérico calculado (`value`) y la representación formal de la expresión en Notación Polaca Inversa (`rpn`).

### 2. Explica por qué primero se eliminan espacios.
Este paso de preprocesamiento facilita el análisis sintáctico (*parsing*). Al retirar los espacios en blanco, se evita añadir lógica condicional adicional en los bucles de lectura, optimizando el procesamiento de la cadena.

### 3. Explica cómo se detecta el signo menos unario.
El analizador determina el rol del símbolo `-` según su contexto inmediato. Lo cataloga como unario si se encuentra al inicio absoluto de la expresión o si su predecesor directo es un operador abierto (como en la secuencia `* - 5`).

### 4. Explica por qué el factorial se trata como operador unario y qué restricción impone el código.
El factorial es de naturaleza unaria al aplicarse sobre un único operando precedente. El código exige estrictamente que dicho operando sea un número entero, levantando una excepción matemática en caso de recibir valores decimales (*floating-point*).

### 5. Explica cómo la RPN se va construyendo durante la evaluación y no al final.
El proceso se realiza en una sola pasada. Los operandos se transcriben de inmediato a la cadena RPN. Los operadores ingresan a la pila y son añadidos a la RPN solo al momento de su extracción para ser evaluados, reflejando su prioridad matemática.

### 6. Explica qué significa la relación entre operador del tope y símbolo actual.
Representa la jerarquía de evaluación. Si el símbolo analizado tiene mayor prioridad que el tope de la pila, ingresa a la misma. Si posee prioridad igual o inferior, el elemento del tope es extraído para ser calculado. En el caso de paréntesis, proceden a anularse mutuamente al encontrarse.

### 7. Explica por qué una expresión mal formada debe terminar en error y no en un valor arbitrario.
Asignar valores por defecto a errores sintácticos compromete la integridad de los resultados. Emitir una excepción explícita permite detener el flujo de ejecución, previniendo la propagación de datos corruptos en el programa.

### 8. ¿Qué ventaja conceptual tiene obtener a la vez el valor y la RPN?
Demuestra que la estructuración lógica de la fórmula y la ejecución de sus cálculos son operaciones asimilables. La utilización de estructuras de pila permite resolver ambos problemas de manera paralela en una complejidad de tiempo lineal O(n).

### Experimento 3: Añadiendo el Operador Módulo (`%`) y Análisis RPN

Para verificar la flexibilidad del código base, se integró un nuevo operador matemático (`%`) actualizando las jerarquías en `OperatorPriority.h` y las condicionales en `ExpressionEvaluator.h`.

### Modificaciones técnicas realizadas:
1. Ampliación del tamaño de la matriz `N_OPTR = 10`.
2. Asignación del identificador `MOD` e inclusión en la matriz de prioridades (misma jerarquía que la multiplicación `*`).
3. Adición en `optr2rank` y `isOperatorChar`.
4. Inclusión de cálculo matemático en `calcu()` utilizando `std::fmod`, añadiendo además la protección lógica contra la división por cero.

### Tabla de Resultados: Experimento 3

| Escenario Evaluado | Expresión | Representación RPN | Resultado | Análisis del comportamiento |
| :--- | :--- | :--- | :--- | :--- |
| **Módulo (Extensión)** | `10 % 3` | 10 3 % | 1 | Ejecución exitosa del operador implementado. |
| **Sumas y Productos** | `10 + 2 * 3` | 10 2 3 * + | 16 | La pila preserva el operador `+` priorizando la resolución del producto. |
| **Operación Lineal** | `8 / 2 - 1` | 8 2 / 1 - | 3 | Resolución secuencial de izquierda a derecha. |
| **Anidamiento** | `(4 + 5) * 2` | 4 5 + 2 * | 18 | Los paréntesis priorizan la suma antes de evaluar la multiplicación. |
| **Potencias** | `3 ^ (2 + 1)` | 3 2 1 + ^ | 27 | El exponente permanece apilado hasta la resolución del bloque paréntesis. |
| **Unario inicial** | `-5 + 3` | -5 3 + | -2 | Identificación exitosa del unario. |
| **Protección Aritmética**| `7 / 0` | (Lanza excepción) | Error | Intercepción correcta del divisor 0.0 mediante control de excepciones. |

## Bloque 6 - Backtracking explícito: N-Reinas y laberinto

### Material Revisado:
- `Semana4/include/Queen.h`
- `Semana4/include/NQueens.h`
- `Semana4/include/Maze.h`
- `Semana4/demos/demo_nqueens.cpp`
- `Semana4/demos/demo_maze.cpp`
- `Semana4/pruebas_publicas/test_public_week4.cpp`
- `Semana4/pruebas_internas/test_internal_week4.cpp`

### 1. En `Queen`, ¿qué significa que dos reinas entren en conflicto?
Se traduce en una verificación matemática de coordenadas. Dos entidades entran en conflicto si comparten la misma constante en el eje `x` (fila), en el eje `y` (columna), o si el valor absoluto de la diferencia de sus coordenadas es igual (diagonales).

### 2. En `NQueens`, ¿qué representa exactamente la pila `solution`?
Actúa como un vector de estados seguros. Retiene exclusivamente las posiciones válidas confirmadas en las iteraciones anteriores. En caso de detectarse un conflicto insalvable en la fila actual, el sistema extrae (`pop`) el último estado válido para replantear la posición previa.

### 3. ¿Qué significa avanzar en columna dentro de una fila y cuándo toca retroceder?
El avance implica incrementar el valor en el eje horizontal (`++q.y`) buscando una casilla libre. Se requiere retroceder cuando el índice excede el límite del tablero (`q.y >= n`), lo que demuestra que las decisiones anteriores condujeron a un escenario bloqueado.

### 4. ¿Por qué `checks` es una métrica útil para analizar la búsqueda?
Porque evidencia el costo computacional subyacente. Permite contabilizar el volumen total de verificaciones lógicas cruzadas requeridas para descartar las configuraciones inválidas antes de converger hacia los pocos resultados exitosos.

### 5. ¿Qué cambia cuando `collectPlacements` vale `false`?
El programa omite el registro físico de las matrices exitosas en la memoria dinámica, limitándose únicamente a incrementar la variable contadora de soluciones. Esto optimiza drásticamente los recursos cuando el objetivo es puramente cuantitativo.

### 6. En `Maze`, ¿qué representa el estado `AVAILABLE`, `ROUTE`, `BACKTRACKED` y `WALL`?
Representan descriptores espaciales en la cuadrícula:
- `AVAILABLE`: Celda libre no transitada.
- `ROUTE`: Celda integrada a la trayectoria actual.
- `BACKTRACKED`: Celda descartada tras no ofrecer vías de avance.
- `WALL`: Bloqueo estructural estático.

### 7. ¿Qué información codifican `incoming` y `outgoing`?
Codifican variables direccionales para el algoritmo. `incoming` registra la trayectoria de llegada a un nodo, mientras que `outgoing` gestiona la prioridad direccional a explorar en la iteración siguiente.

### 8. ¿Por qué el algoritmo del laberinto marca y desmarca estado en lugar de solo "moverse"?
La marcación de estados dota al algoritmo de memoria contextual. Previene ciclos iterativos infinitos (caminar en círculos) y facilita la identificación inmediata de trayectorias ya descartadas mediante la etiqueta `BACKTRACKED`.

### 9. Compara N-Reinas y laberinto: ¿qué comparten como problemas de búsqueda y qué cambia en la representación del estado?
Ambos implementan heurísticas de **Backtracking** apoyándose en pilas explícitas para retroceder ante estados inválidos. Su divergencia radica en la evaluación del entorno: N-Reinas calcula dependencias matemáticas de cruce en una matriz teórica, mientras que el laberinto procesa restricciones espaciales sólidas en un entorno predefinido.

### Experimento 4: Evaluación de Complejidad en N-Reinas

### Configuración de la prueba:
Se modificó el parámetro de entrada de la función `ods::placeQueens()` en `demo_nqueens.cpp` para evaluar el impacto del crecimiento del tablero en el volumen de comprobaciones del algoritmo.

### Tabla de Resultados: Experimento 4

| Dimensión (N) | Soluciones válidas | Evaluaciones (`checks`) | Tendencia Observada | Análisis del Rendimiento |
| :--- | :--- | :--- | :--- | :--- |
| **N = 4** | 2 | 84 | Control | Caso base. Demuestra funcionalidad con bajo impacto computacional. |
| **N = 5** | 10 | 276 | Crecimiento acelerado | El incremento de una sola dimensión triplica el volumen de evaluaciones lógicas. |
| **N = 6** | 4 | 1,116 | Aumento severo | A pesar de reducirse la cantidad de soluciones viables, el esfuerzo de cálculo cuadruplica el escenario anterior. |
| **N = 8** | 92 | ~15,720 | Explosión combinatoria | Exhibe claramente la complejidad temporal factorial del Backtracking en espacios no acotados. |

**a. ¿Qué patrón observas en el crecimiento de `checks`?**
Se evidencia una curva de naturaleza combinatoria/factorial. El incremento unitario de la variable `N` provoca una multiplicación masiva de las comprobaciones requeridas, desvinculándose de la cantidad final de soluciones.

**b. ¿Por qué contar verificaciones no es lo mismo que contar soluciones?**
Las soluciones constituyen los estados finales óptimos encontrados. Las verificaciones representan el esfuerzo iterativo global del algoritmo, incluyendo todo el procesamiento invertido en evaluar y descartar rutas que resultaron en bloqueos.

**c. ¿Dónde aparece la "poda" en este código, aunque no haya una estructura formal con ese nombre?**
El mecanismo de poda se activa en el bloque condicional `while (... && conflictsWithAny(...))`. Al identificar un conflicto temprano en una fila superior, el algoritmo aborta la evaluación de todo el subárbol combinatorio de las filas inferiores, avanzando lateralmente (`++q.y`) y omitiendo millones de operaciones innecesarias.

### Experimento 5: Comportamiento ante escenarios de Laberinto

### Configuración de la prueba:
Se inyectaron representaciones personalizadas en el vector `ods::Maze maze({...})` modificando los obstáculos (`#`) y los pasillos (`.`) para observar el comportamiento dinámico de la pila.

### Escenario 1: Navegación lineal
**Matriz inyectada:**
```text
"#####"
"#...#"
"###.#"
"#...#"
"#####"
```
- **Coordenadas:** (1, 1) a (3, 1).
- **Longitud:** 5 celdas.
- **Retroceso:** Nulo.
- **Análisis:** El algoritmo avanza integrando coordenadas en la pila sin experimentar bloqueos. Evaluado como el caso óptimo O(1) en retrocesos.

### Escenario 2: Bloqueo ineludible
**Matriz inyectada:**
```text
"#####"
"#...#"
"###.#"
"###.#"
"#####"
```
- **Coordenadas:** (1, 1) a (3, 1) (Meta cubierta por muro).
- **Longitud:** 0.
- **Retroceso:** Extremo.
- **Análisis:** El explorador agota el pasillo hábil y, al no identificar alternativas viables, inicia una secuencia repetida de `pop()` marcando todo el trayecto como `BACKTRACKED`. Culmina de forma controlada con una pila vacía, demostrando robustez frente a errores de desbordamiento en mapas no solucionables.

### Escenario 3: Rutas alternas y rectificación
**Matriz inyectada:**
```text
"#######"
"#.....#"
"#.###.#"
"#...#.#"
"###.#.#"
"#...#.#"
"#######"
```
- **Coordenadas:** (1, 1) a (5, 1).
- **Longitud:** 9 celdas.
- **Retroceso:** Parcial.
- **Análisis:** El algoritmo se introduce en el pasillo derecho hasta la coordenada (5, 5). Al confirmar la obstrucción, ejecuta el retroceso reduciendo la pila, descartando el ramal ineficaz y orientándose posteriormente hacia la ruta óptima en la columna izquierda. Demuestra el mecanismo fundamental de auto-corrección espacial.

## Bloque 7 - Simulación bancaria y experimentación con colas

### Material Revisado:
- `Semana4/include/Queue.h`
- `Semana4/include/BankSimulation.h`
- `Semana4/demos/demo_bank.cpp`
- `Semana4/pruebas_publicas/test_public_week4.cpp`
- `Semana4/pruebas_internas/test_internal_week4.cpp`

### 1. ¿Qué representa cada `Queue<Customer>` dentro del vector `windows`?
Representa lógicamente a una unidad operativa junto a su respectiva estructura de espera, agrupando a los clientes que serán atendidos de forma secuencial por dicho operario.

### 2. ¿Qué criterio usa `bestWindow` y qué decisión toma cuando hay empate?
Aplica el criterio de mínima ocupación evaluando la métrica `size()`. En caso de que múltiples colas presenten el mismo tamaño, el operador condicional de estricta minoría (`<`) asigna al cliente al índice más bajo que haya igualado el valor mínimo en memoria.

### 3. ¿Qué significa que la simulación use una semilla (`seed`)?
Establece una base fija para la función de generación pseudoaleatoria. Esto asegura un comportamiento determinista: los eventos (frecuencia de clientes y tiempos de atención) se replicarán de manera idéntica en ejecuciones sucesivas, permitiendo la trazabilidad y la depuración de la lógica.

### 4. ¿Qué relación debe cumplirse entre `totalArrivals` y `totalServed`, y por qué?
Se establece que `totalArrivals >= totalServed`. Es físicamente imposible procesar un número mayor de salidas que de entradas generadas. El diferencial entre ambas variables cuantifica el volumen de elementos que permanecen en el sistema al concluir la simulación.

### 5. ¿Qué representa la línea de tiempo (*timeline*) en el resultado?
Constituye un registro de trazabilidad o volcado de memoria. Proporciona instantes discretos del estado de ocupación del sistema, detallando las asignaciones a ventanillas y el tiempo de trámite restante por entidad en unidades precisas (`ticks`).

### 6. ¿Por qué esta aplicación necesita colas y no pilas?
Por la necesidad estructural de garantizar un servicio equitativo en función del tiempo de llegada. El orden FIFO (primer ingreso, primera atención) es imperativo; el uso de estructuras LIFO invalidaría la representación lógica, priorizando siempre al último evento registrado.

### 7. ¿Qué simplificación del mundo real introduce este simulador?
Modeliza un sistema altamente estático e idealizado: asume una tasa nula de deserción, tiempos de trámite invariables desde el inicio, e imposibilidad técnica de reasignación entre colas (los clientes no cambian de ventanilla).

### 8. ¿Qué cambiaría si la política ya no fuera "cola más corta" sino otra?
Implicaría una reestructuración de clases. Adoptar, por ejemplo, una política de "fila única global" requeriría desestimar el vector de colas individuales, suprimiendo la lógica en `bestWindow` a favor de una estructura centralizada que derive entidades según la disponibilidad binaria (`free`) de los agentes operativos.

### Experimento 6: Evaluación de Estresores en Simulación

### Configuración de la prueba:
Se modificaron directamente los parámetros pasados a `ods::simulate(nWin, servTime, seed)` en el archivo ejecutable para analizar el impacto estructural de las colas frente a alteraciones en la carga y tiempo disponible.

### Tabla de Resultados: Análisis del Simulador

| Agentes | T. Total | Semilla | Llegadas | Salidas | Ocupación Residual | Deducciones Observadas |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| **3** | 20 | 100 | 15 | 0 | [5, 5, 5] | Distribución equitativa comprobada mediante algoritmo `bestWindow`. |
| **3** | 20 | 100 | 15 | 0 | [5, 5, 5] | Comprobación de determinismo: la salida se mantiene invariable ante la misma semilla. |
| **3** | 20 | 999 | 14 | 1 | [5, 4, 4] | Variación heurística. Alterar la semilla reconfigura los tiempos individuales de los clientes. |
| **1** | 20 | 100 | 11 | 0 | [11] | Prueba de cuello de botella: centralización de todo el flujo en una única cola degenerando el rendimiento. |
| **5** | 100 | 123 | 83 | 4 | [16, 16, 16, 16, 15] | Evaluación de estrés a largo plazo. La tasa probabilística de ingresos supera drásticamente la capacidad de despacho asíncrona. |

### Cuestionario Analítico:

**1. ¿Qué parámetro parece influir más en la congestión observable?**
El factor predominante es la duración general (`servTime`). El diseño matemático expone que la probabilidad de generación de nuevos clientes supera ampliamente la frecuencia de resolución de trámites (que pueden abarcar hasta 98 unidades de tiempo), provocando un desbalance de crecimiento lineal severo.

**2. ¿Qué cambia cuando repites exactamente la misma semilla?**
No se registran variaciones. Se demuestra la naturaleza predecible y algorítmica de los motores "aleatorios" en el software, siendo una propiedad indispensable para los tests de integración y la validación de cambios en el código.

**3. ¿Qué cambia cuando mantienes `nWin` y `servTime`, pero alteras la semilla?**
Se modifican las variables estocásticas a nivel micro (ligeros cambios en ingresos y demoras individuales). No obstante, el comportamiento de congestión macroscópica se mantiene estable, evidenciando que el cuello de botella responde a deficiencias estructurales del diseño del modelo y no a la aleatoriedad.

**4. ¿Qué evidencia usarías para defender que la cola más corta es una política razonable, aunque no necesariamente óptima?**
- **Sustento de razonabilidad:** Los reportes de ocupación residual final (ej. `[16, 16, 16, 16, 15]`) demuestran que el algoritmo previene de manera muy eficaz los picos aislados de carga, distribuyendo el peso operativo de forma equitativa.
- **Sustento de no optimización:** La evaluación mediante `size()` resulta ser un criterio parcial. Un algoritmo óptimo debería computar el acumulado del tiempo real de trámite de cada fila en lugar de únicamente la cantidad absoluta de clientes para evitar envíos a colas lentas.

## Bloque 8 - Cierre comparativo

A lo largo del estudio de las estructuras, se evidencia una evolución arquitectónica: las estructuras dejan de emplearse como contenedores pasivos de memoria y adoptan el rol de núcleos lógicos orientadores de flujos y procesamiento.

### Análisis del modelo de representación

* **Sobre LIFO y FIFO:** Su utilidad trasciende el mero almacenaje. Se implementan como paradigmas algorítmicos. La pila se convierte en un mecanismo eficaz de retención transitoria o "aplazamiento seguro", mientras que la cola se asume como el controlador oficial del orden temporal estricto para procesos no interruptibles.

* **Sobre recursión frente a estructura explícita:** Instanciar manualmente la memoria permite transferir el control lógico desde la arquitectura del sistema operativo hacia el desarrollador. Se previene la inestabilidad de la memoria, traduciendo procesos de alta profundidad (arborescencias) en ciclos iterativos que operan en zonas más amplias de memoria dinámica.

* **Sobre evaluación de expresiones:** La estructura base muta hacia un procesador de reglas sintácticas. Gestiona de forma concurrente el texto plano y las normativas matemáticas, actuando como un intermediario capaz de ordenar ejecuciones aritméticas complejas en un solo recorrido de la matriz de datos.

* **Sobre backtracking:** La estructura provee el mecanismo esencial de exploración probabilística. Establece una topología de "deshacer" en tiempo `O(1)`, asegurando viabilidad en tareas donde el árbol de decisión computa miles de ramificaciones erróneas, evitando bucles repetitivos y fatales.

* **Sobre simulación:** El modelado del software desplaza el cálculo de algoritmos puros para abstraer el flujo secuencial del mundo exterior. Facilita la recreación teórica del tiempo continuo en escenarios experimentales sin las variables entrópicas del azar real.

* **Sobre la correctitud experimental:** El procedimiento de evaluación migra de comprobar el comportamiento del método individual hacia certificar la resiliencia integral. Los experimentos aplican cargas asimétricas o inyectan fallos provocados para verificar formalmente que los invariantes persisten sin desbordamientos matemáticos ni pérdidas de conectividad entre los datos.

### Comparativa de Aplicaciones (Semana 4)

| Aplicación | Uso de la Estructura | Naturaleza del Problema |
| :--- | :--- | :--- |
| **Conversión de base** | Pila como inversor | Transformación simple de secuencias numéricas. |
| **Paréntesis** | Pila como validador | Análisis de consistencia sintáctica en textos. |
| **N-Reinas / Laberinto** | Pila como explorador | Búsqueda con retroceso. Las Reinas calculan ataques matemáticos, el Laberinto navega una grilla física. |
| **Simulación Bancaria** | Cola como gestor | Administración de un flujo temporal de eventos que no pueden retroceder. |
