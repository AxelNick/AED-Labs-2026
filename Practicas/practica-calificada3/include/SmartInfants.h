#pragma once

#include <vector>
#include <iostream>
#include <set>       // Para el multiset global
#include <utility>   // Para std::pair
#include "PQ_ComplHeap.h"

class SmartInfants {
private:
  // Arreglos paralelos para acceso O(1)
  std::vector<int> fuerza;
  std::vector<int> guarderia_actual;
  
  // Max-Heap modificado. Ahora guarda pares {fuerza, id_nino}.
  // Por defecto, std::pair se ordena por el primer elemento (la fuerza).
  std::vector<ods::PQ_ComplHeap<std::pair<int, int>>> guarderias;
  
  // Multiset para rastrear los máximos válidos de todas las guarderías.
  // Nos permite extraer el mínimo global en O(1) leyendo el primer elemento.
  std::multiset<int> maximos_globales;

  static const int MAX_GUARDERIAS = 200000;

  // LAZY DELETION
  // Elimina las cimas que corresponden a niños que ya no están en la guardería
  void limpiar_guarderia(int id_guarderia) {
    auto& heap = guarderias[id_guarderia];
    while (!heap.empty()) {
      auto tope = heap.getMax();
      int nino_top = tope.second;
      
      // Si el niño de la cima ya se mudó, lo descartamos (Lazy Deletion)
      if (guarderia_actual[nino_top] != id_guarderia) {
        heap.delMax();
      } else {
        break; // La cima es válida, detenemos la limpieza
      }
    }
  }

  // Devuelve la fuerza del más fuerte de una guardería, o -1 si está vacía
  int getMaxReal(int id_guarderia) {
    limpiar_guarderia(id_guarderia); // Aseguramos que la cima sea real
    if (guarderias[id_guarderia].empty()) return -1;
    return guarderias[id_guarderia].getMax().first;
  }

public:
  SmartInfants(int num_ninos) {
    fuerza.assign(num_ninos + 1, 0);
    guarderia_actual.assign(num_ninos + 1, 0);
    guarderias.resize(MAX_GUARDERIAS + 1);
  }

  void registrar_nino(int id_nino, int rate, int guarderia) {
    fuerza[id_nino] = rate;
    guarderia_actual[id_nino] = guarderia;
    guarderias[guarderia].insert({rate, id_nino});
  }

  // Llena el multiset global una vez leídos todos los niños al inicio
  void inicializar_maximos() {
    for (int i = 1; i <= MAX_GUARDERIAS; ++i) {
      int max_fuerza = getMaxReal(i);
      if (max_fuerza != -1) {
        maximos_globales.insert(max_fuerza);
      }
    }
  }

  // LÓGICA DE TRANSFERENCIA
  void mover_nino(int id_nino, int nueva_guarderia) {
    int vieja_guarderia = guarderia_actual[id_nino];
    if (vieja_guarderia == nueva_guarderia) return;

    // 1. Ubicar y retirar los máximos antiguos del multiset global
    int max_vieja_ant = getMaxReal(vieja_guarderia);
    int max_nueva_ant = getMaxReal(nueva_guarderia);

    if (max_vieja_ant != -1) {
      maximos_globales.erase(maximos_globales.find(max_vieja_ant));
    }
    if (max_nueva_ant != -1) {
      maximos_globales.erase(maximos_globales.find(max_nueva_ant));
    }

    // 2. Realizar la mudanza física
    guarderia_actual[id_nino] = nueva_guarderia;
    guarderias[nueva_guarderia].insert({fuerza[id_nino], id_nino});

    // 3. Obtener los nuevos máximos (esto dispara el Lazy Deletion internamente)
    int max_vieja_nuevo = getMaxReal(vieja_guarderia);
    int max_nueva_nuevo = getMaxReal(nueva_guarderia);

    //reto : grupo vacio 
    if(max_vieja_nuevo ==-1){
        std::cout << "[TRAZA en VIVO] : LA guarderia "<<vieja_guarderia<<" ha quedado vacia tras mover al niño "<<std::endl;

    }
    //Nuevo maximo
    if(max_nueva_nuevo > max_nueva_ant){

      std::cout << "[TRAZA EN VIVO] : La guarderia "<<nueva_guarderia << "recibe u nuevo maximo de " << max_nueva_nuevo << std::endl;
    }


    // 4. Registrar los nuevos máximos en el global
    if (max_vieja_nuevo != -1) {
      maximos_globales.insert(max_vieja_nuevo);
    }
    if (max_nueva_nuevo != -1) {
      maximos_globales.insert(max_nueva_nuevo);
    }
  }

  // Retorna la igualdad (minima o maxima)
  int getMinGlobal() {
    if (maximos_globales.empty()) return 0;
    return *maximos_globales.begin();
  }
};