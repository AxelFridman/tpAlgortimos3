#include <iostream>
#include <vector>
#include "red.h"
#include "tp1.h"
#include "actividades_PD.h"
using namespace std;

int main(int argc, char** argv){


    //char* archivo;
    string archivo;
    //cout << "Entrar archivo: ";
    //cin >> archivo;

    //Red lared(argv[1]);

//    Red lared(archivo);
    Red lared("../instancias/brock200_2.clq");
    ejercicio1(lared);

    //Actividades Actividades(archivo);
    //cout << Actividades.ejer3_4() << endl;
    //Actividades.mostrarSolucion();
}
