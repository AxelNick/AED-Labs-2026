#include <iostream>
#include "SmartInfants.h"

int main() {
  // Optimizacion de entrada/salida para problemas competitivos
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int N, Q;
  // Simularemos la lectura de AtCoder. 
  std::cout << "Ingrese N (ninos) y Q (consultas): ";
  if (!(std::cin >> N >> Q)) return 0;

  SmartInfants sistema(N);

  std::cout << "Ingrese la fuerza y guarderia de los " << N << " ninos:\n";
  for (int i = 1; i <= N; ++i) {
    int rate, guarderia;
    std::cin >> rate >> guarderia;
    sistema.registrar_nino(i, rate, guarderia);
  }

  sistema.imprimir_estado_inicial(N);

  // Las transferencias (Q) se vera en el Día 3
  std::cout << "Listo para programar transferencias...\n";

  return 0;
}