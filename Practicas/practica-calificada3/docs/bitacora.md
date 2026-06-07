# Bitácora de Desarrollo - Práctica Calificada 3
## Problema: AtCoder ABC170 E - Smart Infants

* **Día 1 (04/06/2026):** Lectura comprensiva del problema y rúbrica de evaluación. Creación de la estructura de directorios limpia (include, src, demos, tests, etc.). Configuración del archivo `.gitignore` estricto para evitar subir ejecutables y binarios generados por CMake.

* **Día 2 (05/06/2026):** Importación de la clase `PQ_ComplHeap` desde la Actividad de la Semana 6 hacia la carpeta `include` del proyecto. Ademas se incluyo los otros archivos relacionados con esto para evitar errores o rupturas del codigo.
 Creación de la clase base `SmartInfants` en C++ estableciendo arreglos paralelos para control de fuerza y ubicación de infantes en tiempo $O(1)$. Configuración de un `std::vector` de Heaps para representar las 200,000 guarderías posibles. Configuración inicial del `CMakeLists.txt` y lectura de datos en `src/main.cpp`.

 * **Día 3 (06/06/2026):** Modificación del Heap para almacenar `std::pair<int, int>` permitiendo vincular con el ID del infante. Implementación de la función `limpiar_guarderia` utilizando el concepto de **Lazy Deletion** para depurar en $O(\log N)$ las cimas de los Heaps que contienen niños ya transferidos. 
 Integración de `std::multiset` como estructura secundaria auxiliar para mantener el mínimo global de los máximos en tiempo logarítmico. Cierre del ciclo de procesamiento en `main.cpp`.