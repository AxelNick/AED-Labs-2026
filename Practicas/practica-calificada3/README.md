### PC3 - CC232

#### Estudiante
- Nombre: Axel Alberto Reyes Baldeón
- Código: [20200485B]
- Problema asignado: AtCoder ABC170 E - Smart Infants
- Enlace oficial: https://atcoder.jp/contests/abc170/tasks/abc170_e

#### Referencia oficial
- CSV oficial:
  https://github.com/kapumota/CC-232/blob/main/Practicas/Practica3_CC232/Problemas-Evaluacion3.csv

#### Relación con Semanas 4-6
- Semana principal: Semana 6
- Estructura usada: Conjuntos por grupo y estructura global de máximos usando Priority Queues (Heaps) con Lazy Deletion
- Estructura de la librería `cc232` relacionada: `PQ_ComplHeap` adaptado para permitir eliminación diferida (Lazy Deletion) 

#### Resumen de la solución
El problema requiere mantener el control de miles de infantes que cambian constantemente de guardería, y consultar rapidamente cuál es el "mínimo de los máximos" entre todas las guarderías. 
En lugar de recalcular desde cero, la solución utiliza un Max-Heap para cada guardería (para conocer a su niño más fuerte en tiempo constante) y un Min-Heap global que almacena los representantes máximos de cada grupo activo.Como aclaracion cuando digo mas "fuerte" me refiero a cuál es el infante con el puntaje más alto dentro de una guardería específica.
Para las transferencias, se emplea "Lazy Deletion", dejando registros obsoletos en los Heaps y limpiándolos solo cuando alcanzan la cima.

#### Invariante principal
El invariante lógico mantenido es que el elemento en la cima de cada Heap (tanto locales como el global) debe ser siempre un elemento "vivo" y válido. Si al intentar consultar la cima se detecta que el registro ya no coincide con la ubicación actual del infante, se ejecuta la limpieza (Lazy Deletion) hasta que la nueva cima sea correcta.

#### Complejidad
- Tiempo por operación: $O(\log N)$ para transferencias y limpieza de Heaps
- Tiempo total: $O((N+Q)\log N)$
- Espacio: $O(N+Q)$ debido a la acumulación de registros en los Heaps antes de su limpieza diferida

#### Archivos relevantes
- `include/`: Contiene `SmartInfants.h` con la lógica central de Heaps y guarderías.
- `src/`: Contiene `main.cpp` (sin formato para el juez de AtCoder).
- `tests/`: Contiene las pruebas de CTest (`test_smart_infants.cpp`).
- `benchmark/`: Benchmark de rendimiento comparativo.
- `docs/respuestas_obligatorias.md`: Cuestionario técnico exigido.
- `docs/bitacora.md`: Historial de desarrollo diario.
- `resultados/`: Evidencias de compilación y ejecución en consola.

#### Limpieza del repositorio
Se ha verificado mediante `.gitignore` y comandos de consola que no se suban binarios, carpetas `build/`, ni archivos `.exe`.
```bash
git ls-files | grep -E "(^build/|cmake-build|\.exe$|\.out$|\.o$|\.obj$|CMakeCache.txt|CMakeFiles|__pycache__)"
```
Evidencia al ejecutar el comando:
```bash
AXEL@DESKTOP-70IITE7 UCRT64 /c/Users/AXEL/OneDrive/Escritorio/uni/2026-1/AED/Repositorio/Personal/CC232-2026/Practicas/practica-calificada3
$ git ls-files | grep -E "(^build/|cmake-build|\.exe$|\.out$|\.o$|\.obj$|CMakeCache.txt|CMakeFiles|__pycache__)"
```
*(No se obtuvieron resultados, confirmando la limpieza del repositorio)*

#### Compilación
```bash
cmake -S . -B build
cmake --build build
```

#### Ejecución
```bash
./build/main.exe < input.txt
```

#### Pruebas

He programado 6 aserciones críticas en `test_smart_infants.cpp`. A continuación, el detalle exigido:

