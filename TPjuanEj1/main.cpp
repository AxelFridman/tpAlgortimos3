#include <iostream>
#include <vector>
#include "red.h"
#include "tp1.h"
#include "actividades_PD.h"
#include "actividadesGoloso.h"
using namespace std;

int main(int argc, char** argv){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    //Las siguientes lineas son en caso de pasar el archivo a leer ingresandolo como input
    /*
    char* archivo;
    string archivo;
    cout << "Entrar archivo: ";
    cin >> archivo;
    */

    //-----------------------------------------------------------------------------------------
    //El ejercio 1 y el 2
    //Red lared(archivo); //En caso de pasar el archivo a leer ingresandolo como input
    Red lared(argv[1]);
    //-----------------------------------------------------------------------------------------
    //Ejercicio 1-) con poda:
    //ejercicio1(lared);
    //-----------------------------------------------------------------------------------------
    //Ejercicio 2-):
    ejercicio2(lared);


    /*
    //-----------------------------------------------------------------------------------------
    //El ejercio 3
    //Actividades Actividades(archivo); //En caso de pasar el archivo a leer ingresandolo como input
    Actividades Actividades(argv[1]);
    //----------------------------------------------------------------------------------------

     //Ejercicio 3-) 4:
    //Actividades.ejer3_4();
    //-----------------------------------------------------------------------------------------

     //Actividades.reiniciarMem();
    //Ejercicio 3-) 5:
    //Actividades.ejer3_5();

     //------------------------------------------------------------------------------------------
    Actividades.reiniciarMem();
    //Ejercicio 3-) 6:
    Actividades.ejer3_6();
    */

    /*
    //-----------------------------------------------------------------------------------------
    //El ejercio 4
    //Ejercicio 4-) 3:
    //ActividadesGoloso ActividadesGoloso(archivo); //En caso de pasar el archivo a leer ingresandolo como input
    ActividadesGoloso ActividadesGoloso(argv[1]);
    ActividadesGoloso.ejer4_3();
     */
}
