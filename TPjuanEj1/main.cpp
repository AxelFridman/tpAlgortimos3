#include <iostream>
#include <vector>
#include "red.h"
#include "tp1.h"
using namespace std;

int main(int argc, char** argv){

    /*if(argc!=2){
            cout << "Esta mal" << endl;
            return 0;
    }*/

    char* archivo;
    cout << "Entrar archivo: ";
    cin >> archivo;

    //Red lared(argv[1]);
    Red lared(archivo);
    ejercicio1(lared);
}
