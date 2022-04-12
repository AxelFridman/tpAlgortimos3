//
// Created by Noé Fabián HSUEH on 06/04/2022.
//

#ifndef TPJUANEJ1_ACTIVIDADES_PD_H
#define TPJUANEJ1_ACTIVIDADES_PD_H

#include <iostream>
#include <vector>
#include <fstream>
#include <set>
#include <vector>

using namespace std;

class Actividades {
public:
    Actividades(string archivo);
    /* Constructor de actividades, lee el archivo de entrada e inicializa
     * las variables internas.
    */

    int cantActividades() const;
    int buscarBeneficioMax(int i);
    /*
     * Busca el máximo beneficio entre todos los subconjuntos de
     * actividades compatibles incluidos en el máximo beneficio
     * entre todos los subconjuntos de actividades compatibles
     * incluidos en A_i ... A_{n-1}
     */

    void reiniciarMem();
    void ejer3_4();
    int bottom_up();
    void ejer3_5();
    vector<int> reConstruccionRes();
    void ejer3_6();


private:
    int _N; // cantidad de actividades
    vector<int> _S; // vector donde en la posición i-ésima indica
    // el tiempo de inicio de la actividad i
    vector<int> _T; // vector donde en la posición i-ésima indica
    // el tiempo de terminación de la actividad i
    vector<int> _B; // vector de beneficio
    vector<int> _W; // vector donde en la posición i-ésima indica
    // la primera actividad k que no se solapa con
    // la actividad i, con k > i. Si no existe, k=n.
    vector<int> _mem;

    void construirW(vector<int>&);
};







#endif //TPJUANEJ1_ACTIVIDADES_PD_H
