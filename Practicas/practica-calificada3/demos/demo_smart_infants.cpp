#include <iostream>
#include "SmartInfants.h" 

int main() {
    std::cout << "DEMO VISUAL: SMART INFANTS Y LAZY DELETION\n\n";

    // Inicializamos la estructura para 3 infantes
    SmartInfants sistema(3); 

    std::cout << "[Fase 1] INGRESO DE INFANTES AL SISTEMA\n";
    std::cout << "-> Infante 1 (Fuerza 8) entra a la Guarderia 1\n";
    sistema.registrar_nino(1, 8, 1);
    
    std::cout << "-> Infante 2 (Fuerza 6) entra a la Guarderia 2\n";
    sistema.registrar_nino(2, 6, 2);
    
    std::cout << "-> Infante 3 (Fuerza 9) entra a la Guarderia 3\n";
    sistema.registrar_nino(3, 9, 3);

    // Inicializamos el multiset global despues del registro inicial
    sistema.inicializar_maximos();

    std::cout << "\nESTADO INICIAL:\n";
    std::cout << "Minimo de los maximos actual: " << sistema.getMinGlobal() << "\n\n";

    std::cout << "[Fase 2] INICIANDO TRANSFERENCIAS Y LAZY DELETION\n";
    std::cout << "-> Moviendo Infante 2 a la Guarderia 1...\n";
    sistema.mover_nino(2, 1);
    
    std::cout << "(Nota: El Infante 2 ha dejado un fantasma en la Guarderia 2)\n";
    std::cout << "Minimo global despues del movimiento: " << sistema.getMinGlobal() << "\n\n";

    std::cout << "[Fase 3] VACIADO DE GUARDERIA Y NUEVO MAXIMO (RETO EN VIVO)\n";
    std::cout << "-> Moviendo Infante 3 a la Guarderia 1...\n";
 
    sistema.mover_nino(3, 1); 
    
    std::cout << "\n(Nota: La Guarderia 3 ha quedado vacia y el sistema la ignora correctamente)\n";
    std::cout << "Minimo global final: " << sistema.getMinGlobal() << "\n\n";

    return 0;
}