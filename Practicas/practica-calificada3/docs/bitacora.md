# Bitácora de Desarrollo - Práctica Calificada 3
## Problema: AtCoder ABC170 E - Smart Infants

 * **Día 1 (04/06/2026):** Lectura comprensiva del problema y rúbrica de evaluación. Creación de la estructura de directorios limpia (include, src, demos, tests, etc.). Configuración del archivo `.gitignore` estricto para evitar subir ejecutables y binarios generados por CMake.

 * **Día 2 (05/06/2026):** Importación de la clase `PQ_ComplHeap` desde la Actividad de la Semana 6 hacia la carpeta `include` del proyecto. Ademas se incluyo los otros archivos relacionados con esto para evitar errores o rupturas del codigo.
 Creación de la clase base `SmartInfants` en C++ estableciendo arreglos paralelos para control de fuerza y ubicación de infantes en tiempo $O(1)$. Configuración de un `std::vector` de Heaps para representar las 200,000 guarderías posibles. Configuración inicial del `CMakeLists.txt` y lectura de datos en `src/main.cpp`.

 * **Día 3 (06/06/2026):** Modificación del Heap para almacenar `std::pair<int, int>` permitiendo vincular con el ID del infante. Implementación de la función `limpiar_guarderia` utilizando el concepto de **Lazy Deletion** para depurar en $O(\log N)$ las cimas de los Heaps que contienen niños ya transferidos. 
 Integración de `std::multiset` como estructura secundaria auxiliar para mantener el mínimo global de los máximos en tiempo logarítmico. Cierre del ciclo de procesamiento en `main.cpp`.

 * **Día 4 (07/06/2026):** Implementación de las pruebas automatizadas en `test_smart_infants.cpp`. Cubriendo los 6 escenarios exigidos por la rúbrica: 
    1. Caso mínimo garantizado.
    2. Comportamiento ante guarderías vacías (colapso de Heaps).
    3. Manejo estable de infantes con fuerza duplicada.
    4. Simulación extrema de verificación manual.
    5. Benchmark de rendimiento validando la optimización logarítmica frente a una solución ingenua en tiempo $O(N)$.
    6. Verificación explícita del invariante principal (Lazy Deletion para la limpieza de nodos basura).
  
  Adicionalmente, se actualizó el archivo `CMakeLists.txt` para integrar el ecosistema CTest, y se documentaron los resultados en los registros de evidencia textual (`tests_pc3.txt`, `casos_borde.txt` y `ejecucion_pc3.txt`). 
  Finalmente, se creó el archivo auxiliar `input.txt` para permitir la inyección rápida y automatizada del caso de prueba de AtCoder en la terminal.

  * **Día 5 (08/06/2026):** Redacción de la documentación técnica completa. Se elaboró el archivo `README.md` cumpliendo con la plantilla exigida por la rúbrica. Se documentaron las justificaciones de complejidad, diseño algorítmico y control de redundancias mediante Lazy Deletion en `respuestas_obligatorias.md`. 
  Finalmente, se desarrolló e implementó `benchmark_pc3.cpp` para validar el rendimiento empírico de $O(\log N)$ y registrar oficialmente el quinto día de trabajo en el historial del repositorio.

  * **Día 6 (09/06/2026):** Se desarrollo la demostración interactiva en `demos/demo_smart_infants.cpp` para visualizar el comportamiento del *Lazy Deletion* y estructurar el caso de vaciado de grupo. 
  Se optimizó el ecosistema de construcción en `CMakeLists.txt` unificando el main, tests, demo y benchmark (este último con bandera de optimización `-O3`). 
  En el apartado de documentación, se actualizaron las respuestas_obligatorias.md mejorando la explicación de las 3 preguntas específicas del problema AtCoder ABC170 E.
  Además, se concluyó la Actividad 6 (incluyendo la instrumentación del Treap, pruebas de invariantes y defensa escrita) y se aplicaron correcciones menores de formato visual y adición de autoevaluaciones en las Actividades 4 y 5.