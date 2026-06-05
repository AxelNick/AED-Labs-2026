# CC232 - Evaluación Parcial 1
**Semanas 0, 1, 2 y 3: fundamentos, arreglos dinámicos y listas**
**Versión C**

**Nombre:** Axel Alberto Reyes Baldeon  
**Código:** 20200485B

## SOLUCIONARIO

### Pregunta 1
Se desea implementar el ADT `IndexedBag<T>`, una colección que permite repetidos y mantiene un orden interno observable por índice:

```cpp
template<class T>
class IndexedBag {
public:
    int size() const;
    void add(T x);             // agrega al final lógico
    T get(int i) const;
    bool contains(T x) const;
    bool removeOne(T x);       // elimina una ocurrencia si existe
    void uniqueStable();       // elimina duplicados conservando primera aparicion
};
```
Compare tres posibles representaciones: ArrayStack, RootishArrayStack y SLList.

a) [0.5 pts] Distinga ADT, representación e implementación usando este ejemplo.

* **ADT:** Es la interfaz o el contrato (qué hace la estructura). En este caso sería `IndexedBag`, que permite repetidos y acceso por índice.
* **Representación:** Es cómo se organizan los datos en la memoria física.
* **Implementación:** Es el código fuente en C++ que hace que la representación funcione y cumpla con el ADT.

b) [0.7 pts] Complete y justifique costos para add, get, contains y removeOne en las tres representaciones.

* **ArrayStack:** 
    * `add`: O(1) amortizado (se pone al final, el costo del resize se diluye)
    * `get`: O(1) (acceso aritmético directo)
    * `contains`: O(n) (búsqueda lineal)
    * `removeOne`: O(n) (hay que buscar y luego empujar el resto a la izquierda para tapar el hueco)

* **RootishArrayStack:** 
    * `add`: O(1) amortizado (va al bloque final o reserva uno nuevo)
    * `get`: O(1) (se calcula el bloque con una ecuación sin iterar)
    * `contains`: O(n) (recorrer los bloques)
    * `removeOne`: O(n) (desplazar elementos en cascada entre los bloques)

* **SLList (con puntero tail):** 
    * `add`: O(1) (se enlaza directo en tail)
    * `get`: O(n) (hay que iterar nodo por nodo desde el inicio)
    * `contains`: O(n) (recorrido lineal)
    * `removeOne`: O(n) (iterar para encontrar y luego saltar el nodo)

c) [0.5 pts] Explique qué trade-off espacial introduce RootishArrayStack frente a ArrayStack.

ArrayStack desperdicia O(n) de memoria al duplicar su tamaño. El RootishArrayStack baja este desperdicio a solo O(√n) usando bloques que crecen aritméticamente. 
El trade-off es que ahorramos RAM, pero gastamos un poco de tiempo de CPU calculando raíces cuadradas para encontrar en qué bloque está el dato.

d) [0.5 pts] Indique qué operación es más incómoda para SLList y por qué.

La operación más incómoda es `get(i)`. Debido a que los datos están dispersos en memoria, buscar por índice obliga a iterar nodo por nodo desde el principio, lo que toma un tiempo lento de O(n).

e) [0.8 pts] Diseñe a alto nivel uniqueStable() y analice su costo si no se permite usar tablas hash ni estructuras externas no vistas.

Diseño : 
- Usamos dos bucles anidados.
- El bucle externo toma cada elemento de izquierda a derecha.
- El bucle interno busca hacia adelante si hay copias de ese elemento. 
- Si encuentra un duplicado, lo borra (o desplaza el arreglo) y ajusta el índice para no saltarse datos.

Costo: El primer bucle hara $n$ vueltas y el interno en promedio $n/2$. Esto nos da una complejidad de O(n^2), ya sea usando arreglo o lista, porque no podemos evitar la búsqueda lineal repetitiva.

### Pregunta 2

Considere la función recursiva que suma un arreglo:

```cpp
1 int sumRec(const int A[], int n) {
2     if (n == 0) return 0;
3     return sumRec(A, n-1) + A[n-1];
4 }
```

a) [0.5 pts] Trace sumRec([2,4,6,8],4) mostrando llamadas y retornos.

