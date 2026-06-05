#pragma once

#include <vector>
#include <iostream>
// Incluimos el Priority Queue (Max-Heap) de tu Semana 6
#include "PQ_ComplHeap.h"

class SmartInfants {
private:
  // Arreglos paralelos para saber la información de cada niño en O(1)
  std::vector<int> fuerza;
  std::vector<int> guarderia_actual;
  
  // Un arreglo de Max-Heaps. El índice es el ID de la guardería.
  // Cada guardería tendrá su propio Heap para saber quién es el más fuerte.
  std::vector<ods::PQ_ComplHeap<int>> guarderias;

  // Constante para el número máximo de guarderías según AtCoder (2 * 10^5)
  static const int MAX_GUARDERIAS = 200000;

public:
  // Constructor: inicializa los arreglos (1-indexed para facilitar la lectura)
  SmartInfants(int num_ninos) {
    fuerza.assign(num_ninos + 1, 0);
    guarderia_actual.assign(num_ninos + 1, 0);
    guarderias.resize(MAX_GUARDERIAS + 1);
  }

  // Registra a un niño al inicio del programa
  void registrar_nino(int id_nino, int rate, int guarderia) {
    fuerza[id_nino] = rate;
    guarderia_actual[id_nino] = guarderia;
    
    // Insertamos la fuerza del niño en el Heap de su respectiva guardería
    guarderias[guarderia].insert(rate);
  }

  // Método temporal para depurar el Día 2
  void imprimir_estado_inicial(int num_ninos) {
    std::cout << "--- ESTADO INICIAL ---\n";
    for (int i = 1; i <= num_ninos; ++i) {
      std::cout << "Nino " << i << " | Fuerza: " << fuerza[i] 
                << " | Guarderia: " << guarderia_actual[i] << "\n";
    }
  }
};