
#ifndef TPJUANEJ1_TP1_H
#define TPJUANEJ1_TP1_H
#include "red.h"

void ejercicio1(Red& red);

void buscarMaxInfl (set<int>& Q, vector<int>& K, int idx_K, vector<int>& usados, int infl, Red&);

vector<int> amigosDexEnY(int v, vector<int>& K, Red&);

int agregarTodosLosKenQeInfluenciaK(set<int>&, vector<int>&, Red&);
#endif //TPJUANEJ1_TP1_H
