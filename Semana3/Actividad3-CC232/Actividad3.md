# Actividad 3 - Semana 3

**Estudiante:**
Axel Alberto Reyes Baldeón

## Bloque 0 - Instalación y preparación

### Tareas de Configuración:
- [X] Dejé lista mi carpeta de trabajo.
- [X] Verifiqué mi acceso a:
    - Directorio `Semana3`
    - Lecturas correspondientes.
    - Archivo de entrega.
- [X] Creé el archivo `Actividad3.md` en la carpeta correcta.
- [X] Anoté mi nombre como único integrante.

### Verificación de Entorno (Semana 3)

**Estado de Compilación y Ejecución en mi máquina:**
* **Demo ejecutada localmente:** `demo_capitulo3_panorama.cpp`
```text
$ ./sem3_demo_capitulo3_panorama
Semana 3 cargada correctamente
SLList size = 3, peek = 0
DLList: 10 20 30 
SEList: 8 6 7 
LinkedStack top = 200
LinkedQueue front = 11
LinkedDeque front/back = 5/9
ArrayDeque first/last = 4/6
```

* **Prueba pública ejecutada desde mi terminal:** ```text
$ ctest
Test project C:/Users/AXEL/OneDrive/Escritorio/uni/2026-1/Algoritmos y estructura de datos/Repositorio/Personal/CC-232_Personal-2026--main/Libreria_cc232/Semana3/build
    Start 1: semana3_public
1/7 Test #1: semana3_public ...................   Passed    0.02 sec
    Start 2: semana3_public_extras
2/7 Test #2: semana3_public_extras ............   Passed    0.02 sec
    Start 3: semana3_internal
3/7 Test #3: semana3_internal .................   Passed    0.02 sec
    Start 4: semana3_internal_extras
4/7 Test #4: semana3_internal_extras ..........   Passed    0.02 sec
    Start 5: semana3_stress_selist
5/7 Test #5: semana3_stress_selist ............   Passed    0.02 sec
    Start 6: semana3_public_linked_adapters
6/7 Test #6: semana3_public_linked_adapters ...   Passed    0.02 sec
    Start 7: semana3_public_compare
7/7 Test #7: semana3_public_compare ...........   Passed    0.02 sec

100% tests passed, 0 tests failed out of 7

Total Test time (real) =   0.13 sec
```

> *Nota: Confirmé que mi entorno de desarrollo está correctamente configurado para trabajar con las estructuras de la Semana 3.*

## Bloque 1 - Núcleo conceptual de la semana

### Material Revisado:
- `Semana3/README.md`
- `Parte3-Deng.pdf`
- `Parte3-Morin.pdf`
- `Semana3/include/SLList.h`
- `Semana3/include/DLList.h`
- `Semana3/include/SEList.h`
- `Semana3/include/DengList.h`
- `Semana3/include/MorinDengBridge.h`

### 1. ¿Qué cambia cuando una estructura pasa de almacenamiento contiguo a almacenamiento dinámico?

Entendí que cambia el mecanismo que define el orden de la secuencia. 
En el modelo contiguo (arreglos), la sucesión de datos está dada por la adyacencia física en la memoria, lo que permite calcular aritméticamente las posiciones. 
En el modelo dinámico (listas), la contigüidad física desaparece; el orden lo mantengo de manera abstracta mediante referencias (punteros) que enlazan nodos distribuidos por cualquier lado de la RAM.

### 2. ¿Qué diferencia hay entre acceso por rango y acceso por posición o enlace?

- Noté que el acceso por rango utiliza un índice numérico para denotar la distancia desde el inicio, obligando a las estructuras dinámicas a realizar una iteración secuencial lenta. 
- El acceso por posición o enlace utiliza la dirección de memoria exacta del nodo, permitiéndome intervenir la estructura de manera directa e inmediata, en tiempo constante O(1).

### 3. ¿Por qué una lista enlazada mejora inserciones y eliminaciones locales, pero empeora el acceso por índice?

Mejora las actualizaciones locales porque, al poseer la referencia exacta, la inserción o eliminación se reduce a reasignar un par de punteros adyacentes en O(1), sin que yo tenga que desplazar el resto de datos. Empeora el acceso por índice porque al no haber contigüidad física no puedo sumar posiciones de memoria, obligándome a recorrer los enlaces iterativamente en O(n) para llegar al elemento deseado.

### 4. ¿Por qué SLList implementa bien operaciones de Stack y Queue?

Porque vi que la estructura mantiene referencias explícitas hacia sus dos extremos (`head` y `tail`). Esto me permite que las inserciones y eliminaciones por la cabecera (operaciones de Pila) y las inserciones por la cola (operaciones de Cola) se realicen resolviendo un número constante de punteros en tiempo O(1).

