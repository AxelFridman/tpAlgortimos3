
#ifndef TPJUANEJ1_TP1_H
#define TPJUANEJ1_TP1_H
#include "red.h"

void ejercicio1(Red& red);
void ejercicio2(Red& red);

void buscarMaxInflEj1 (set<int>& Q, list<int>& K, int infl, Red&);
void buscarMaxInflEj2 (set<int>& Q, list<int>& K, int infl, Red&);
void buscarMaxInflEnIndependientes (set<int>& Q, list<list<int>>& K, int infl, Red&);

list<int> amigosDexEnY(int v, list<int>& K, Red&);
bool sonTodosNoAmigosDeIter(list<int>::iterator it, list<int> &I_i, Red &red);
bool sonTodosNoAmigosEntreSi(list<int> &I_i, Red &red);

int agregarTodosLosKenQeInfluenciaK(set<int>&, list<int>&, Red&);
void agregarCadaAmigoDeTodosLosDemasEnK(set<int>&, list<int>&, int&, Red&);


void pasarAlgunosKenQyActualizarInfluencia(list<int>&, set<int>&, int&, Red);
#endif //TPJUANEJ1_TP1_H