Llamadas:
* `sumRec(A, 4) -> sumRec(A, 3) + 8`
* `sumRec(A, 3) -> sumRec(A, 2) + 6`
* `sumRec(A, 2) -> sumRec(A, 1) + 4`
* `sumRec(A, 1) -> sumRec(A, 0) + 2`
* `sumRec(A, 0) -> 0` (El cual es el caso base)

Retornos:
* `0 + 2 = 2`
* `2 + 4 = 6`
* `6 + 6 = 12`
* `12 + 8 = 20`

Total: 20

b) [0.6 pts] Pruebe correctitud por inducción sobre $n$.

* **Base (n=0):** Retorna 0. Correcto, un arreglo vacío suma 0.
* **Hipótesis:** Asumimos que `sumRec(A, k)` suma correctamente los primeros $k$ elementos.
* **Paso (n=k+1):** La función retorna `sumRec(A, k) + A[k]`. Por la hipótesis, esto equivale a (Suma de los k elementos) + el elemento k+1. Por lo tanto, esto confirma que la suma total es correcta.

c) [0.5 pts] Analice tiempo y espacio adicional. Distinga memoria del arreglo y pila de llamadas.

* **Tiempo:** O(n), porque hace exactamente $n$ llamadas recursivas y cada suma cuesta O(1).
* **Espacio adicional:** O(n). El arreglo en sí se pasa por puntero (O(1)), pero la recursión crea un nuevo marco en el Call Stack por cada llamada, apilando $n$ llamadas en memoria antes de llegar al caso base.

d) [0.5 pts] Escriba una versión iterativa equivalente y proponga una invariante del ciclo.

```cpp
int sumIter(const int A[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += A[i];
    }
    return sum;
}
```

Invariante: Al inicio de la iteración i, la variable "sum" tiene la suma acumulada de los elementos desde A[0] hasta A[i-1]

e) [0.4 pts] Explique por qué pasar const int A[] comunica una intención útil para correctitud.

Evita que modifiquemos el arreglo por accidente dentro de la función (contrato de solo lectura). Esto previene bugs y le asegura a quien use la función que sus datos originales no serán alterados.

f) [0.5 pts] Indique dos casos borde y cómo deberían probarse.

1. Arreglo vacío (n=0): Para comprobar que pase directo al return 0 y no intente leer memoria inválida como A[-1].

2. Arreglo de 1 elemento (n=1): Para asegurar que la transición lógica al caso base (sumRec(A,0) + A[0]) funcione sin ciclos extra.

### Pregunta 3

Un RootishArrayStack usa bloques de tamaños $1, 2, 3, \dots, r$. Con $r$ bloques, la capacidad total es $r(r + 1)/2$.

a) [0.5 pts] Para $r = 5$, dibuje los bloques y ubique los índices lógicos 0 a 14.

La estructura divide la memoria en bloques separados, donde el bloque $b$ tiene capacidad $b+1$
- Bloque 0 : [ 0 ] -> tiene capacidad para 1 
- Bloque 1 : [ 1,2 ] -> tiene capacidad para 2 
- Bloque 2 : [ 3,4,5 ] -> tiene capacidad para 3
- Bloque 3 : [ 6,7,8,9 ] -> tiene capacidad para 4
- Bloque 4 : [ 10,11,12,13,14 ] -> tiene capacidad para 5

b) [0.6 pts] Para los índices $i = 0, 1, 2, 5, 9, 14$, indique el bloque y el desplazamiento dentro del bloque.

- i = 0  -> Bloque 0, Desplazamiento 0
- i = 1  -> Bloque 1, Desplazamiento 0
- i = 2  -> Bloque 1, Desplazamiento 1
- i = 5  -> Bloque 2, Desplazamiento 2
- i = 9  -> Bloque 3, Desplazamiento 3
- i = 14 -> Bloque 4, Desplazamiento 4

c) [0.5 pts] Explique por qué se necesita una función i2b(i) o locate(i).

Como los bloques tienen distinto tamaño y están separados en memoria, no podemos usar la suma directa memoria + i de los arreglos normales. Se necesita la función para calcular con matemáticas en qué bloque específico cayó el índice sin tener que iterar buscando.