### 5. ¿Por qué SLList no implementa naturalmente todas las operaciones de un Deque con el mismo costo?

Un Deque exige máxima eficiencia de inserción y eliminación en ambos extremos. Aunque mi `SLList` inserta en la cola rapidísimo, si quiero eliminar el último elemento necesito actualizar el puntero `tail` hacia el penúltimo nodo. Al poseer únicamente enlaces que apuntan hacia adelante, localizar ese nodo previo me exige iterar toda la lista desde la cabecera, degradando el costo a O(n).

### 6. ¿Qué aporta el nodo centinela dummy en DLList?

Comprendí que aporta uniformidad estructural al convertir la lista en una topología circular. 
Al garantizar que todos los nodos reales posean siempre un predecesor y un sucesor definidos (nunca apuntan a nulo), me quita la necesidad de programar un montón de condicionales "if" para los casos frontera (como insertar en una lista vacía o modificar los extremos).

### 7. ¿Por qué DLList permite justificar get(i), set(i,x), add(i,x) y remove(i) con costo O(1 + min(i, n-i))?

Gracias al doble enlace y a que conozco estáticamente el tamaño (n), el algoritmo de búsqueda decide de forma inteligente la ruta más corta: si el índice que busco está en la primera mitad, itero hacia adelante desde la cabeza; si está en la segunda mitad, retrocedo desde la cola. Así me aseguro de que el recorrido nunca supere la mitad de la estructura.

### 8. ¿Cuál es la idea espacial central de SEList?

Comprendí que su propósito es mitigar el enorme desperdicio de memoria (*overhead*) de las listas enlazadas puras, donde cada elemento requiere memoria extra para los punteros. Lo resuelve agrupando múltiples elementos dentro de un bloque continuo por cada nodo. Así, el costo en bytes de los punteros se "amortiza" al compartirse entre todos los datos de ese bloque.

### 9. ¿Por qué SEList reutiliza una BDeque basada en ArrayDeque?

Al operar con bloques de elementos en lugar de datos individuales, vi que la estructura necesita reacomodar internamente sus componentes rápido para mantener el equilibrio. Utilizar un `ArrayDeque` (un arreglo circular dinámico) le da a cada nodo la eficiencia necesaria para absorber estos pequeños movimientos locales (inserciones o eliminaciones internas) sin sobrecargar el procesador.

### 10. ¿Qué papel cumple DengList dentro de esta semana y por qué no reemplaza a las estructuras de Morin?

Identifiqué que `DengList` actúa como una capa de abstracción (un *wrapper* o adaptador) diseñada puramente para darme las operaciones algorítmicas de Deng (como ordenar y quitar duplicados). No reemplaza a las estructuras de Morin (`SLList`, `DLList`) porque las de Morin son el motor real de bajo nivel que gestiona eficientemente mi memoria RAM.

## Bloque 2 - Demostración y trazado guiado

### Material Revisado:
- `Semana3/demos/demo_sllist.cpp`
- `Semana3/demos/demo_dllist.cpp`
- `Semana3/demos/demo_selist.cpp`
- `Semana3/demos/demo_deng_list.cpp`
- `Semana3/demos/demo_morin_deng_bridge.cpp`
- `Semana3/demos/demo_capitulo3_panorama.cpp`
- `Semana3/demos/demo_min_structures.cpp`
- `Semana3/demos/demo_xor_list.cpp`
- `Semana3/demos/demo_linked_adapters.cpp`
- `Semana3/demos/demo_contiguous_vs_linked.cpp`

### Tabla de análisis de mis demos