##### 1. Caso mínimo garantizado
* **Entrada usada:** 1 infante (Fuerza 10, Guardería 1), movido a Guardería 2.
* **Salida esperada:** Mínimo global 10.
* **Salida obtenida:** 10.
* **Qué aspecto valida:** Correctitud básica y que el sistema no colapse con $N=1$.

##### 2. Caso con estructura vacía / frontera
* **Entrada usada:** 2 infantes en Guardería 1. Ambos son movidos a la Guardería 2.
* **Salida esperada:** Guardería 1 reporta fuerza -1 (vacía).
* **Salida obtenida:** -1.
* **Qué aspecto valida:** Demuestra que al vaciar un grupo, el sistema lo detecta y lo retira del multiset global, superando el reto de "ausencia de respuesta".

##### 3. Manejo de duplicados o empates
* **Entrada usada:** Dos infantes con fuerza exacta de 100 en la Guardería 1. Se transfiere a uno de ellos.
* **Salida esperada:** El máximo de la Guardería 1 sigue siendo 100.
* **Salida obtenida:** 100.
* **Qué aspecto valida:** Estabilidad matemática ante colisiones de fuerza.

##### 4. Caso extremo pequeño verificable manualmente
* **Entrada usada:** 3 infantes uniéndose progresivamente a una sola guardería.
* **Salida esperada:** El sistema descarta los grupos anteriores y actualiza el máximo en la nueva guardería paso a paso.
* **Salida obtenida:** `Test Passed`.
* **Qué aspecto valida:** Simulación progresiva manual para comprobar el agrupamiento correcto.

##### 5. Comparación contra solución ingenua (Fuerza Bruta)
* **Entrada usada:** Arreglos aleatorios pequeños iterados.
* **Salida esperada:** Resultado idéntico entre cálculo ingenuo iterativo y estructura de Heaps.
* **Salida obtenida:** `Test Passed`.
* **Qué aspecto valida:** Exactitud matemática absoluta (cumple el Reto Transversal de comparar versiones).

##### 6. Prueba específica del invariante (Lazy Deletion)
* **Entrada usada:** Infante fuerte (rate 50) y débil (rate 20) en Guardería 1. El infante fuerte es transferido a Guardería 2.
* **Salida esperada:** El nuevo máximo de la Guardería 1 es 20 (el 50 obsoleto es ignorado).
* **Salida obtenida:** 20.
* **Qué aspecto valida:** Verifica explícitamente que el Lazy Deletion limpia al "fantasma" sin alterar el estado del sistema.


#### Evidencia Git
Comandos ejecutados para registrar el proceso:
```bash
git status
git log --date=short --pretty=format:"%ad - %h - %an - %s"
git log --date=short --pretty=format:"%ad" | sort | uniq -c
git log --graph --oneline --decorate --all
git log --date=short --name-status --pretty=format:"%ad - %h - %s" -- Semana4 Semana5 Semana6 Practicas practica-calificada3
git log --date=short --stat --pretty=format:"%ad - %h - %s"
```
El historial demuestra que en días distintos de trabajo (desde la configuración inicial hasta el blindaje de pruebas y respuestas teóricas).

#### Preguntas obligatorias
Respondidas en detalle y documentadas en docs/respuestas_obligatorias.md.

#### Bitácora obligatoria
Registrada en docs/bitacora.md.

#### Enlaces de la Sustentación
- **Video de sustentación:** [https://drive.google.com/file/d/1mvt9otofLnJ5ByHUVTY6B-7ShvQMmCXZ/view?usp=sharing]
- **Diapositivas (Canva):** [https://canva.link/6w5xp9tvcjwkgq1]

#### Declaración de autoría
Declaro que entiendo el código entregado, que puedo explicarlo, compilarlo, ejecutarlo y modificarlo sin ayuda externa durante la grabación. También declaro que el repositorio entregado corresponde al trabajo mostrado en el video y que no contiene builds, ejecutables ni archivos generados usados para aparentar funcionamiento.