d) [0.5 pts] Justifique por qué el espacio desperdiciado es $\mathcal{O}(\sqrt{n})$ cuando hay $n$ elementos.

El único espacio vacío está en el último bloque asignado. Si hay $r$ bloques, sabemos que $n \approx r^2 / 2$, por lo que despejando, la cantidad de bloques es $r \approx \sqrt{2n}$. Como el último bloque mide exactamente $r$, el número de celdas vacías es directamente proporcional a $\sqrt{n}$.

e) [0.5 pts] Compare el acceso por índice con ArrayStack. ¿Qué se conserva y qué costo adicional aparece?

- Se conserva la complejidad temporal teórica: ambos logran acceder en tiempo O(1). 
- El costo adicional es que RootishArrayStack hace trabajar un poco más al procesador calculando una raíz cuadrada y haciendo dos saltos de memoria (ubicar el bloque, luego el dato), mientras que ArrayStack es una suma simple.

f) [0.4 pts] Explique qué ocurre cuando se necesita crecer o reducir el número de bloques.

- Cuando crece: Se crea un bloque nuevo de tamaño $r+1$. No se necesita copiar ni mover la memoria antigua, a diferencia de un ArrayStack.
- Cuando se reduce: Si al borrar elementos el último bloque queda totalmente vacío, se libera esa memoria (delete) para dársela al sistema operativo.

### Pregunta 4 

Se tiene un DualArrayDeque implementado con dos ArrayStack: front guarda la primera mitad en orden inverso y back guarda la segunda mitad en orden normal. La secuencia lógica se obtiene leyendo front de atrás hacia adelante y luego back de adelante hacia atrás.

Inicialmente: front = [30, 20, 10] y back = [40, 50, 60, 70]. Por tanto, la secuencia lógica es [10, 20, 30, 40, 50, 60, 70].

a) [0.6 pts] Muestre cómo se calcula get(i) para $i = 0, 2, 3, 6$.

Como sabemos que el tamaño de front es f = 3:
* Si i < f, se busca en front[f - i - 1]
* Si i >=  f, se busca en back[i - f]

- i = 0: (0 < 3)  -> front[3 - 0 - 1] = front[2] = 10
- i = 2: (2 < 3)  -> front[3 - 2 - 1] = front[0] = 30
- i = 3: (3 >= 3) -> back[3 - 3] = back[0] = 40
- i = 6: (6 >= 3) -> back[6 - 3] = back[3] = 70

b) [0.6 pts] Ejecute add(1, 15) y add(6, 55) indicando en cuál arreglo se inserta y cómo cambia la representación.

- add(1, 15): Como 1 < 3, va a front en el índice físico 3 - 1 - 1 = 1.
front pasa a ser [30, 20, 15, 10]. Nuevo f = 4.

- add(6, 55): Con la nueva distribución , y 6 >= 4, va a back en el índice físico 6 - 4 = 2.
back pasa a ser [40, 50, 55, 60, 70].

c) [0.5 pts] Explique por qué front guarda su contenido en orden inverso.

Para alinear el inicio lógico del Deque con el final físico del arreglo front. Los arreglos insertan y borran en O(1) si es al final; al invertirlo, logramos que operaciones como addFirst sean instantáneas sin tener que mover todos los datos.

d) [0.6 pts] Defina una condición razonable de balance entre front y back. Explique qué debe hacer balance() cuando se viola.

La condición sería que un lado no debe ser más del triple del otro (ej. 3 * f < b o al revés). Esto evita que un arreglo cargue casi todo el peso.
Y en caso se viole el balance() se sacarían todos los datos y se repartirían mitad y mitad (n/2) entre front y back construyendo los arreglos desde cero.

e) [0.7 pts] Justifique que el rebalanceo puede mantener costos amortizados aceptables si no ocurre en cada operación.

balance() cuesta O(n) porque mueve todo. Pero una vez balanceado (mitad y mitad), para que se vuelva a desbalancear tienen que pasar muchas operaciones (aprox. n/4 inserciones). El costo pesado de O(n) se reparte entre todas esas operaciones rápidas, quedando matemáticamente en un costo promedio amortizado de O(1).

