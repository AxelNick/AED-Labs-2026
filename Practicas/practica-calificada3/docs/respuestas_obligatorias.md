# Respuestas Obligatorias - PC3 (ABC170 E - Smart Infants)

### Preguntas Específicas del Problema 24

1. **¿Qué guarda cada grupo?**
   Guarda un Max-Heap que contiene objetos o pares con la fuerza (rate) y el ID de cada infante asignado a esa guardería, permitiendo consultar al infante más fuerte del grupo en $O(1)$.

2. **¿Qué guarda la estructura global?**
    Guarda un Min-Heap que recolecta el valor máximo actual de cada guardería activa. Su cima representa la respuesta a la consulta: la guardería cuyo máximo es el menor de todos.

3. **¿Qué se actualiza cuando un niño cambia de grupo?**
   Se actualiza un arreglo interno que rastrea la ubicación real del niño. Luego, el niño se inserta en el Max-Heap del nuevo grupo. En el grupo antiguo, se aplica *Lazy Deletion* (se marca lógicamente como ausente sin borrar el nodo del Heap). Finalmente, se insertan los nuevos máximos de ambas guarderías en el Min-Heap global.


### Preguntas Comunes Obligatorias

1. **¿Cuál es el problema exacto asignado?**
   Problema *AtCoder ABC170 E - Smart Infants*

2. **¿Qué recibe la entrada y qué produce la salida?**
   La entrada consiste en $N$ infantes, definidos por su nivel inicial (rate) y la guardería a la que pertenecen, seguidos de $Q$ consultas de transferencia. 
   La salida requerida es el mínimo de los valores máximos actuales de cada guardería tras ejecutar cada transferencia.

3. **¿Cuál es la restricción que vuelve insuficiente una solución ingenua?**
   Los parámetros $N$ y $Q$ pueden alcanzar valores de hasta $2\times 10^5$. Una complejidad algorítmica cuadrática excedería el límite de tiempo de ejecución.

4. **¿Cuál sería la solución ingenua y cuál es su complejidad?**
   Consistiría en actualizar el estado en arreglos unidimensionales y recalcular iterativamente el máximo de cada guardería, seguido del cálculo del mínimo global. Esta aproximación posee una complejidad temporal de $O(N\times Q)$, resultando inviable para los límites del problema.

5. **¿Qué estructura de datos elegiste?**
   Se optó por una arquitectura basada COLAS DE PRIORIDAD(*Heaps*). Se emplea un Max-Heap independiente por cada guardería y un Min-Heap global para administrar a los representantes máximos, sincronizando la información mediante la técnica de eliminación perezosa (*Lazy Deletion*).

6. **¿Qué estructura de la librería `cc232` se parece más?**
   Deriva conceptualmente de la estructura `PQ_ComplHeap` correspondiente a la Semana 6, la cual ha sido adaptada metodológicamente para soportar la validación y purga diferida de su elemento tope.

7. **¿Qué operación domina el tiempo?**
   El tiempo de ejecución está dominado por las operaciones de inserción y el proceso de purga de registros obsoletos en los Heaps, presentando un costo asintótico de $O(\log N)$ por cada operación.

8. **¿Qué invariante mantiene tu estructura?**
   El invariante estructural garantiza que el elemento ubicado en la cima de cualquier Heap corresponda estrictamente a un registro vigente. Todo dato obsoleto que alcance la cima es purgado antes de procesar cualquier consulta.

9. **¿Dónde se actualiza ese invariante en el código?**
   Se restablece en los métodos de lectura, como `getMinGlobal()` o las funciones de limpieza interna. Se utilizan bucles `while` que ejecutan la operación `pop()` consecutivamente hasta que los datos de la cima coinciden de forma exacta con el registro central de ubicaciones del sistema.

10. **¿Qué caso borde puede romper una solución superficial?**
    El escenario donde una guardería transita a un estado completamente vacío. La lógica del sistema debe garantizar que el Min-Heap global no procese ni retenga representaciones de guarderías sin población activa.

11. **¿Cómo manejas duplicados, empates o elementos obsoletos?**
    Los duplicados físicos de un mismo infante (generados en el Heap por transferencias sucesivas) y los elementos obsoletos se gestionan conjuntamente mediante un arreglo de control de estado (`ubicacion_actual[id]`). Si la guardería registrada en el nodo del Heap difiere de este registro central, el duplicado se clasifica como inválido y se descarta mediante *Lazy Deletion*. 
    Por otro lado, las colisiones lógicas (empates de fuerza entre diferentes infantes) se resuelven de forma natural y sin conflictos por las propiedades estructurales inherentes del Max-Heap.

12. **¿Cuál es la complejidad temporal por operación?**
    Presenta un costo de $O(\log N)$ en tiempo amortizado por cada evento de transferencia.

13. **¿Cuál es la complejidad total?**
    La complejidad asintótica total es de $O((N+Q)\log N)$, englobando la construcción inicial y la resolución secuencial de consultas.

14. **¿Cuál es la complejidad espacial?**
    La cota de memoria es $O(N + Q)$ en el peor de los escenarios, determinado por la acumulación de registros históricos sin purgar dentro de los arreglos subyacentes de los Heaps.

15. **¿Qué parte del código sería más fácil de romper?**
    La sincronización del estado. La omisión en la actualización del arreglo de control previo a la inserción en el Heap comprometería la técnica de *Lazy Deletion*, derivando en la emisión de máximos lógicamente inválidos.

16. **¿Qué alternativa de estructura existe y qué perderías con ella?**
    Emplear contenedores auto-balanceados como `std::multiset` (basados en Árboles Rojo-Negro). Si lo usaramos implicaría sacrificar la localidad de referencia en caché y la eficiencia operacional bruta inherente a los Heaps construidos sobre arreglos contiguos.

17. **¿Qué prueba propia escribiste?**
    Se implementaron pruebas unitarias integradas mediante CTest en `test_smart_infants.cpp`. Estas incluyen pruebas de validación estructural, destacando escenarios de estrés para evaluar el vaciado de guarderías y la correcta estabilización matemática de los Heaps.

18. **¿Qué cambiaste durante el bloque sin cortes?**
    Se implementó un diagnóstico dentro de la función principal de transferencia. Esta modificación introduce un monitoreo de estado que emite una alerta por consola en el instante preciso en que una guardería queda completamente vacía (población igual a cero), validando así el dominio del código en vivo exigido para la sustentación.

19. **¿Cómo sabes que el cambio no rompió la solución?**
    Su validez estructural se garantiza de forma empírica mediante la ejecución de los 6 escenarios de pruebas automatizadas en CTest. La obtención de un 100% de éxito confirma la preservación del invariante y la ausencia de regresiones.

20. **¿Qué demuestra que no es una solución de caja negra?**
    Queda evidenciado mediante la implementación del algoritmo del *Lazy Deletion*. Una solución de caja negra dependería de abstracciones del lenguaje (como el método `.erase()` en contenedores estándar), mientras que esta solucion diseña y administra manualmente el ciclo de vida y la expiración asíncrona de los nodos para maximizar la optimización.