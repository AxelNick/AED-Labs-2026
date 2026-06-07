#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
#include "../include/SmartInfants.h"

// 1. Caso mínimo: 1 solo infante
void test_caso_minimo() {
  SmartInfants sistema(1);
  sistema.registrar_nino(1, 100, 1);
  sistema.inicializar_maximos();
  
  assert(sistema.getMinGlobal() == 100);
  
  // Se mueve a otra guardería
  sistema.mover_nino(1, 2);
  assert(sistema.getMinGlobal() == 100);
  std::cout << "[OK] Test 1: Caso minimo pasado.\n";
}

// 2. Caso con estructura vacía / frontera
void test_estructura_vacia() {
  SmartInfants sistema(2);
  sistema.registrar_nino(1, 50, 1);
  sistema.registrar_nino(2, 60, 1); // Ambos en la guardería 1
  sistema.inicializar_maximos();
  
  assert(sistema.getMinGlobal() == 60);
  
  // Movemos al niño 2 a la guardería 2
  // La guardería 1 ya no tiene a su máximo anterior.
  sistema.mover_nino(2, 2);
  assert(sistema.getMinGlobal() == 50); // El min(50, 60)
  
  // Vaciamos la guardería 1 por completo
  sistema.mover_nino(1, 2);
  assert(sistema.getMinGlobal() == 60); // Solo queda la guardería 2 activa
  std::cout << "[OK] Test 2: Estructura vacia/frontera pasado.\n";
}

// 3. Caso con duplicados o empates
void test_duplicados() {
  SmartInfants sistema(3);
  sistema.registrar_nino(1, 80, 1);
  sistema.registrar_nino(2, 80, 1); // Empate en fuerza en la misma guardería
  sistema.registrar_nino(3, 90, 2);
  sistema.inicializar_maximos();
  
  assert(sistema.getMinGlobal() == 80);
  
  // Movemos un 80, la guardería 1 aún debería reportar 80 gracias al otro niño
  sistema.mover_nino(1, 3);
  assert(sistema.getMinGlobal() == 80); // min(80 de G1, 90 de G2, 80 de G3)
  std::cout << "[OK] Test 3: Duplicados y empates pasado.\n";
}

// 4. Caso extremo pequeño verificable manualmente
void test_extremo_manual() {
  // 3 infantes, fuerzas: 10, 20, 30. Todos empiezan separados
  SmartInfants sistema(3);
  sistema.registrar_nino(1, 10, 1);
  sistema.registrar_nino(2, 20, 2);
  sistema.registrar_nino(3, 30, 3);
  sistema.inicializar_maximos();
  
  assert(sistema.getMinGlobal() == 10);
  
  // Juntamos a 1 y 2 en la guardería 3
  sistema.mover_nino(1, 3);
  sistema.mover_nino(2, 3);
  // Ahora la G3 tiene {10, 20, 30}. G1 y G2 están vacías.
  assert(sistema.getMinGlobal() == 30);
  std::cout << "[OK] Test 4: Caso extremo manual pasado.\n";
}

// 5. Comparación contra solución ingenua (Fuerza Bruta O(N))
void test_solucion_ingenua() {
  std::vector<int> fuerzas = {0, 45, 12, 89, 34}; // Indice 0 sin usar
  std::vector<int> guarderias = {0, 1, 1, 2, 2};
  
  SmartInfants sistema(4);
  for(int i = 1; i <= 4; ++i) {
    sistema.registrar_nino(i, fuerzas[i], guarderias[i]);
  }
  sistema.inicializar_maximos();
  int min_global_optimo = sistema.getMinGlobal();
  
  // Algoritmo ingenuo: iterar todo el arreglo
  std::vector<int> max_por_g(3, -1);
  for(int i = 1; i <= 4; ++i) {
    max_por_g[guarderias[i]] = std::max(max_por_g[guarderias[i]], fuerzas[i]);
  }
  int min_global_ingenuo = 1e9;
  for(int m : max_por_g) {
    if(m != -1) min_global_ingenuo = std::min(min_global_ingenuo, m);
  }
  
  assert(min_global_optimo == min_global_ingenuo);
  std::cout << "[OK] Test 5: Benchmark vs Solucion Ingenua pasado.\n";
}

// 6. Prueba específica del invariante (Lazy Deletion)
void test_invariante() {
  SmartInfants sistema(2);
  sistema.registrar_nino(1, 100, 1);
  sistema.registrar_nino(2, 50, 1);
  sistema.inicializar_maximos();
  
  // Al mover al niño 1, el Heap de G1 conserva el 100 en la cima "basura" pero nuestro método getMaxReal() (Lazy Deletion) lo debe ignorar y reportar 50
  sistema.mover_nino(1, 2);
  // Si el Lazy Deletion falla, el sistema creería que la G1 sigue teniendo 100 y el mínimo global sería 100. Como funciona, el mínimo es 50
  assert(sistema.getMinGlobal() == 50);
  std::cout << "[OK] Test 6: Invariante principal (Lazy Deletion) pasado.\n";
}

int main() {
  std::cout << "--- INICIANDO PRUEBAS PC3 ---\n";
  test_caso_minimo();
  test_estructura_vacia();
  test_duplicados();
  test_extremo_manual();
  test_solucion_ingenua();
  test_invariante();
  std::cout << "--- TODAS LAS PRUEBAS PASARON EXITOSAMENTE ---\n";
  return 0;
}