### Pregunta 5

Una SEList almacena elementos en bloques, donde cada bloque se comporta como un pequeño deque basado en arreglos. La intención es combinar acceso por bloques, inserciones locales y menor desperdicio de espacio que algunos arreglos dinámicos.

a) [0.5 pts] Explique la idea de representación de SEList y cómo difiere de una DLList simple.

Una SEList es una lista doble, pero en cada nodo guarda un pequeño arreglo (BDeque) con capacidad $b$ en vez de un solo valor. Esto reduce drásticamente la memoria gastada en punteros y ayuda a que la memoria Caché funcione mejor al agrupar datos contiguos.


b) [0.5 pts] Indique qué invariante debería cumplirse sobre el tamaño de los bloques, salvo quizá en extremos.

Para no desperdiciar espacio, los bloques internos deben estar consistentemente ocupados, manteniéndose típicamente limitados a un tamaño entre $b-1$ y $b+1$, a excepción del primer y último bloque.


c) [0.6 pts] Describa qué ocurre al insertar en un bloque lleno: búsqueda de espacio, desplazamientos entre bloques o creación de bloque nuevo.

Llama a spread(). Busca un bloque vecino cercano con espacio y empuja un dato en cascada a través de los bloques intermedios para hacer hueco. Si no hay ningún bloque con espacio cerca, crea uno nuevo, lo enlaza y reparte los datos.

d) [0.5 pts] Compare SEList con ArrayDeque para muchas inserciones cerca del centro.

ArrayDeque es malo aquí porque obliga a mover la mitad de todo el arreglo ($O(n)$ real). 
SEList en cambio es mejor porque el desplazamiento es local: solo mueve datos dentro de su propio bloque o a los vecinos más próximos, manteniendo el costo amortizado bajo.

e) [0.4 pts] Explique por qué la interfaz puede parecer la de una lista aunque internamente use arreglos pequeños.

Esto es debido al encapsulamiento. El usuario solo ve los métodos estándar del ADT (add, get).
Mientras que toda la complejidad , la cual traduce un indice logico aun par de coordenadas(bloque y desplazamiento) queda oculta.

f) [0.5 pts] Proponga una prueba de estrés que detecte errores de tamaño lógico o pérdida de elementos.

Meter masivamente miles de elementos en posiciones aleatorias y luego borrar la mitad de forma intercalada. Luego, el detector o checkSize() recorre nodo por nodo contando cuántos elementos físicos quedan todavia. Si ese conteo físico no cuadra exactamente con la variable teórica size, significa que hubo fugas o se sobrescribieron datos.

### Pregunta 6

Un estudiante entrega una implementación de ArrayDeque::remove(i) que pasa las pruebas públicas, pero falla en pruebas internas cuando hay wrap-around y cuando se elimina el primer o último elemento.

a) [0.6 pts] Proponga 2 pruebas concretas que probablemente fallen si no se maneja correctamente el wrap-around.

1. Llenar cruzando el límite final físico y borrar un elemento en medio. Si el código no usa módulo (%), fallará al intentar mover los datos fuera de los límites de la RAM.

2. Configurar que el índice lógico 0 coincida con la última posición del arreglo y hacer remove(0). Si no hay wrap-around, el puntero avanzará a memoria basura en lugar de reiniciar en 0.

b) [0.4 pts] Proponga 2 pruebas para eliminación en estructura de tamaño 1 y tamaño 2.

- Para tamaño 1: Meter un dato y borrarlo. La prueba debe verificar que la estructura no colapse al quedar vacía (size == 0) y aguante una nueva inserción sin romperse.

- Para tamaño 2: Meter dos datos, borrar el primero y ver que el puntero apunte limpiamente al segundo sin dejar rastros o "basura" del dato anterior.

c) [0.4 pts] Explique por qué pasar pruebas públicas no prueba correctitud total.

Las pruebas públicas solo validan escenarios controlados para asegurar que la interfaz básica responde. Nunca van a cubrir las infinitas posibilidades de casos borde y combinaciones degeneradas que ocurren cuando la memoria se fragmenta tras miles de operaciones en un entorno real.

d) [0.3 pts] Indique qué invariante debería revisarse después de cada eliminación.

