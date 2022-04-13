#ifndef TPJUANEJ1_ACTIVIDADESGOLOSO_H
#define TPJUANEJ1_ACTIVIDADESGOLOSO_H

#include <iostream>
#include <vector>
#include <fstream>
#include <set>
#include <vector>

using namespace std;

class ActividadesGoloso{
public:

    ActividadesGoloso(string archivo);

    vector<int> ordenarPorT();

    int buscarMaxBeneficio();

    vector<int> construirRes();

    void ejer4_3();

private:

    int _N;
    vector<int> _S;
    vector<int> _T;
};
#endif //TPJUANEJ1_ACTIVIDADESGOLOSO_H