| Archivo | Salida u observable importante | Idea estructural | Argumento de costo, espacio o diseño |
| :--- | :--- | :--- | :--- |
| **`demo_sllist.cpp`** | `peek = 5`, `pop = 5`, `remove = 10` | Lista simple que guarda referencias a `head` y `tail`. | Frente y fin cuestan O(1). No sirve para deques porque eliminar el último cuesta O(n). |
| **`demo_dllist.cpp`** | `DLList: 10 30 20` | Lista doble con nodo centinela (`dummy`). | Bidireccionalidad optimiza búsqueda a O(1 + min(i, n-i)). Centinela elimina los "if" de casos borde. |
| **`demo_selist.cpp`** | `SEList: 0 10 ... 90` | Nodos que contienen arreglos fijos (`BDeque`). | Reduce el desperdicio de RAM agrupando datos. Más rápida que `DLList` al saltar de bloque en bloque. |
| **`demo_deng_list.cpp`** | `ordenada: 5 10 20 30` | Patrón *wrapper* sobre listas de Morin. | Expone métodos avanzados (`sort`) sin romper el diseño de bajo nivel de la lista original. |
| **`demo_morin_deng_bridge.cpp`** | `DLList reforzada...: 1 2 3 4` | Muestra un puente entre bibliotecas distintas. | Permite aplicar operaciones costosas (ej. `dedup`) temporalmente y devolver los datos limpios. |
| **`demo_capitulo3_panorama.cpp`** | Muestra extremos de todas las colecciones. | Instancia y prueba todo el ADT en conjunto. | Valida empíricamente que todas mis interfaces responden correctamente a los mismos comandos lógicos. |
| **`demo_min_structures.cpp`** | `MinStack min=2 top=7` | Estructuras decoradas que guardan mínimos históricos. | Sacrifica RAM (espacio O(n) extra) a cambio de poder responder a `min()` en tiempo O(1) instantáneo. |
| **`demo_xor_list.cpp`** | `XorList: 5 10 20` | Usa lógica de bits para comprimir punteros. | Logra bidireccionalidad usando el mismo espacio que una lista simple (XOR entre prev y next). |
| **`demo_linked_adapters.cpp`** | Restricciones estrictas (`pop`, `front`). | Oculta la lista base dejando solo métodos del ADT. | Garantiza seguridad restringiendo acceso aleatorio O(n) y asegurando O(1). |
| **`demo_contiguous_vs_linked.cpp`** | Comparativa `ArrayDeque` vs `LinkedDeque`. | Enfrenta arreglos contra nodos. | Confirma que arreglos ganan en caché y acceso directo; nodos ganan en inserciones sin redimensionar. |

### Evidencias de Ejecución Local

**Ejecución: demo_sllist.cpp**
```text
$ ./sem3_demo_sllist
size = 3
peek = 5
pop = 5
remove = 10
```

**Ejecución: demo_dllist.cpp**
```text
$ ./sem3_demo_dllist
DLList: 10 20 30 
```

**Ejecución: demo_selist.cpp**
```text
$ ./sem3_demo_selist
SEList: 0 10 20 30 40 50 60 70 80 90 
```

**Ejecución: demo_deng_list.cpp**
```text
$ ./sem3_demo_deng_list.exe
size = 4
front = 5
back = 20
ordenada: 5 10 20 30 
```

**Ejecución: demo_morin_deng_bridge.cpp**
```text
$ ./sem3_demo_morin_deng_bridge.exe
DLList reforzada con Deng: 1 2 3 4 
Removido = 1
```

**Ejecución: demo_min_structures.cpp**
```text
$ ./sem3_demo_min_structures
MinStack min=3 top=7
MinQueue min=2 front=4
MinDeque min=1 front=3 back=1
```

**Ejecución: demo_xor_list.cpp**
```text
$ ./sem3_demo_xor_list
XorList: 5 10 20 
front=5 back=20
```

**Ejecución: demo_linked_adapters.cpp**
```text
$ ./sem3_demo_linked_adapters
Adaptadores enlazados de Semana 3

LinkedStack
  top() = 30
  pop() = 30
  top() = 20
  size() = 2

LinkedQueue
  front() = 1
  remove() = 1
  front() = 2
  size() = 2

LinkedDeque
  front() = 10, back() = 40
  removeFirst() = 10
  removeLast() = 40
  front() = 20, back() = 30
  size() = 2
```

**Ejecución: demo_contiguous_vs_linked.cpp**
```text
$ ./sem3_demo_contiguous_vs_linked
Comparacion contiguo vs enlazado (standalone Semana3)

[1] Cola FIFO
  Cola contigua (sobre ArrayDeque)  front/remove: 1 / 1
  Cola enlazada (LinkedQueue)       front/remove: 1 / 1

[2] Deque
  ArrayDeque   first/last: a / d
  LinkedDeque  first/last: a / d

[3] Acceso por indice
  ArrayDeque get(4) = 40
  DLList    get(4) = 40
```

### Análisis de mis Observables (Semana 3)

### 1. En `demo_sllist.cpp`, ¿qué secuencia deja más clara la coexistencia de comportamiento tipo pila y tipo cola?
Al correr en mi terminal la secuencia de `push(5)` (pila) seguida de `add(10)` y `add(20)` (cola). Al ejecutar `pop()` y obtener el 5, y luego `remove()` para obtener el 10, vi clarísimo que la estructura soporta ambos protocolos por sus extremos sin conflicto.

### 2. En `demo_dllist.cpp`, ¿qué operación muestra mejor la inserción en una posición intermedia?
La operación `d.add(1, 20)`. Al ver que inserta el 20 en medio del 10 y el 30, comprobé que la `DLList` reengancha punteros rápidamente en cualquier parte usando el nodo centinela.