Después de cada eliminación, debe revisar que $0 \le n \le capacity$, que el puntero frontal siga siendo válido ($0 \le j < capacity$) y verificar si toca reducir el arreglo físico (usualmente si $3n < capacity$).

e) [0.3 pts] Explique qué tipo de error podría detectar ASan en una implementación incorrecta y qué tipo de error lógico no detectaría.

Sí detecta: Accesos ilegales a la memoria osea si calculas mal el desplazamiento y escribes fuera del límite físico del arreglo (buffer overflow).

No detecta: Si tienes un error de lógica y borras el dato equivocado, pero lo haces dentro de tu memoria válida, ASan no dirá nada porque no violaste ninguna regla del sistema operativo.

### Pregunta 7 

Se desea mantener un historial de operaciones con soporte para deshacer. La estructura debe ofrecer:
apply(x), undo(), current(), size(), clear().

Cada apply(x) agrega un nuevo estado al final. undo() vuelve al estado anterior. current() retorna el estado actual.

a) [0.4 pts] Defina el ADT con precondiciones y comportamiento observable.

- apply(x): Agrega el estado x al historial.Se observa que size() aumenta en 1 y current() ahora retorna x.
- undo(): Elimina el estado más reciente, su precondicion seria que size() > 0.Y se observa que size() disminuye en 1 y current() retorna el estado anterior.
- current(): Retorna el estado más reciente sin eliminarlo ,tiene como precondicion que size() > 0.
- size(): Retorna la cantidad total de estados guardados.
- clear(): Vacía todo el historial y se observa que size() == 0.


b) [0.6 pts] Proponga dos representaciones: una basada en arreglo dinámico y otra basada en lista enlazada. Indique sus invariantes.

- Para un arreglo dinámico (ArrayStack) ,el cual utiliza un bloque de memoria contigua , la invariante seria la cantidad de elementos n nunca puede superar la capacidad física de la memoria reservada (0 <= n <= capacity). El elemento actual siempre reside en el índice n-1.

- Para una lista enlazada (LinkedStack) ,el cual utiliza nodos individuales conectados por punteros, la invariante seria que el puntero principal apunta siempre al estado más reciente. La cantidad de nodos enlazados es exactamente igual al valor de size

c) [0.6 pts] Compare costos de apply, undo, current y clear.

Para un arreglo dinámico apply y undo cuestan O(1) amortizado porque de vez en cuando el arreglo se llena y debe duplicar su tamaño o contraerse, lo que cuesta O(n), pero se diluye.El current es O(1) y clear es O(1) porque se reinicia el contador de tamaño a 0.

Para una lista enlazada apply, undo y current son O(1) ya que solo se reasignan un par de punteros sin importar cuántos datos haya.En cambio clear cuesta O(n), porque hay que iterar liberando memoria nodo por nodo.

d) [0.5 pts] Explique cómo manejaría el caso de deshacer hasta quedar sin estado previo.

Lanzando una excepción tipo de la forma "std::out_of_range". Esto interrumpe el flujo y avisa al código principal que se rompió la precondición, evitando que se manipule memoria inválida o se alteren punteros nulos.

e) [0.4 pts] Proponga pruebas para secuencias largas, estados repetidos y operaciones inválidas.

Secuencias largas: Ejecutar un bucle que haga 100 000 apply() , seguidos de 100 000 undo() para estresar los resizes de memoria.

Estados repetidos: Hacer apply("A"), apply("A") y luego undo().Para comprobar que la estructura no se confunda y borre ambos al ver el mismo valor.

Operaciones inválidas: Ejecutar clear() y luego undo() para comprobar que salte la excepción de seguridad.

f) [0.5 pts] Suponga que ahora se pide consultar cualquier estado por índice. Reevalúe su elección de estructura y justifica.

Si se nos pide acceder a cualquier estado usando un índice , optaria por usar el arreglo dinámico en vez de una lista enlazada , ya que para el arreglo saltar a un índice cuesta $O(1)$ haciendo una suma aritmética de punteros.En cambio si usaramos una lista enlazada, estaríamos obligados a iterar nodo por nodo, matando el rendimiento a $O(n)$.
