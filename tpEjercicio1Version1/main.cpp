#include <iostream>
#include <vector>
#include "red.h"
#include "TP-1.h"
using namespace std;

int main(int argc, char** argv){

    if(argc!=2){
            cout << "Esta mal" << endl;
            return 0;
    }
    Red lared(argv[1]);

    /*char* archivo;
    cout << "Entrar archivo: ";
    cin >> archivo;
    Red lared(archivo);*/

     ejercicio1(lared);
}