### 3. En `demo_selist.cpp`, ¿qué observable permite defender el orden lógico frente al trabajo por bloques?
La salida de mi consola `SEList: 0 10 20 ... 90`. Aunque sé que por dentro mis datos están cortados en miniarreglos (`BDeque`), la interfaz me los devuelve perfectamente en orden, demostrándome que la abstracción protege al usuario de la complejidad interna.

### 4. En `demo_deng_list.cpp`, ¿qué evidencia muestra un ADT de lista más completo?
Al ver el método `lista.sort()` ejecutándose. Esto me demuestra que `DengList` no es un simple contenedor de datos tonto, sino que tiene algoritmos de procesamiento pesados incorporados listos para usarse.

### 5. En `demo_morin_deng_bridge.cpp`, ¿qué justifica la reutilización de algoritmos?
Ver impreso `Removido = 1` tras aplicar `dedup_with_deng(lista)`. Justifica que puedo aplicarle un algoritmo complejo (quitar duplicados) a mi modesta `DLList` usando un puente, ahorrándome reprogramar la lógica de deduplicación.

### 6. En `demo_min_structures.cpp`, ¿qué diferencia conceptual se observa en `min()`?
Observé que no escanea toda la lista buscando el número más pequeño. Simplemente invierte más memoria guardando el "mínimo histórico" en cada nodo, logrando devolverme la respuesta al instante en O(1).

### 7. En `demo_linked_adapters.cpp`, ¿qué adaptador representa mejor la reutilización?
Para mí, `LinkedStack`. Usa toda la maquinaria de la `SLList` completa, pero "apaga" o esconde todos los métodos excepto los que tocan la cabecera, cumpliendo con la definición teórica de Pila.

### 8. En `demo_contiguous_vs_linked.cpp`, ¿qué contraste se observa en los accesos?
Al compararlos en tiempo real, confirmé que `ArrayDeque` aplasta en velocidad si quiero consultar el índice 1000 gracias a la memoria RAM contigua, mientras que `LinkedDeque` es mi mejor opción si voy a estar metiendo y sacando datos a cada rato en los extremos sin querer gastar CPU copiando arreglos.

## Bloque 3 - Pruebas públicas, stress y correctitud

### Material Revisado:
- `Semana3/pruebas_publicas/README.md`
- `Semana3/pruebas_publicas/test_public_week3.cpp`
- `Semana3/pruebas_publicas/test_public_deng_bridge.cpp`
- `Semana3/pruebas_publicas/test_public_extras.cpp`
- `Semana3/pruebas_publicas/test_public_linked_adapters.cpp`
- `Semana3/pruebas_publicas/test_public_contiguous_vs_linked.cpp`
- `Semana3/pruebas_internas/test_internal_week3.cpp`
- `Semana3/pruebas_internas/test_internal_deng_algorithms.cpp`
- `Semana3/pruebas_internas/test_internal_extras.cpp`
- `Semana3/pruebas_internas/stress_selist_week3.cpp`

### 1. ¿Qué operaciones mínimas valida la prueba pública para `SLList`?
Al leer el test, vi que valida: inserción al inicio (`push`) y al final (`add`), lectura frontal (`peek`), eliminación frontal (`pop`/`remove`), y que el contador `size` se actualice bien.

### 2. ¿Qué operaciones mínimas valida la prueba pública para `DLList`?
Valida mi comportamiento de lista general: insertar por índice (`add(i, x)`), leer por índice (`get(i)`), borrar por índice (`remove(i)`) y el tamaño.

### 3. ¿Qué operaciones mínimas valida la prueba pública para `SEList`?
Prueba exactamente las mismas operaciones que la `DLList`, pero asegurándose de que la lógica no se rompa al buscar adentro de los bloques internos y sub-colas.

### 4. ¿Qué operaciones nuevas quedan cubiertas por `test_public_extras.cpp`?
Noté que cubre mis algoritmos experimentales y avanzados: invertir (`reverse`), rotar (`rotate`), buscar el penúltimo (`secondLast`), chequear palíndromos, y el comportamiento de mis estructuras extra (`MinStack`, `XorList`).

### 5. ¿Qué valida específicamente `test_public_linked_adapters.cpp` sobre `LinkedStack`, `LinkedQueue` y `LinkedDeque`?
Valida que realmente me hayan quedado bien encapsuladas. El test trata de usar métodos que romperían la regla (como leer el medio de una cola), y confirma que mis adaptadores solo exponen métodos LIFO, FIFO y de extremos dobles respectivamente.

### 6. ¿Qué demuestra `test_public_deng_bridge.cpp` sobre integración y reutilización?
Me demostró la interoperabilidad. Probé que puedo meter una `DLList` por el puente, hacerle un `sort` o un `dedup` teórico de Deng, y sacarla ordenada sin perder un solo dato ni romper punteros.

