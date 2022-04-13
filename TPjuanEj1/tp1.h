
#ifndef TPJUANEJ1_TP1_H
#define TPJUANEJ1_TP1_H
#include "red.h"

void ejercicio1(Red& red);

void buscarMaxInfl (set<int>& Q, list<int>& K, int infl, Red&);

list<int> amigosDexEnY(int v, list<int>& K, Red&);

int agregarTodosLosKenQeInfluenciaK(set<int>&, list<int>&, Red&);

void pasarAlgunosKenQyActualizarInfluencia(list<int>&, set<int>&, int&, Red);
#endif //TPJUANEJ1_TP1_H
