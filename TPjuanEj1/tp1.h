
#ifndef TPJUANEJ1_TP1_H
#define TPJUANEJ1_TP1_H
#include "red.h"

void ejercicio1(Red& red);

void buscarMaxInfl (set<int>& Q, set<int>& K, int infl, Red&);

int maxInfl(set<int>& K);

set<int >amigosDexEnY(int v, set<int>& K, Red&);

int pasar(set<int>&, set<int>&, Red&);
#endif //TPJUANEJ1_TP1_H