### 7. En `stress_selist_week3.cpp`, ¿qué comportamiento intenta estresar sobre crecimiento, borrado y mantenimiento del tamaño lógico?
Corrí este test y vi que inserta 500 datos de golpe, borra 250 y mete 100 en medio. Su meta es torturar mis funciones `spread` y `gather` para obligarlas a reacomodar bloques en memoria a lo loco, verificando que mi variable tamaño termine marcando exactamente 350.

### 8. ¿Qué sí demuestra una prueba pública sobre una estructura enlazada?
Para mí, demuestra la correctitud funcional básica. Me da la tranquilidad empírica de que no dejé punteros apuntando a la nada (*segfaults*) y que los métodos hacen lo que dicen hacer para mis entradas de prueba.

### 9. ¿Qué no demuestra una prueba pública por sí sola?
No me demuestra que mi código sea eficiente asintóticamente (O(1) o O(n)), ni garantiza que mi código esté libre de fugas de memoria silenciosas (*memory leaks*) que podrían tumbar el servidor después de horas de uso.

### 10 . ¿Por qué pasar pruebas no reemplaza una explicación de invariantes, punteros y complejidad?
Porque una prueba es como decir "funcionó esta vez", pero solo entendiendo las invariantes teóricas y calculando mi Big O puedo jurar que mi código va a sobrevivir aunque le inyecte diez millones de datos en producción.

## Bloque 4 - SLList, DLList y SEList: lectura cercana del código

### Material Revisado:
- `Semana3/include/SLList.h`
- `Semana3/include/DLList.h`
- `Semana3/include/SEList.h`
- `Parte3-Morin.pdf`
- `Parte3-Deng.pdf`

### 1. En SLList, ¿qué papel cumplen head, tail y n?
`head` es mi puntero que agarra el inicio del tren de nodos, `tail` es mi puntero atajo para el último vagón, y `n` es mi contador entero para no tener que recorrer toda la lista cada vez que alguien pregunta el tamaño.

### 2. En SLList::push, pop, add y remove, ¿qué punteros cambian exactamente?
- En `push`: El `next` de mi nuevo nodo agarra al viejo `head`, y luego `head` se muda a mi nuevo nodo.
- En `pop`: `head` salta a `head->next`, soltando el primer nodo para que se borre.
- En `add`: El `next` de mi `tail` actual agarra al nodo nuevo, y luego `tail` se actualiza al nuevo.

### 3. Expliquen cómo funciona secondLast() y por qué no puede resolverse directamente con solo mirar tail.
Vi que `secondLast()` se ve obligado a recorrer todo desde `head` usando un `while` hasta que ve que el `next` de su nodo actual es igual a `tail`. No puedo mirarlo desde `tail` porque en la `SLList` las flechas son de una vía; `tail` no sabe quién lo está apuntando por la espalda.

### 4. Expliquen paso a paso cómo funciona reverse() y por qué no necesita estructura auxiliar.
Paso a paso que observé analizando el código:
1. Me guardo a dónde iba el nodo (`next = curr->next`).
2. Volteo físicamente la flecha de mi nodo hacia atrás (`curr->next = prev`).
3. Doy un paso a la derecha con mis variables temporales.
No ocupa memoria auxiliar porque solo me dedico a desatar nudos y amarrarlos al revés, no creo nodos nuevos.

### 5. Expliquen qué verifica checkSize() y por qué esta función ayuda a defender correctitud.
Verifica manualmente la integridad de mi estructura: se va caminando desde `head` contando los nodos uno por uno y verifica que ese conteo físico sea idéntico a mi variable `n`. Me salva la vida para darme cuenta rápido si en alguna función me olvidé de actualizar `n` o rompí la cadena de punteros.

### 6. En DLList, expliquen por qué getNode(i) puede empezar desde el inicio o desde el final.
Porque al ser doblemente enlazada, tengo flechas de reversa. Si me piden el índice 900 de una lista de 1000, el código usa un "if" matemático inteligente y decide empezar por la cola y dar 100 pasos atrás, en vez de dar 900 pasos hacia adelante desde la cabeza.

### 7. En DLList::addBefore, ¿qué enlaces se actualizan y por qué el nodo centinela elimina casos borde?
Al insertar el nuevo nodo `u`, noté que conecto cuatro cables: los dos del nuevo (`next` y `prev`), la flecha de ida del anterior (`u->prev->next = u`) y la flecha de regreso del siguiente (`u->next->prev = u`). El centinela (`dummy`) es brillante porque es un nodo falso perpetuo que me garantiza que SIEMPRE tendré a alguien a la derecha o izquierda, borrando los pesados `if(head == null)` de mi código.

