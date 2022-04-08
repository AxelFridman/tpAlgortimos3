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


    bool haySolapamiento(int& i, int& j) const;
    /*
     * Verifica si la actividad i-ésima se solapa con la actividad j-ésima
     */

    int cantActividades() const;
    int buscarBeneficioMax(int i, vector<int>&, int);
    /*
     * Busca el máximo beneficio entre todos los subconjuntos de
     * actividades compatibles incluidos en el máximo beneficio
     * entre todos los subconjuntos de actividades compatibles
     * incluidos en A_i ... A_{n-1}
     */

    int ejer3_4();
    void mostrarSolucion();


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

    int _maxBeneficio;
    vector<int> sol_optima;

    int sumaMax;

    void construirW(vector<int>&);
};







#endif //TPJUANEJ1_ACTIVIDADES_PD_H
