#include <iostream>
#include "SmartInfants.h"

int main() {
  // Optimizacion para evitar exceso de tiempo limite
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int N, Q;
  if (!(std::cin >> N >> Q)) return 0;

  SmartInfants sistema(N);

  for (int i = 1; i <= N; ++i) {
    int rate, guarderia;
    std::cin >> rate >> guarderia;
    sistema.registrar_nino(i, rate, guarderia);
  }

  // Preparacion de la estructura global antes de la primera consulta
  sistema.inicializar_maximos();

  // Aca se procesa cada transferencia
  for (int i = 0; i < Q; ++i) {
    int c, d; // c: ID del niño, d: nueva guardería
    std::cin >> c >> d;
    sistema.mover_nino(c, d);
    
    // Impresion del mínimo de los máximos actuales
    std::cout << sistema.getMinGlobal() << "\n";
  }

  return 0;
}