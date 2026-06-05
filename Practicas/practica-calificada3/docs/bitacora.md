# Bitácora de Desarrollo - Práctica Calificada 3
## Problema: AtCoder ABC170 E - Smart Infants

* **Día 1 (04/06/2026):** Lectura comprensiva del problema y rúbrica de evaluación. Creación de la estructura de directorios limpia (include, src, demos, tests, etc.). Configuración del archivo `.gitignore` estricto para evitar subir ejecutables y binarios generados por CMake.

* **Día 2 (05/06/2026):** Importación de la clase `PQ_ComplHeap` desde la Actividad de la Semana 6 hacia la carpeta `include` del proyecto. Ademas se incluyo los otros archivos relacionados con esto para evitar errores o rupturas del codigo.
 Creación de la clase base `SmartInfants` en C++ estableciendo arreglos paralelos para control de fuerza y ubicación de infantes en tiempo $O(1)$. Configuración de un `std::vector` de Heaps para representar las 200,000 guarderías posibles. Configuración inicial del `CMakeLists.txt` y lectura de datos en `src/main.cpp`.