### 8. Expliquen cómo funciona rotate(r) sin mover los datos elemento por elemento.
En lugar de vaciar valores uno a uno, `rotate(r)` calcula dónde debe ser el nuevo punto de corte, desengancha el anillo físico en esa zona y reconecta el centinela a los nuevos extremos. Roto la lista entera haciendo trampa con solo un par de punteros.

### 9. Expliquen cómo isPalindrome() aprovecha la naturaleza doblemente enlazada de la estructura.
Pone a correr a dos punteros a la vez: uno avanza desde la cabeza con `next` y el otro retrocede desde la cola con `prev`. Chocan en el medio comparando valores en tiempo récord, algo impensable si solo tuviera enlaces de ida.

### 10. En SEList, expliquen qué representa Location.
Es mi mapa de coordenadas. `u` me indica en qué nodo grande de la lista aterricé (el bloque), y `j` me indica la dirección de memoria exacta o el índice interno dentro del miniarreglo (`BDeque`) de ese nodo.

### 11. Expliquen qué hacen spread() y gather() y en qué situaciones aparecen.
Comprendí que son mis funciones de mantenimiento de memoria:
- `spread()` reacciona cuando meto datos y un bloque revienta; crea un bloque nuevo y "unta" o reparte los sobrantes entre los vecinos para que nadie quede al 100% de capacidad.
- `gather()` reacciona al borrar datos; si ve bloques medio vacíos, "recolecta" a los sobrevivientes, los aprieta en un solo bloque y destruye el vacío para liberar RAM.

### 12. Expliquen cómo el tamaño de bloque b afecta el trade-off entre acceso, actualización y uso de espacio.
Descubrí que la variable `b` es la perilla de balance:
- Si pongo una `b` gigante: ahorro RAM porque uso poquísimos punteros, pero me demoro más en las inserciones locales porque tengo que mover datos como si fuera un arreglo clásico.
- Si pongo una `b` enana: inserto y borro rápido a nivel local, pero gasto un montón de memoria en punteros para atar tantos bloques pequeños.

## Bloque 5 - Adaptadores y estructuras derivadas

### Material Revisado:
- `Semana3/include/LinkedStack.h`
- `Semana3/include/LinkedQueue.h`
- `Semana3/include/LinkedDeque.h`
- `Semana3/include/MinStack.h`
- `Semana3/include/MinQueue.h`
- `Semana3/include/MinDeque.h`
- `Semana3/demos/demo_linked_adapters.cpp`
- `Semana3/demos/demo_min_structures.cpp`

### 1. ¿Cómo reutiliza `LinkedStack` a `SLList`?
Al revisar el código, vi que reutiliza la lista mediante composición. Metí una `SLList` privada adentro de la clase y redirigí mis comandos públicos `push` y `pop` para que internamente llamen a los métodos frontales de la lista base.

### 2. ¿Cómo reutiliza `LinkedQueue` a `SLList`?
Igual que la pila. Para lograr el efecto fila del banco (FIFO), amarro mi método `add` a la función que inserta al fondo de la `SLList`, y amarro mi método `remove` a la función que borra a la cabeza.

### 3. ¿Por qué `LinkedDeque` se construye naturalmente sobre `DLList` y no sobre `SLList`?
Porque un Deque necesita poder inyectar y extirpar datos por los dos extremos en O(1). Si uso la `SLList`, puedo insertar atrás, pero el `removeLast` me obligaría a iterar todo el tren. Con la `DLList` y sus enlaces de reversa, arrancar un nodo de atrás me toma un instante.

### 4. En `MinStack`, ¿por qué cada entrada guarda el valor y el mínimo acumulado?
Porque así evito iterar. Si meto el número 5, anoto "el mínimo de aquí para abajo es 5". Si luego meto el 10, sigo anotando que "el mínimo es 5". Así, la función `min()` solo lee el papelito del último nodo en O(1).

### 5. En `MinQueue`, ¿por qué usar dos pilas permite mantener semántica FIFO y consulta de mínimo?
Vi que se emplean dos `MinStack`: una que hace de embudo de entrada (`in_`) y otra de salida (`out_`). Al vaciar `in_` sobre `out_`, el orden se voltea, logrando la magia FIFO de una cola. Luego solo comparo el mínimo de las dos pilas para tener el mínimo general.

### 6. En `MinDeque`, ¿qué problema resuelve el rebalanceo entre `front_` y `back_`?
Me salva cuando pido retirar un dato por el frente pero la subestructura `front_` está vacía (y todos los datos están amontonados atrás). `rebalance()` detiene el programa, lee todo, y corta la baraja por la mitad, repartiendo equitativamente para que ambos extremos respiren.

