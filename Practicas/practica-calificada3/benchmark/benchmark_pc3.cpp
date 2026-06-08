#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include "SmartInfants.h"

int main() {
    std::cout << "------------------------------------------\n";
    std::cout << "  BENCHMARK: SMART INFANTS (ABC170 E)     \n";
    std::cout << "------------------------------------------\n";

    const int N = 20000; // Infantes
    const int Q = 10000; // Transferencias

    SmartInfants sistema(N);
    std::mt19937 rng(42);
    std::uniform_int_distribution<int> dist_rate(1, 10000);
    std::uniform_int_distribution<int> dist_guarderia(1, 2000);
    std::uniform_int_distribution<int> dist_infante(1, N);

    // Inicialización
    for (int i = 1; i <= N; ++i) {
        sistema.registrar_nino(i, dist_rate(rng), dist_guarderia(rng));
    }
    sistema.inicializar_maximos();

    // Medición de la solución óptima O(log N)
    auto start_optimo = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < Q; ++i) {
        int c = dist_infante(rng);
        int d = dist_guarderia(rng);
        sistema.mover_nino(c, d);
        volatile int ans = sistema.getMinGlobal(); // Volatile para evitar que el compilador lo optimice
    }
    auto end_optimo = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> tiempo_optimo = end_optimo - start_optimo;

    std::cout << "Operaciones: " << Q << " transferencias.\n";
    std::cout << "Tiempo solucion con Heaps y Lazy Deletion: " << tiempo_optimo.count() << " ms.\n";
    std::cout << "Complejidad demostrada: O(Q log N).\n";

    return 0;
}