### 7. Comparen "implementar una estructura" y "adaptar una estructura existente" usando ejemplos de este bloque.
Para mí, "implementar" es mancharme las manos con la memoria, gestionando punteros, `new` y `delete` como hice en `SLList`. "Adaptar" es ponerme un traje de director: no creo nodos, simplemente uso una estructura ya construida (como hice en `LinkedStack`) y restrinjo su uso con nuevas reglas lógicas.

### 8. ¿Qué operaciones pueden defender como constantes y cuáles deben defender como amortizadas?
Puedo defender como constantes estrictas O(1) a los `push` y `pop` simples. Sin embargo, operaciones como `remove()` en mi `MinQueue` o los borrados en mi `MinDeque` debo defenderlos como de costo constante **amortizado**, porque la mayoría de veces son rápidos, pero estadísticamente a veces me tocará pagar el alto costo de hacer un rebalanceo o un vaciado de pila.

## Bloque 6 - Deng como refuerzo algorítmico y puente de integración

### Material Revisado:
- `Semana3/include/CleanList.h`
- `Semana3/include/DengList.h`
- `Semana3/include/MorinDengBridge.h`
- `Semana3/demos/demo_deng_list.cpp`
- `Semana3/demos/demo_morin_deng_bridge.cpp`
- `Semana3/pruebas_publicas/test_public_deng_bridge.cpp`
- `Semana3/pruebas_internas/test_internal_deng_algorithms.cpp`
- `Parte3-Deng.pdf`

### 1. ¿Qué operaciones del ADT de lista aparecen reforzadas en `DengList`?
Al revisar `DengList`, noté que me da las herramientas de procesamiento duro: el ordenamiento masivo (`sort`), purgado de clones (`dedup`, `uniquify`), voltear colecciones (`reverse`) y escaneo complejo (`search`).

### 2. ¿Qué ventaja tiene encapsular una lista más rica sin cambiar el resto de estructuras de Semana 3?
Me permite no violar el Principio de Responsabilidad Única. Dejo que las listas de Morin sigan siendo ágiles gestionando bytes de RAM, y encapsulo toda la lógica de ordenamiento pesada por separado. No ensucio mi código base.

### 3. Expliquen qué hacen `to_deng` y `assign_from_deng`.
Comprendí que son funciones traductoras. `to_deng` exporta mis datos de Morin, creando una copia en formato `DengList`. Y `assign_from_deng` es el viaje de regreso: purga la estructura original y le reasigna los datos limpios que llegaron del procesador de Deng.

### 4. Expliquen por qué `stable_sort_with_deng` no obliga a reimplementar ordenamiento dentro de `DLList` o `SEList`.
Porque hace uso del puente traductor. Agarra mi `DLList`, la disfraza de `DengList`, ejecuta el `sort()` maduro que ya está programado en Deng, y me devuelve los datos ordenados al formato original de Morin sin que yo haya tenido que programar un solo bucle de ordenamiento.

### 5. Expliquen qué hace `dedup_with_deng` y qué relación guarda con `deduplicate()` o `uniquify()` de la teoría.
Comprobé que esta función elimina elementos repetidos usando el puente hacia Deng. Aterrizando la teoría: `dedup` hace el trabajo sucio en listas desordenadas, pero si yo sé que mi lista ya está ordenada, utilizo la función optimizada `uniquify` para borrar duplicados adyacentes a hipervelocidad.

### 6. Expliquen por qué `reverse_with_deng` es un ejemplo de reutilización de algoritmos sobre una interfaz común.
Porque unifiqué el proceso. Sin importar si mis datos vienen empaquetados en bloques (`SEList`) o en nodos bidireccionales (`DLList`), los convierto al estándar común de Deng, les aplico la misma función matemática de volteo y los devuelvo a casa, ahorrándome diseñar un algoritmo `reverse` específico para cada topología.

### 7. ¿Qué costo adicional introduce la conversión entre estructuras y cuándo vale la pena aceptarlo?
Me cobra el peaje de iterar y copiar toda la memoria: tiempo O(n) y RAM extra O(n). Solo vale la pena pagarlo si la operación que voy a aplicar en Deng es extremadamente compleja (como un ordenamiento grueso), ya que el beneficio de reutilizar código supera la pequeña penalización de hacer la copia.

## Bloque 7: Comparación enlazado vs contiguo, variantes y evidencia experimental

### Material Revisado:
- `Semana3/include/ArrayDeque.h`
- `Semana3/include/XorList.h`
- `Semana3/demos/demo_contiguous_vs_linked.cpp`
- `Semana3/demos/demo_xor_list.cpp`
- `Semana3/benchmarks/benchmark_semana3.cpp`
- `Parte3-Morin.pdf`

### 1. Comparen `ArrayDeque` y `LinkedDeque`: ¿qué cambia en representación y qué cambia en costo observable?
En cuanto a la representación, noté que `ArrayDeque` guarda todo empacado en un solo bloque sólido de RAM, mientras que `LinkedDeque` tiene nodos flotando atados por hilos. En costo observable, mi `ArrayDeque` vuela leyendo posiciones aleatorias, pero si se llena hace que mi PC trabaje copiando arreglos nuevos; mi `LinkedDeque` jamás redimensiona y añade en extremos al instante, pero me castiga con lentitud extrema si le pido buscar el dato del medio.

### 2. ¿Qué significa que una representación contigua tenga mejor localidad de memoria?
Significa que mi hardware procesa esto mejor. Al estar los bytes pegados en la RAM, mi procesador carga todo el bloque de un golpe a su memoria caché ultrarrápida. Los nodos de lista enlazada, al estar regados, obligan a mi procesador a ir a la RAM lenta nodo por nodo (*cache misses*).

### 3. ¿Qué tipo de operaciones favorecen más a la representación enlazada?
Las inserciones y borrados caprichosos en medio de la estructura. Modificar una lista enlazada es un trabajo quirúrgico de O(1) con las flechas; en cambio, con un arreglo, meter un número me obliga a correr todo el peso de los datos restantes hacia la derecha.

### 4. En el benchmark, ¿qué comparación sirve mejor para discutir acceso aleatorio y cuál sirve mejor para discutir operaciones en extremos?
Al correr el benchmark, deduje que para analizar acceso aleatorio debo fijarme en `random_get_arraydeque` vs `random_get_dllist`, que cronometra la búsqueda agresiva. Y para discutir los extremos, la clave está en mirar el duelo `deque_contiguo_arraydeque` vs `deque_enlazado_linkeddeque`.

### 5. ¿Por qué el benchmark no debe leerse como prueba absoluta de superioridad de una estructura sobre otra?
Porque es una prueba de laboratorio aislada. El benchmark no midió si me quedé sin memoria RAM o si las latencias empeoraron tras horas de ejecución. Comprendí que no hay estructura mágica: todo depende de las reglas de mi caso de uso real en producción.

### 6. ¿Qué idea intenta mostrar `XorList` respecto al ahorro de punteros?
Me fascina cómo demuestra que puedo tener la navegación ida y vuelta de una lista doble usando el espacio en bytes de una lista simple. Comprime el puntero de atrás y adelante en una sola variable haciendo matemática de bits (`prev` XOR `next`).

### 7. ¿Qué desventaja práctica introduce una estructura como `XorList` aunque sea interesante desde el punto de vista del espacio?
La pesadilla del mantenimiento. Es imposible debuggear un puntero XOR a simple vista, pierdes la lectura limpia del código, y te arriesgas a crasheos letales si intentas acceder aleatoriamente sin conocer la dirección exacta de donde vienes.

## Bloque 8 - Cierre comparativo y preparación de sustentación

### ¿Qué cambia cuando pasamos de "usar arreglos dinámicos" a "diseñar estructuras enlazadas y adaptadores sobre nodos"?

Al terminar la semana, concluí que el paso de arreglos dinámicos a estructuras enlazadas es dejar atrás un paradigma físico rígido para adoptar uno de flexibilidad lógica. Resumo los cambios así:

* **Representación:** Dejé de pedirle a Windows grandes bloques de RAM ininterrumpidos y pasé a usar nodos independientes que flotan en la memoria, guiados solo por punteros.
* **Acceso y Costo:** Perdí mi súper poder aritmético de ir a `A[500]` en O(1). Ahora pago una penalización de O(n) para iterar, pero a cambio gané la capacidad de romper e insertar en la cadena en O(1) localmente sin afectar al resto.
* **Balance Estratégico:** Aprendí a mitigar los defectos. Usé la lista doble (`DLList`) para no quedar ciego hacia atrás, y la lista de bloques (`SEList`) para amortizar el duro gasto de RAM que generan tantos punteros por nodo.
* **Arquitectura de Software:** Comprendí la fuerza de la encapsulación. Utilizando **adaptadores** escondo mi lista compleja y expongo solo lo que me sirve para simular pilas o colas; y mediante **puentes de integración**, evito ensuciar mis clases puras de Morin conectándolas temporalmente a los algoritmos procesadores de Deng. 
* **Conclusión Realista:** Ninguno aplasta al otro. El bloque continuo domina donde reinan las búsquedas y la memoria caché, y los nodos dominan donde la escritura impredecible y la inserción quirúrgica son la ley.